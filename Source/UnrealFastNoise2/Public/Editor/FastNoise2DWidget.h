#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "FastNoise2/FastNoise2Generators.h"
#include "FastNoise2DWidget.generated.h"

UCLASS(Abstract)
class UNREALFASTNOISE2_API UFastNoise2DWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> NoiseImage;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UTexture2D> NoiseTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint NoiseImageSize = FIntPoint(1024, 1024);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Frequency = 0.05f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Seed;
	
	virtual void NativePreConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void GenerateFastNoise(UFastNoise2GeneratorBase*& InSource);
};
