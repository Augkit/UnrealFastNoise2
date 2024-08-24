#include "Editor/FastNoise2DWidget.h"

void UFastNoise2DWidget::NativePreConstruct()
{
	if (NoiseImage)
	{
		UFastNoise2GeneratorBase* FastNoise = nullptr;
		GenerateFastNoise(FastNoise);
		if (FastNoise)
		{
			NoiseTexture = UTexture2D::CreateTransient(NoiseImageSize.X, NoiseImageSize.Y, EPixelFormat::PF_R32_FLOAT);
			check(NoiseTexture);
			NoiseTexture->bNotOfflineProcessed = true;
			NoiseTexture->SRGB = false;
			NoiseTexture->LODGroup = TEXTUREGROUP_RenderTarget;
			NoiseTexture->CompressionSettings = TC_SingleFloat;
			TArray<float> PixelValues;
			FastNoise->GenUniformGrid2D(PixelValues, FIntPoint::ZeroValue, NoiseImageSize, Frequency, Seed);
			uint8* MipData = static_cast<uint8*>(NoiseTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
			check(MipData != nullptr);
			FMemory::Memmove(MipData, PixelValues.GetData(), PixelValues.Num() * PixelValues.GetTypeSize());
			NoiseTexture->GetPlatformData()->Mips[0].BulkData.Unlock();
			NoiseTexture->UpdateResource();
			FSlateBrush NoiseImageBrush = NoiseImage->GetBrush();
			NoiseImageBrush.SetResourceObject(NoiseTexture);
			NoiseImage->SetBrush(NoiseImageBrush);
		}
	}

	Super::NativePreConstruct();
}
