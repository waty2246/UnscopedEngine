#pragma once

#include"Common.h"
#include"Core/IInitializable.h"

namespace ue
{
	enum class ImageType
	{
		BITMAP
	};

	enum class ImageColorFormat
	{
		UNKNOW,
		R8G8B8A8
	};

	class Image : public IInitializable
	{
	public:
		Image(const char* fileName, ImageType imageType,ImageColorFormat colorFormat);

		/// <summary>
		/// Load image data from the given fileName, imageType and colorFormat
		/// </summary>
		/// <param name="state"></param>
		virtual void Init(uintptr_t state) override;

		ImageColorFormat GetImageColorFormat()const;
		ImageType GetImageType()const;
		const std::string& GetImageFileName()const;
		UINT GetImageWidth()const;
		UINT GetImageHeight()const;
		uint8_t* GetImageData()const;

	private:
		std::tuple<std::unique_ptr<uint8_t[]>, UINT, UINT> LoadBitmapImageData(const char* fileName);

	private:
		bool _hasInit;
		
		const std::string _fileName;
		const ImageType _imageType;
		const ImageColorFormat _colorFormat;
	
		std::unique_ptr<uint8_t[]> _imageData;
		UINT _imageWidth;
		UINT _imageHeight;
	};
}