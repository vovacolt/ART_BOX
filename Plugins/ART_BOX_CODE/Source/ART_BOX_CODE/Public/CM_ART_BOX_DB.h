// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "CM_ART_BOX_DB.h"
#include "CM_ART_BOX_Socket.h"

#include "JsonObjectConverter.h"

#include "CM_ART_BOX_DB.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUserLoginEvent, bool, bStatus);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ART_BOX_CODE_API UCM_ART_BOX_DB : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCM_ART_BOX_DB();

	// server connection component
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AA_Net")
		UCM_ART_BOX_Socket* vNodeSocketCmp;

	/**
	 * callback - called when a message has arrived from the server
	 * and sent to the appropriate handler
	*/
	UFUNCTION(BlueprintCallable, Category = "AA")
		void fOnServerMsgClb(const  FString& msg);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * check if everything is ok in the message
	*/
	bool fIsMsgOk(const FString& msg);

	/**
	 * Get route from server message
	 **/
	FString fGetRouteFromMsg(const FString& msg);



	// ----------------------------------------
	//				Router

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, Category = "AA_User")
		FUserLoginEvent onUserLoginEvent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AA_User")
		bool Info_Received;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AA_User")
		int32 Count_DB;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AA_User")
		FUserStruct UserData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AA_User")
		TMap<FGuid,FUserStruct> UserDataMap;

	// login to server
	UFUNCTION(BlueprintCallable, Category = "AA_User")
		bool fOnUserLoginReq(int32 ID, FGuid widget_id);

	UFUNCTION(BlueprintCallable, Category = "AA_User")
		bool fOnCountReq();

	// callback - from the server at login
	UFUNCTION(BlueprintCallable, Category = "AA_User")
		void fOnUserLoginResp(FString msg);

	UFUNCTION(BlueprintCallable, Category = "AA_User")
		void fOnCountResp(FString msg);


};
