// Fill out your copyright notice in the Description page of Project Settings.


#include "BFL_ART_BOX.h"

int32 UBFL_ART_BOX::GetTexture2DDynamicWidth(UTexture2DDynamic* InTexture2DDynamicReference)
{
    if (!InTexture2DDynamicReference)
    {
        return -1;
    }

    return InTexture2DDynamicReference->SizeX;
}

int32 UBFL_ART_BOX::GetTexture2DDynamicHight(UTexture2DDynamic* InTexture2DDynamicReference)
{
    if (!InTexture2DDynamicReference)
    {
        return -1;
    }

    return InTexture2DDynamicReference->SizeY;
}