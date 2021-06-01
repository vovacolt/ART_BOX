// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/Texture2DDynamic.h"

#include "BFL_ART_BOX.generated.h"

USTRUCT(BlueprintType, Category = "Structure")
struct FUserStruct
{
	GENERATED_USTRUCT_BODY()
		FUserStruct() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
		int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
		int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
		FString Author;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
		FString Age;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
		FString URL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
		bool Ready_To_Use;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structure")
		//int32 nIsLoginCorrect = 0; // 0 - undefined, -1 - invalid, 1 - valid
};

/**
 * 
 */
UCLASS()
class ART_BOX_CODE_API UBFL_ART_BOX : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Texture2DDynamic")
		static int32 GetTexture2DDynamicWidth(UTexture2DDynamic* InTexture2DDynamicReference);

	UFUNCTION(BlueprintCallable, Category = "Texture2DDynamic")
		static int32 GetTexture2DDynamicHight(UTexture2DDynamic* InTexture2DDynamicReference);
};
