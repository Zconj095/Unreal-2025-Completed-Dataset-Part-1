#include "OctitionaryInterpreterComponent.h"
#include <limits>

UOctitionaryInterpreterComponent::UOctitionaryInterpreterComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UOctitionaryInterpreterComponent::ClearAll()
{
    LetterPairs.Reset();
    SymbolPairs.Reset();
    DigitSemantics.Reset();
}

void UOctitionaryInterpreterComponent::AddPairs(const TArray<FOctitionaryPair>& Pairs, bool bLetters)
{
    if (bLetters) { LetterPairs.Append(Pairs); }
    else { SymbolPairs.Append(Pairs); }
}

static void Add(TArray<FOctitionaryPair>& Arr, const TCHAR* K, const TCHAR* V)
{
    FOctitionaryPair P; P.Key = K; P.Value = V; Arr.Add(MoveTemp(P));
}

void UOctitionaryInterpreterComponent::LoadPreset_SongOfTemporalCollaboration()
{
    ClearAll();
    // Letters A..Z
    Add(LetterPairs, TEXT("A"), TEXT("32849"));
    Add(LetterPairs, TEXT("B"), TEXT("G82256"));
    Add(LetterPairs, TEXT("C"), TEXT("372845"));
    Add(LetterPairs, TEXT("D"), TEXT("835e62"));
    Add(LetterPairs, TEXT("E"), TEXT("as375d"));
    Add(LetterPairs, TEXT("F"), TEXT("G89726"));
    Add(LetterPairs, TEXT("G"), TEXT("E42901"));
    Add(LetterPairs, TEXT("H"), TEXT("f34h29"));
    Add(LetterPairs, TEXT("I"), TEXT("K2910m"));
    Add(LetterPairs, TEXT("J"), TEXT("K329fD"));
    Add(LetterPairs, TEXT("K"), TEXT("j56a92"));
    Add(LetterPairs, TEXT("L"), TEXT("32891D"));
    Add(LetterPairs, TEXT("M"), TEXT("869725"));
    Add(LetterPairs, TEXT("N"), TEXT("JU76851"));
    Add(LetterPairs, TEXT("O"), TEXT("Aa3651725"));
    Add(LetterPairs, TEXT("P"), TEXT("J98625*3972851"));
    Add(LetterPairs, TEXT("Q"), TEXT("05821*658231"));
    Add(LetterPairs, TEXT("R"), TEXT("G81256"));
    Add(LetterPairs, TEXT("S"), TEXT("E56a92"));
    Add(LetterPairs, TEXT("T"), TEXT("G8351"));
    Add(LetterPairs, TEXT("U"), TEXT("Tu65391"));
    Add(LetterPairs, TEXT("V"), TEXT("F32fr31"));
    Add(LetterPairs, TEXT("W"), TEXT("095321"));
    Add(LetterPairs, TEXT("X"), TEXT("G681325"));
    Add(LetterPairs, TEXT("Y"), TEXT("F835721"));
    Add(LetterPairs, TEXT("Z"), TEXT("85*66851"));
    // Lowercase a..z
    Add(LetterPairs, TEXT("a"), TEXT("□*8351"));
    Add(LetterPairs, TEXT("b"), TEXT("∞ 3527216"));
    Add(LetterPairs, TEXT("c"), TEXT("846351"));
    Add(LetterPairs, TEXT("d"), TEXT("∞^86513"));
    Add(LetterPairs, TEXT("e"), TEXT("0361*∞(77.651)"));
    Add(LetterPairs, TEXT("f"), TEXT("F321(8651)"));
    Add(LetterPairs, TEXT("g"), TEXT("8651"));
    Add(LetterPairs, TEXT("h"), TEXT("r3285"));
    Add(LetterPairs, TEXT("i"), TEXT("o32051"));
    Add(LetterPairs, TEXT("j"), TEXT("89325"));
    Add(LetterPairs, TEXT("k"), TEXT("000513728"));
    Add(LetterPairs, TEXT("l"), TEXT("3256813"));
    Add(LetterPairs, TEXT("m"), TEXT("6851"));
    Add(LetterPairs, TEXT("n"), TEXT("6yTY5z1"));
    Add(LetterPairs, TEXT("o"), TEXT("9932451"));
    Add(LetterPairs, TEXT("p"), TEXT("∞(L651)"));
    Add(LetterPairs, TEXT("q"), TEXT("Ufh37451"));
    Add(LetterPairs, TEXT("r"), TEXT("000"));
    Add(LetterPairs, TEXT("s"), TEXT("i7325"));
    Add(LetterPairs, TEXT("t"), TEXT("u835fe21"));
    Add(LetterPairs, TEXT("u"), TEXT("85726531"));
    Add(LetterPairs, TEXT("v"), TEXT("ytz281"));
    Add(LetterPairs, TEXT("w"), TEXT("j64981"));
    Add(LetterPairs, TEXT("x"), TEXT("8849326"));
    Add(LetterPairs, TEXT("y"), TEXT("fluxjk821"));
    Add(LetterPairs, TEXT("z"), TEXT("g85321"));

    // Special mapping for circle symbol "○ = A351" is not a single key in input here; skip.
    // Symbols and semantics
    Add(SymbolPairs, TEXT("∞"), TEXT("INF"));
    Add(SymbolPairs, TEXT("□"), TEXT("=="));

    // Digit semantics (documentation only)
    Add(DigitSemantics, TEXT("0"), TEXT("Read"));
    Add(DigitSemantics, TEXT("1"), TEXT("Time"));
    Add(DigitSemantics, TEXT("2"), TEXT("Space"));
    Add(DigitSemantics, TEXT("3"), TEXT("Temporal"));
    Add(DigitSemantics, TEXT("4"), TEXT("Synchronys"));
    Add(DigitSemantics, TEXT("5"), TEXT("J46a9(Server)"));
    Add(DigitSemantics, TEXT("6"), TEXT("Collaborate"));
    Add(DigitSemantics, TEXT("7"), TEXT("Calibrate"));
    Add(DigitSemantics, TEXT("8"), TEXT("Setttings"));
    Add(DigitSemantics, TEXT("9"), TEXT("Joint"));
}

FOctitionaryEvaluation UOctitionaryInterpreterComponent::Evaluate(const FString& Formula)
{
    FOctitionaryEvaluation Out;
    Out.Expanded = ExpandFormula(Formula);

    double Num = 0.0; bool bOk = TryEvalArithmetic(Out.Expanded, Num);
    Out.bHasNumericValue = bOk; Out.NumericValue = Num;
    Out.BinaryBits = ToBinaryBits(Out.Expanded);
    Out.Hash64 = HashFNV1a64(Out.Expanded);
    Out.HashHex = FString::Printf(TEXT("%016llX"), (unsigned long long)Out.Hash64);
    return Out;
}

FString UOctitionaryInterpreterComponent::ExpandFormula(const FString& In) const
{
    FString S = In;
    // Replace letter pairs (longest keys first to avoid partial overlaps)
    TArray<FOctitionaryPair> All = LetterPairs; All.Append(SymbolPairs);
    All.Sort([](const FOctitionaryPair& A, const FOctitionaryPair& B){ return A.Key.Len() > B.Key.Len(); });
    for (const FOctitionaryPair& P : All)
    {
        if (!P.Key.IsEmpty())
        {
            S = S.Replace(*P.Key, *P.Value, ESearchCase::CaseSensitive);
        }
    }
    return S;
}

// Simple shunting-yard evaluator with support for + - * / ^, parentheses, and INF, and == (returns 1 or 0)
static bool Tokenize(const FString& In, TArray<FString>& Toks)
{
    int32 i = 0; const int32 n = In.Len();
    while (i < n)
    {
        TCHAR c = In[i];
        if (FChar::IsWhitespace(c)) { ++i; continue; }
        if (FChar::IsDigit(c) || c == TEXT('.') )
        {
            int32 j = i+1; while (j<n && (FChar::IsDigit(In[j]) || In[j]==TEXT('.'))) ++j;
            Toks.Add(In.Mid(i, j-i)); i=j; continue;
        }
        if (FChar::IsAlpha(c))
        {
            int32 j=i+1; while (j<n && FChar::IsAlpha(In[j])) ++j;
            Toks.Add(In.Mid(i, j-i)); i=j; continue;
        }
        if (c==TEXT('(') || c==TEXT(')') || c==TEXT('+') || c==TEXT('-') || c==TEXT('*') || c==TEXT('/') || c==TEXT('^'))
        {
            FString One; One.Reserve(1); One.AppendChar(c);
            Toks.Add(MoveTemp(One));
            ++i; continue;
        }
        if (c==TEXT('='))
        {
            if (i+1<n && In[i+1]==TEXT('=')) { Toks.Add(TEXT("==")); i+=2; continue; }
        }
        // unknown token, skip
        ++i;
    }
    return true;
}

static int Prec(const FString& op){ if(op=="==") return 0; if(op=="+") return 1; if(op=="-") return 1; if(op=="*") return 2; if(op=="/") return 2; if(op=="^") return 3; return -1; }
static bool RightAssoc(const FString& op){ return op=="^"; }

bool UOctitionaryInterpreterComponent::TryEvalArithmetic(const FString& In, double& Out) const
{
    // Replace INF with a large constant
    FString S = In; S = S.Replace(TEXT("INF"), TEXT("1e309"), ESearchCase::CaseSensitive); // -> inf in double parse
    TArray<FString> T; Tokenize(S, T);
    TArray<FString> output; TArray<FString> ops;
    for (int i=0;i<T.Num();++i)
    {
        const FString& tok = T[i];
        if (tok.Len()>0 && (FChar::IsDigit(tok[0]) || tok[0]=='.')) { output.Add(tok); continue; }
        if (FChar::IsAlpha(tok[0])) { return false; } // contains symbol -> not purely numeric
        if (tok=="(") { ops.Add(tok); continue; }
        if (tok==")") { while(ops.Num()>0 && ops.Last()!="(") { output.Add(ops.Pop()); } if (ops.Num()==0) return false; ops.Pop(); continue; }
        // operator
        while(ops.Num()>0 && Prec(ops.Last())>=0 && ( (RightAssoc(tok) && Prec(ops.Last())>Prec(tok)) || (!RightAssoc(tok) && Prec(ops.Last())>=Prec(tok)) ))
        { output.Add(ops.Pop()); }
        ops.Add(tok);
    }
    while(ops.Num()>0){ if(ops.Last()=="("||ops.Last()==")") return false; output.Add(ops.Pop()); }
    // eval RPN
    TArray<double> st;
    for (const FString& tok : output)
    {
        if (tok.Len()>0 && (FChar::IsDigit(tok[0]) || tok[0]=='.')) { st.Add(FCString::Atod(*tok)); continue; }
        if (tok=="==") { if (st.Num()<2) return false; double b=st.Pop(); double a=st.Pop(); st.Add( a==b ? 1.0 : 0.0 ); continue; }
        if (st.Num()<2) return false; double b=st.Pop(); double a=st.Pop();
        if (tok=="+") st.Add(a+b); else if (tok=="-") st.Add(a-b); else if (tok=="*") st.Add(a*b); else if (tok=="/") st.Add(a/b); else if (tok=="^") st.Add(FMath::Pow(a,b)); else return false;
    }
    if (st.Num()!=1) return false; Out = st[0]; return true;
}

FString UOctitionaryInterpreterComponent::ToBinaryBits(const FString& In)
{
    FTCHARToUTF8 U8(*In);
    const ANSICHAR* Data = U8.Get();
    const int32 Len = U8.Length();
    FString Bits; Bits.Reserve(Len*8);
    for (int32 i=0; i<Len; ++i)
    {
        uint8 b = (uint8)Data[i];
        for (int k=7; k>=0; --k)
        {
            Bits.AppendChar(((b>>k)&1) ? '1' : '0');
        }
    }
    return Bits;
}

uint64 UOctitionaryInterpreterComponent::HashFNV1a64(const FString& In)
{
    const uint64 FNV_offset = 1469598103934665603ULL; const uint64 FNV_prime = 1099511628211ULL;
    uint64 h = FNV_offset; FTCHARToUTF8 U8(*In);
    const ANSICHAR* Data = U8.Get();
    const int32 Len = U8.Length();
    for (int32 i=0; i<Len; ++i) { h ^= (uint8)Data[i]; h *= FNV_prime; }
    return h;
}
