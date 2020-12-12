#include "Image.h"

namespace ue
{
	Image::Image(const char* fileName, ImageType imageType, ImageColorFormat colorFormat):
		_hasInit(false),
		_fileName(fileName),
		_imageType(imageType),
		_colorFormat(colorFormat),
		_imageData(),
		_imageWidth(0),
		_imageHeight(0)
	{
	}

	void Image::Init(uintptr_t state)
	{
		if (_hasInit)
		{
			return;
		}
		_hasInit = true;

		if (ImageType::BITMAP == _imageType)
		{
			std::tie(_imageData, _imageWidth, _imageHeight) = this->LoadBitmapImageData(_fileName.c_str());
		}
		else
		{
			LOGMSG("Unsupported image type.", 0);
		}
	}

	ImageColorFormat Image::GetImageColorFormat() const
	{
		return _colorFormat;
	}

	ImageType Image::GetImageType() const
	{
		return _imageType;
	}

	const std::string& Image::GetImageFileName() const
	{
		return _fileName;
	}

	UINT Image::GetImageWidth() const
	{
		return _imageWidth;
	}

	UINT Image::GetImageHeight() const
	{
		return _imageHeight;
	}

	uint8_t* Image::GetImageData() const
	{
		return _imageData.get();
	}

	std::tuple<std::unique_ptr<unsigned char[]>, UINT, UINT> Image::LoadBitmapImageData(const char* fileName)
	{
		std::ifstream in(fileName, std::ios::in | std::ios::binary);
		std::stringstream buf;
		buf << in.rdbuf();

		auto data = buf.str();
		auto dataPtr = reinterpret_cast<const unsigned char*>(data.c_str());

		auto bitmapHeader = reinterpret_cast<const BITMAPFILEHEADER*>(dataPtr);
		auto bitmapInfo = reinterpret_cast<const BITMAPINFOHEADER*>(dataPtr + sizeof(BITMAPFILEHEADER));

		if (bitmapHeader->bfType != 0x4D42)
		{
			LOGMSG("Image is not bitmap type.", 0);
		}

		if (bitmapInfo->biBitCount != 24 || bitmapInfo->biCompression != BI_RGB)
		{
			LOGMSG("Image is not 24-bit color format.", 0);
		}

		//bitmap row size must be multiple of four.
		auto imageData = dataPtr + bitmapHeader->bfOffBits;
		size_t bitmapHeight = std::abs(bitmapInfo->biHeight);
		size_t bitmapWidth = bitmapInfo->biWidth;
		size_t indexTextureData = 0;
		size_t rowSize = bitmapWidth * 3;
		UINT padding = (4 - rowSize % 4) & 0x03;
		rowSize += padding;

		auto bitmapSize = rowSize * bitmapHeight;
		std::unique_ptr<uint8_t[]> textureData{};

		//Bottom - Left else Top - Left.
		auto bottomLeft = false;
		if (bitmapInfo->biHeight > 0)
		{
			bottomLeft = true;
		}

		size_t nextColor = 0;

		switch (_colorFormat)
		{
			case ImageColorFormat::R8G8B8A8:
			{
				textureData = std::make_unique<uint8_t[]>(bitmapWidth * bitmapHeight * 4);
				for (size_t row = 0; row < bitmapHeight; ++row)
				{
					if (bottomLeft)
					{
						nextColor = bitmapSize - rowSize * (row + 1);
					}

					for (size_t col = 0; col < bitmapWidth; ++col)
					{
						textureData[indexTextureData] = imageData[nextColor + 2];
						textureData[indexTextureData + 1] = imageData[nextColor + 1];
						textureData[indexTextureData + 2] = imageData[nextColor];
						textureData[indexTextureData + 3] = uint8_t(-1);
						nextColor += 3;
						indexTextureData += 4;
					}
				}
				break;
			}
			case ImageColorFormat::R8G8B8:
			{
				textureData = std::make_unique<uint8_t[]>(bitmapWidth * bitmapHeight * 3);
				for (size_t row = 0; row < bitmapHeight; ++row)
				{
					if (bottomLeft)
					{
						nextColor = bitmapSize - rowSize * (row + 1);
					}

					for (size_t col = 0; col < bitmapWidth; ++col)
					{
						textureData[indexTextureData] = imageData[nextColor + 2];
						textureData[indexTextureData + 1] = imageData[nextColor + 1];
						textureData[indexTextureData + 2] = imageData[nextColor];
						nextColor += 3;
						indexTextureData += 3;
					}
				}
				break;
			}
			default:
				LOGMSG("Image color format is not supported.", 0);
		}

		return std::make_tuple(std::move(textureData), static_cast<UINT>(bitmapWidth), static_cast<UINT>(bitmapHeight));
	}
}

