// Fill out your copyright notice in the Description page of Project Settings.


#include "CM_ART_BOX_DB.h"

// Sets default values for this component's properties
UCM_ART_BOX_DB::UCM_ART_BOX_DB()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}

// Called when the game starts
void UCM_ART_BOX_DB::BeginPlay()
{
	Super::BeginPlay();

	// we get the tcp component
	//this->vPlayerCtrl = (ATopDown1PlayerController *)GetWorld()->GetFirstPlayerController();
	//this->vNodeSocketCmp = this->vPlayerCtrl->vNodeSocketCmp;

	//this->vGameMode = (ATopDown1GameMode *)GetWorld()->GetAuthGameMode();
	//this->vNodeSocketCmp = this->vGameMode->vNodeSocketCmp;


	this->vNodeSocketCmp->OnReceivedStr.AddDynamic(this, &UCM_ART_BOX_DB::fOnServerMsgClb);


}


// Called every frame
void UCM_ART_BOX_DB::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



bool UCM_ART_BOX_DB::fOnUserLoginReq(int32 ID, FGuid widget_id)
{
	// we form a request to the server
	TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);

	request->SetStringField("sClientToken", FString(TEXT("")));
	request->SetStringField("sRoute", FString(TEXT("id_req")));

	data->SetStringField("id", FString::FromInt(ID));
	data->SetStringField("widget_id", widget_id.ToString());

	request->SetObjectField("data", data);

	FString requestStr;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&requestStr);
	FJsonSerializer::Serialize(request.ToSharedRef(), Writer);

	// send request
	return this->vNodeSocketCmp->EmitStr(requestStr);

}

bool UCM_ART_BOX_DB::fOnCountReq()
{
	// we form a request to the server
	TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);

	request->SetStringField("sClientToken", FString(TEXT("")));
	request->SetStringField("sRoute", FString(TEXT("count_req")));

	//data->SetStringField("id", FString::FromInt(ID));

	//request->SetObjectField("data", data);

	FString requestStr;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&requestStr);
	FJsonSerializer::Serialize(request.ToSharedRef(), Writer);

	// send request
	return this->vNodeSocketCmp->EmitStr(requestStr);

}

void UCM_ART_BOX_DB::fOnUserLoginResp(FString msg)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("fOnUserLoginResp"));

	bool bRespOk = fIsMsgOk(msg);

	FUserStruct CurArtInfo;
	// parsing response from server

	// check the correctness of the answer
	if (bRespOk)
	{
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(msg);
		TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
		FJsonSerializer::Deserialize(JsonReader, request);

		TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
		TSharedPtr<FJsonObject> user = MakeShareable(new FJsonObject);

		data = request->GetObjectField("data");
		user = data->GetObjectField("art");

		FString str_widget_id = user->GetStringField("widget_id");
		FGuid widget_id;
		FGuid::Parse(str_widget_id, widget_id);

		//UserDataMap.Add()

		CurArtInfo.Count = user->GetIntegerField("count");
		CurArtInfo.ID = user->GetIntegerField("id");
		CurArtInfo.Name = user->GetStringField("name");
		CurArtInfo.Author = user->GetStringField("author");
		CurArtInfo.Age = user->GetStringField("age");
		CurArtInfo.Description = user->GetStringField("description");
		CurArtInfo.URL = user->GetStringField("url");
		CurArtInfo.Ready_To_Use = true;

		UserDataMap.Add(widget_id, CurArtInfo);

		Info_Received = true;
		//UserData.nIsLoginCorrect = 1;
	}
	else
	{
		CurArtInfo.Ready_To_Use = false;

		Info_Received = false;
		//UserData.nIsLoginCorrect = -1;
	}

	onUserLoginEvent.Broadcast(bRespOk);
}

void UCM_ART_BOX_DB::fOnCountResp(FString msg)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("fOnUserLoginResp"));

	bool bRespOk = fIsMsgOk(msg);

	// parsing response from server

	// check the correctness of the answer
	if (bRespOk)
	{
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(msg);
		TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
		FJsonSerializer::Deserialize(JsonReader, request);

		TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
		TSharedPtr<FJsonObject> user = MakeShareable(new FJsonObject);

		data = request->GetObjectField("data");
		user = data->GetObjectField("count");

		Count_DB = user->GetIntegerField("count");

		Info_Received = true;
	}
	else
	{
		Info_Received = false;
	}

	onUserLoginEvent.Broadcast(bRespOk);
}

bool UCM_ART_BOX_DB::fIsMsgOk(const FString& msg)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(msg);
	TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
	FJsonSerializer::Deserialize(JsonReader, request);

	bool out = false;
	request->TryGetBoolField(TEXT("ok"), out);

	return out;

}

FString UCM_ART_BOX_DB::fGetRouteFromMsg(const FString& msg)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(msg);
	TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
	FJsonSerializer::Deserialize(JsonReader, request);

	FString out;
	request->TryGetStringField("sRoute", out);

	return out;
}


// от серевера пришло сообщение
void UCM_ART_BOX_DB::fOnServerMsgClb(const FString& pMsg)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, *pMsg);

	// маршрут сообщения
	FString sRoute = fGetRouteFromMsg(pMsg);

	if (sRoute == "id_resp")
	{
		fOnUserLoginResp(pMsg);
	}
	else if (sRoute == "count_resp")
	{
		fOnCountResp(pMsg);
	}
}