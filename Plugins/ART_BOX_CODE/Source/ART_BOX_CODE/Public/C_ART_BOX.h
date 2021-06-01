// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "CM_ART_BOX_DB.h"
#include "CM_ART_BOX_Socket.h"

#include "C_ART_BOX.generated.h"

/**
 * 
 */
UCLASS()
class ART_BOX_CODE_API AC_ART_BOX : public APlayerController
{
	GENERATED_BODY()

public:

	AC_ART_BOX();

	// --------------------------------------------
	//					Network

	UPROPERTY(BluePrintReadWrite, Category = "AA_Net")
		UCM_ART_BOX_Socket* vNodeSocketCmp;

	UPROPERTY(BluePrintReadWrite, Category = "AA_Net")
		FString sServerAddress = TEXT("vovacolt.asuscomm.com");

	UPROPERTY(BluePrintReadWrite, Category = "AA_Net")
		int32 nServerPort = 3008;


	// --------------------------------------------
	//					DB
	UPROPERTY(BluePrintReadWrite, Category = "AA_DB")
		UCM_ART_BOX_DB* vUDBComp;

protected:

	// Begin PlayerController interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
