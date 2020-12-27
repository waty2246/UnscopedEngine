#pragma once

#include"Graphics/DX11/DX11Common.h"
#include"Core/IInitializable.h"

namespace ue
{
	struct TextureVertex
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT2 Tex;
	};

	class TextureModel : public IInitializable
	{
	public:
		TextureModel();

		virtual void Init(uintptr_t state) override;

		UINT* GetIndices() const;
		UINT GetIndexCount() const;

		TextureVertex* GetVertices() const;
		UINT GetVertexCount() const;
	private:
		UINT _indexCount;
		UINT _vertexCount;
		std::unique_ptr<UINT[]> _indices;
		std::unique_ptr<TextureVertex[]> _vertices;
	};
}