// Copyright 2007-2017 Simul Software Ltd.. All Rights Reserved.

#include "TrueSkyLight.h"

#include "TrueSkyPluginPrivatePCH.h"

#include "TrueSkyLightComponent.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BillboardComponent.h"

#define LOCTEXT_NAMESPACE "TrueSkyLight"

ATrueSkyLight::ATrueSkyLight(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	LightComponent = CreateDefaultSubobject<UTrueSkyLightComponent>(TEXT("SkyLightComponent0"));
	RootComponent = LightComponent;
	
	RootComponent->Mobility = EComponentMobility::Movable;
#if WITH_EDITORONLY_DATA
	if (!IsRunningCommandlet())
	{
		// Structure to hold one-time initialization
		struct FConstructorStatics
		{
				ConstructorHelpers::FObjectFinderOptional<UTexture2D> SkyLightTextureObject;
			FName ID_Sky;
			FText NAME_Sky;

			FConstructorStatics()
					: SkyLightTextureObject(TEXT("/Engine/EditorResources/LightIcons/SkyLight"))
					, ID_Sky(TEXT("Sky"))
				, NAME_Sky(NSLOCTEXT( "SpriteCategory", "Sky", "Sky" ))
			{
			}
		};
		static FConstructorStatics ConstructorStatics;

		if (GetSpriteComponent())
		{
			GetSpriteComponent()->Sprite = ConstructorStatics.SkyLightTextureObject.Get();
			GetSpriteComponent()->SpriteInfo.Category = ConstructorStatics.ID_Sky;
			GetSpriteComponent()->SpriteInfo.DisplayName = ConstructorStatics.NAME_Sky;
			GetSpriteComponent()->SetupAttachment( LightComponent);
		}
	}
#endif // WITH_EDITORONLY_DATA
}

void ATrueSkyLight::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( ATrueSkyLight, bEnabled ); 
}

void ATrueSkyLight::OnRep_bEnabled()
{
	LightComponent->SetVisibility(bEnabled);
}


UTrueSkyLightComponent* ATrueSkyLight::GetLightComponent() const { return LightComponent; }

#undef LOCTEXT_NAMESPACE