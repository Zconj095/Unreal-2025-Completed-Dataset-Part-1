import sys
import traceback
import argparse
from typing import Optional


DEFAULT_MODEL_ID = "mistralai/Codestral-22B-v0.1"


def _try_import(name: str):
    try:
        module = __import__(name)
        return module, None
    except Exception as e:
        return None, e


def _pick_device_and_dtype(torch):
    if torch.cuda.is_available():
        return "cuda", (torch.bfloat16 if torch.cuda.is_bf16_supported() else torch.float16)
    if getattr(torch.backends, "mps", None) and torch.backends.mps.is_available():
        return "mps", torch.float16
    return "cpu", torch.float32


def _generate_with_transformers(
    model_id: str,
    prompt: str,
    max_new_tokens: int,
    temperature: float,
    top_p: float,
    load_in_4bit: bool,
    load_in_8bit: bool,
):
    import torch
    from transformers import AutoModelForCausalLM, AutoTokenizer

    device, dtype = _pick_device_and_dtype(torch)

    tokenizer = AutoTokenizer.from_pretrained(model_id, trust_remote_code=True)

    model_kwargs = {
        "torch_dtype": dtype,
        "device_map": "auto" if device in ("cuda", "mps") else None,
        "trust_remote_code": True,
    }

    if load_in_4bit:
        model_kwargs["load_in_4bit"] = True
    if load_in_8bit:
        model_kwargs["load_in_8bit"] = True

    model = AutoModelForCausalLM.from_pretrained(model_id, **model_kwargs)

    if device == "cpu":
        model = model.to(device)

    inputs = tokenizer(prompt, return_tensors="pt")
    inputs = {k: v.to(model.device) for k, v in inputs.items()}

    output_ids = model.generate(
        **inputs,
        max_new_tokens=max_new_tokens,
        do_sample=temperature > 0,
        temperature=temperature,
        top_p=top_p,
        eos_token_id=tokenizer.eos_token_id,
        pad_token_id=tokenizer.eos_token_id,
    )

    return tokenizer.decode(output_ids[0], skip_special_tokens=True)


def _build_codestral_prompt(model_id: str, system: Optional[str], user: str) -> str:
    system = system.strip() if system else ""
    user = user.strip()

    # Prefer a chat template if the tokenizer supports it, otherwise fall back to a simple instruction format.
    tokenizer, _ = _try_import("transformers")
    if tokenizer is not None:
        try:
            from transformers import AutoTokenizer

            tok = AutoTokenizer.from_pretrained(model_id, trust_remote_code=True)
            if hasattr(tok, "apply_chat_template"):
                messages = []
                if system:
                    messages.append({"role": "system", "content": system})
                messages.append({"role": "user", "content": user})
                return tok.apply_chat_template(messages, tokenize=False, add_generation_prompt=True)
        except Exception:
            pass

    if system:
        return f"[SYSTEM]\n{system}\n\n[USER]\n{user}\n\n[ASSISTANT]\n"
    return f"[USER]\n{user}\n\n[ASSISTANT]\n"


def main():
    parser = argparse.ArgumentParser(description="Sanity-check Mistral Vibe / HF Transformers with Codestral-22B.")
    parser.add_argument("--model", default=DEFAULT_MODEL_ID, help="HF model id (default: Codestral-22B-v0.1)")
    parser.add_argument("--prompt", default="Write a C++ Unreal Engine function that returns the dot product of two FVector values.", help="User prompt")
    parser.add_argument("--system", default="You are a helpful coding assistant. Prefer Unreal Engine C++.", help="Optional system prompt")
    parser.add_argument("--max-new-tokens", type=int, default=256)
    parser.add_argument("--temperature", type=float, default=0.2)
    parser.add_argument("--top-p", type=float, default=0.95)
    parser.add_argument("--load-in-4bit", action="store_true", help="Requires bitsandbytes; useful for 22B on consumer GPUs")
    parser.add_argument("--load-in-8bit", action="store_true", help="Requires bitsandbytes")
    args = parser.parse_args()

    print("Python:", sys.version.replace("\n", " "))

    try:
        import torch
        print("torch:", getattr(torch, '__version__', str(torch)))
        try:
            cuda_avail = torch.cuda.is_available()
            print("cuda_available:", cuda_avail)
            if cuda_avail:
                print("cuda_device_count:", torch.cuda.device_count())
                try:
                    print("cuda_device_name:", torch.cuda.get_device_name(0))
                except Exception as e:
                    print("Could not get device name:", e)
        except Exception as e:
            print("Error checking CUDA:", e)
    except Exception as e:
        print("torch import failed:", e)
        traceback.print_exc()

    try:
        import transformers
        print("transformers:", getattr(transformers, '__version__', str(transformers)))
    except Exception as e:
        print("transformers import failed:", e)
        traceback.print_exc()

    try:
        # try the package import name as the PyPI project (mistral-vibe)
        import vibe as mv
        mv_name = "vibe"
        ver = getattr(mv, "__version__", None)
        print(f"imported {mv_name}:", ver if ver else repr(mv))
    except Exception as e:
        print("vibe import failed:", e)
        traceback.print_exc()

    try:
        import mistralai
        ver = getattr(mistralai, "__version__", None)
        print("mistralai:", ver if ver else repr(mistralai))
    except Exception as e:
        print("mistralai import failed:", e)
        traceback.print_exc()

    # Actual Codestral smoke test: try to generate via HF Transformers.
    try:
        prompt = _build_codestral_prompt(args.model, args.system, args.prompt)
        print("\n--- Generating (transformers) ---")
        text = _generate_with_transformers(
            model_id=args.model,
            prompt=prompt,
            max_new_tokens=args.max_new_tokens,
            temperature=args.temperature,
            top_p=args.top_p,
            load_in_4bit=args.load_in_4bit,
            load_in_8bit=args.load_in_8bit,
        )
        print(text)
    except Exception as e:
        print("Generation failed:", e)
        traceback.print_exc()

if __name__ == '__main__':
    main()
