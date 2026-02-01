#include "MatrixSerialCode.h"

AMatrixSerialCode::AMatrixSerialCode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixSerialCode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Matrix Serial Code System Initialized."));
}

void AMatrixSerialCode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Increment timers
    AddEntryTimer += DeltaSeconds;
    SearchWordTimer += DeltaSeconds;
    SearchCodeTimer += DeltaSeconds;
    RetrieveEntriesTimer += DeltaSeconds;

    // Automate adding entries
    if (AddEntryTimer >= AddEntryInterval)
    {
        const int32 RandWord = FMath::RandRange(1, 100);
        const int32 RandA = FMath::RandRange(1000, 9999);
        const int32 RandB = FMath::RandRange(100, 999);
        const FString RandomWord = FString::Printf(TEXT("Word_%d"), RandWord);
        const FString RandomCode = FString::Printf(TEXT("s%d.x%d"), RandA, RandB);
        AddWordWithSerialCode(RandomWord, RandomCode);
        AddEntryTimer = 0.f;
    }

    // Automate searching for a word
    if (SearchWordTimer >= SearchWordInterval && SerialCodeDatabase.Num() > 0)
    {
        for (const TPair<FString, FSerialCodeEntry>& Pair : SerialCodeDatabase)
        {
            SearchWord(Pair.Value.Word);
            break; // Use the first available word for testing
        }
        SearchWordTimer = 0.f;
    }

    // Automate searching for a serial code
    if (SearchCodeTimer >= SearchCodeInterval && SerialCodeDatabase.Num() > 0)
    {
        for (const TPair<FString, FSerialCodeEntry>& Pair : SerialCodeDatabase)
        {
            SearchSerialCode(Pair.Value.SerialCode);
            break; // Use the first available code for testing
        }
        SearchCodeTimer = 0.f;
    }

    // Automate retrieving all entries
    if (RetrieveEntriesTimer >= RetrieveEntriesInterval)
    {
        RetrieveAllEntries();
        RetrieveEntriesTimer = 0.f;
    }
}

void AMatrixSerialCode::AddWordWithSerialCode(const FString& Word, const FString& SerialCode)
{
    const FString LowerWord = Word.ToLower();
    if (SerialCodeDatabase.Contains(LowerWord))
    {
        UE_LOG(LogTemp, Warning, TEXT("Word '%s' already exists in the database."), *Word);
        return;
    }

    FSerialCodeEntry Entry(Word, SerialCode);
    SerialCodeDatabase.Add(LowerWord, MoveTemp(Entry));
    UE_LOG(LogTemp, Log, TEXT("Added Word: '%s', Serial Code: '%s'"), *Word, *SerialCode);
}

FString AMatrixSerialCode::SearchWord(const FString& Word) const
{
    const FString LowerWord = Word.ToLower();
    if (const FSerialCodeEntry* Found = SerialCodeDatabase.Find(LowerWord))
    {
        UE_LOG(LogTemp, Log, TEXT("Word Found: '%s', Serial Code: '%s'"), *Word, *Found->SerialCode);
        return Found->SerialCode;
    }

    UE_LOG(LogTemp, Warning, TEXT("Word '%s' not found in the database."), *Word);
    return FString();
}

FString AMatrixSerialCode::SearchSerialCode(const FString& SerialCode) const
{
    for (const TPair<FString, FSerialCodeEntry>& Pair : SerialCodeDatabase)
    {
        if (Pair.Value.SerialCode == SerialCode)
        {
            UE_LOG(LogTemp, Log, TEXT("Serial Code Found: '%s', Word: '%s'"), *SerialCode, *Pair.Value.Word);
            return Pair.Value.Word;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Serial Code '%s' not found in the database."), *SerialCode);
    return FString();
}

void AMatrixSerialCode::RetrieveAllEntries() const
{
    UE_LOG(LogTemp, Log, TEXT("Retrieving all words and serial codes..."));
    for (const TPair<FString, FSerialCodeEntry>& Pair : SerialCodeDatabase)
    {
        const FSerialCodeEntry& Entry = Pair.Value;
        UE_LOG(LogTemp, Log, TEXT("Word: '%s', Serial Code: '%s'"), *Entry.Word, *Entry.SerialCode);
    }
}

