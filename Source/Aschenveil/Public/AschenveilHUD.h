#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AschenveilHUD.generated.h"

class UHealthComponent;

UCLASS()
class ASCHENVEIL_API AAschenveilHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void DrawHUD() override;

private:

	UHealthComponent* GetFlynnHealth() const;
};

