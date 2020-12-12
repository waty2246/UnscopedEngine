#pragma once

#include"DX11Common.h"
#include"Core/IInitializable.h"
#include"Core/ServiceConsumer.h"

namespace ue
{
	class DX11ShaderBase :public IInitializable, public ServiceConsumer
	{
	public:
		virtual void Init(uintptr_t state) override;

	protected:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="vertexCSOFile"></param>
		/// <param name="pixelCSOFile"></param>
		/// <returns>Vertex shader byte code</returns>
		virtual std::vector<uint8_t> InitShaders(const char* vertexCSOFile, const char* pixelCSOFile);

	protected:
		std::vector<uint8_t> CreateVertexShader(const char* vertexCSOFile);
		void CreatePixelShader(const char* pixelCSOFile);

	protected:
		ComPtr<ID3D11VertexShader> _vertexShader;
		ComPtr<ID3D11PixelShader> _pixelShader;

		
		ServicePtr<ID3D11Device> _device;
		ServicePtr<ID3D11DeviceContext> _deviceContext;
	};
}