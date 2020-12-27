#pragma once

#include"DX11Common.h"
#include"Core/IInitializable.h"
#include"Core/ServiceConsumer.h"
#include"Graphics/Image.h"

namespace ue
{
	/// <summary>
	/// Manage the loading, unloading and accessing to a single Texture-2D resource.
	/// </summary>
	class DX11Texture2D :public IInitializable, public ServiceConsumer
	{
	public:
		DX11Texture2D(const std::string& fileName, ImageType imageType);
		DX11Texture2D(std::string&& fileName,ImageType imageType);

		/// <summary>
		/// Load Texture-2D from the given fileName and imageType.
		/// </summary>
		/// <param name="state"></param>
		virtual void Init(uintptr_t state) override;

		/// <summary>
		/// Get the shader resource so that it can be used for rendering by shaders.
		/// </summary>
		/// <returns></returns>
		ID3D11ShaderResourceView* GetShaderResourceView()const;

		~DX11Texture2D();

	private:
		bool _hasInit;
		const std::string _fileName;
		const ImageType _imageType;
		const bool _isAutoGenerateMipmaps;
		const bool _isSampledTexture;
		UINT _bindFlags;
		UINT _miscFlags;
		UINT _cpuAccess;
		const D3D11_USAGE _usage;
		const DXGI_FORMAT _colorFormat;

		ComPtr<ID3D11Texture2D> _texture2D;
		ComPtr<ID3D11ShaderResourceView> _texture2DView;
	};
}