#pragma once

#include"DX11ShaderPart.h"

namespace ue
{
	class DX11ShaderBase :public DX11ShaderPart
	{
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

		
		
	};
}