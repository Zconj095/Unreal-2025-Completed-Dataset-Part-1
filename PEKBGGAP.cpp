// Copyright Epic Games, Inc. All Rights Reserved.

#include "PEKBGGAP.h"
#include "Modules/ModuleManager.h"
#include "ShaderCore.h"
#include "Misc/Paths.h"

#if WITH_EDITOR
#include "ToolMenus.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Framework/Docking/TabManager.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/SWindow.h"
#endif

class FPEKBGGAPModule final : public FDefaultGameModuleImpl
{
public:
    virtual void StartupModule() override
    {
        // Map a virtual shader directory to this module's Private/Shaders path
        {
            const FString ShaderDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Source"), TEXT("PEKBGGAP"), TEXT("Private"), TEXT("Shaders"));
            if (FPaths::DirectoryExists(ShaderDir))
            {
                AddShaderSourceDirectoryMapping(TEXT("/PEKBGGAP"), ShaderDir);
            }
        }
#if WITH_EDITOR
        if (UToolMenus::IsToolMenuUIEnabled())
        {
            UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FPEKBGGAPModule::RegisterMenus));
        }
#endif
    }

    virtual void ShutdownModule() override
    {
#if WITH_EDITOR
        if (UToolMenus::IsToolMenuUIEnabled())
        {
            UToolMenus::UnRegisterStartupCallback(this);
            if (UToolMenus* Menus = UToolMenus::Get())
            {
                Menus->RemoveMenu("LevelEditor.MainMenu.Tools.LLMHelper");
            }
        }
#endif
    }

#if WITH_EDITOR
private:
    class SLLMHelperWidget : public SCompoundWidget
    {
    public:
        SLATE_BEGIN_ARGS(SLLMHelperWidget) {}
        SLATE_END_ARGS()

        void Construct(const FArguments&)
        {
            ChildSlot
            [
                SNew(SBorder)
                [
                    SNew(SVerticalBox)
                    + SVerticalBox::Slot().AutoHeight().Padding(4)
                    [
                        SNew(STextBlock).Text(FText::FromString(TEXT("LLM Integration")))
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(4)
                    [
                        SNew(SHorizontalBox)
                        + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0,0,8,0)
                        [
                            SNew(STextBlock).Text(FText::FromString(TEXT("Temperature")))
                        ]
                        + SHorizontalBox::Slot().AutoWidth()
                        [
                            SAssignNew(TemperatureSpin, SSpinBox<float>)
                            .MinValue(0.0f)
                            .MaxValue(2.0f)
                            .Delta(0.05f)
                            .Value(0.7f)
                        ]
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(4)
                    [
                        SNew(SHorizontalBox)
                        + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0,0,8,0)
                        [
                            SNew(STextBlock).Text(FText::FromString(TEXT("Batch Size")))
                        ]
                        + SHorizontalBox::Slot().AutoWidth()
                        [
                            SAssignNew(BatchSizeSpin, SSpinBox<int32>)
                            .MinValue(1)
                            .MaxValue(1024)
                            .Delta(1)
                            .Value(1)
                        ]
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(4)
                    [
                        SNew(SHorizontalBox)
                        + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0,0,8,0)
                        [
                            SNew(STextBlock).Text(FText::FromString(TEXT("Context Size")))
                        ]
                        + SHorizontalBox::Slot().AutoWidth()
                        [
                            SAssignNew(ContextSizeSpin, SSpinBox<int32>)
                            .MinValue(128)
                            .MaxValue(65536)
                            .Delta(128)
                            .Value(4096)
                        ]
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(4)
                    [
                        SNew(SHorizontalBox)
                        + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0,0,8,0)
                        [
                            SNew(STextBlock).Text(FText::FromString(TEXT("GPU Layers")))
                        ]
                        + SHorizontalBox::Slot().AutoWidth()
                        [
                            SAssignNew(GPULayersSpin, SSpinBox<int32>)
                            .MinValue(0)
                            .MaxValue(200)
                            .Delta(1)
                            .Value(0)
                        ]
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(4)
                    [
                        SAssignNew(PromptBox, SEditableTextBox).Text(FText::FromString(TEXT("Describe your problem...")))
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(4)
                    [
                        SNew(SButton)
                        .Text(FText::FromString(TEXT("Send to LLM")))
                        .OnClicked(this, &SLLMHelperWidget::OnSendClicked)
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(4)
                    [
                        SAssignNew(ResponseText, STextBlock).Text(FText::FromString(TEXT("")))
                    ]
                ]
            ];
        }

    private:
        FReply OnSendClicked()
        {
            const FString Prompt = PromptBox.IsValid() ? PromptBox->GetText().ToString() : FString();
            const float Temp = TemperatureSpin.IsValid() ? TemperatureSpin->GetValue() : 0.7f;
            const int32 Batch = BatchSizeSpin.IsValid() ? BatchSizeSpin->GetValue() : 1;
            const int32 Ctx = ContextSizeSpin.IsValid() ? ContextSizeSpin->GetValue() : 4096;
            const int32 Gpu = GPULayersSpin.IsValid() ? GPULayersSpin->GetValue() : 0;
            const FString Simulated = FString::Printf(TEXT("Response (temp %.2f, batch %d, ctx %d, gpu %d) to: %s"), Temp, Batch, Ctx, Gpu, *Prompt);
            if (ResponseText.IsValid())
            {
                ResponseText->SetText(FText::FromString(Simulated));
            }
            return FReply::Handled();
        }

    private:
        TSharedPtr<SEditableTextBox> PromptBox;
        TSharedPtr<STextBlock> ResponseText;
        TSharedPtr<SSpinBox<float>> TemperatureSpin;
        TSharedPtr<SSpinBox<int32>> BatchSizeSpin;
        TSharedPtr<SSpinBox<int32>> ContextSizeSpin;
        TSharedPtr<SSpinBox<int32>> GPULayersSpin;
    };

    void OpenLLMHelperWindow()
    {
        TSharedRef<SWindow> Window = SNew(SWindow)
            .Title(FText::FromString(TEXT("LLM Helper")))
            .ClientSize(FVector2D(480, 200))
            .SupportsMinimize(false)
            .SupportsMaximize(false);

        Window->SetContent(SNew(SLLMHelperWidget));
        FSlateApplication::Get().AddWindow(Window);
    }

    void RegisterMenus()
    {
        UToolMenu* ToolsMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
        FToolMenuSection& Section = ToolsMenu->AddSection("LLMHelperSection", FText::FromString(TEXT("LLM")));
        Section.AddMenuEntry(
            "OpenLLMHelper",
            FText::FromString(TEXT("LLM Helper")),
            FText::FromString(TEXT("Open the LLM Helper window.")),
            FSlateIcon(),
            FUIAction(FExecuteAction::CreateRaw(this, &FPEKBGGAPModule::OpenLLMHelperWindow))
        );
    }
#endif
};

IMPLEMENT_PRIMARY_GAME_MODULE(FPEKBGGAPModule, PEKBGGAP, "PEKBGGAP");
