// Fill out your copyright notice in the Description page of Project Settings.


#include "AschenveilGameMode.h"
#include "Flynn.h"

AAschenveilGameMode::AAschenveilGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> PawnClass(TEXT("/Game/Blueprint/BP_Flynn"));
    if (PawnClass.Succeeded())
    {
        DefaultPawnClass = PawnClass.Class;
    }
}

