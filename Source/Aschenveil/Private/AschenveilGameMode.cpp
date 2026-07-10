// Fill out your copyright notice in the Description page of Project Settings.


#include "AschenveilGameMode.h"
#include "Flynn.h"
#include "AschenveilHUD.h"

AAschenveilGameMode::AAschenveilGameMode()
{
    DefaultPawnClass = nullptr;
    HUDClass = AAschenveilHUD::StaticClass();
}


