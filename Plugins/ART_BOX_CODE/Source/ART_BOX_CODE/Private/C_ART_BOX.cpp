// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ART_BOX.h"

AC_ART_BOX::AC_ART_BOX()
{
	// node connector
	this->vNodeSocketCmp = CreateDefaultSubobject<UCM_ART_BOX_Socket>(TEXT("UNodeSocketCmp"));

	// DB component
	this->vUDBComp = CreateDefaultSubobject<UCM_ART_BOX_DB>(TEXT("UDBComp"));
	this->vUDBComp->vNodeSocketCmp = vNodeSocketCmp;
}

// Called when the game starts
void AC_ART_BOX::BeginPlay()
{
	Super::BeginPlay();
	// connecting to server
	this->vNodeSocketCmp->ConnectToServer(*(sServerAddress), nServerPort);
}

void AC_ART_BOX::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	// disconect from server
	this->vNodeSocketCmp->CloseSocket();
}