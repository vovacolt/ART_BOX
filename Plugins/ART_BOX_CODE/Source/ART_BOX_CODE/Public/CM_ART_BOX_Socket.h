// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GeneratedCodeHelpers.h"
#include "Async/Async.h"

#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Networking.h"

#include "IPAddress.h"
#include "JsonObjectConverter.h"

#include "HAL/ThreadSafeBool.h"

#include "BFL_ART_BOX.h"

#include "CM_ART_BOX_Socket.generated.h"

typedef TSharedPtr<FString, ESPMode::ThreadSafe> FStringReaderPtr;

// when there was a connection to the server
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNetEventS);

// when did you get the bytes
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNetMsgEvent, const TArray<uint8>&, Bytes);

// 
// when did you get the string
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNetMsgEventStr, const  FString&, Msg);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ART_BOX_CODE_API UCM_ART_BOX_Socket : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCM_ART_BOX_Socket();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// ��� ����� �����������
	FSocket* ClientSocket;

	// can receive data safe for thread
	FThreadSafeBool bShouldReceiveData;

	// 
	TFuture<void> ClientConnectionFinishedFuture;

	// server address
	TSharedPtr<FInternetAddr> RemoteAdress;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	// received bytes from the server
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
		FNetMsgEvent OnReceivedBytes;

	// received a line from the server
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
		FNetMsgEventStr OnReceivedStr;

	// runs when connected to the server
	FNetEventS OnConnected;


	/**
	 * Converts bytes to string
	 */
	FString fBytesToString(const TArray<uint8>& InArray);


	/**
	 * Converts string to bytes
	 */
	TArray<uint8> fStringToBytes(FString InString);



	// connection name
	FString ClientSocketName;

	// buffer size in bytes
	int32 BufferMaxSize;

	// sign that connected
	UPROPERTY(BluePrintReadWrite, Category = "AA")
	bool bIsConnected;


	/**
	 * Connects over TCP to the server
	 *
	 * @param InIP ip4 address where we connect
	 * @param InPort TCP connection port
	 */
	UFUNCTION(BlueprintCallable, Category = "AA")
		void ConnectToServer(const FString& InIP = TEXT("127.0.0.1"), const int32 InPort = 3000, const bool ByDomain = true);

	/**
	 * Closes the connection
	 */
	UFUNCTION(BlueprintCallable, Category = "AA")
		void CloseSocket();

	/**
	 * Sends bytes to the server
	 *
	 * @param Message	Bytes
	 */
	UFUNCTION(BlueprintCallable, Category = "AA")
		bool Emit(const TArray<uint8>& Bytes);

	/**
	 * Sends a string to the server
	 *
	 * @param Message	Bytes
	 */
	UFUNCTION(BlueprintCallable, Category = "AA")
		bool EmitStr(const FString& str);

	// ----------------------------------------------

	void fTestP();
};
