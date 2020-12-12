#pragma once

#include"Graphics/DX11/DX11Common.h"
#include"Core/IInitializable.h"

namespace ue
{
	struct TriangleDataType
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT4 Color;
	};

	class TriangleModel : public IInitializable
	{
	public:
		TriangleModel();

		virtual void Init(uintptr_t state) override;

		UINT* GetIndices() const;
		UINT GetIndexCount()const;

		TriangleDataType* GetVertices()const;
		UINT GetVertexCount()const;
	private:
		UINT _indexCount;
		UINT _vertexCount;
		std::unique_ptr<UINT[]> _indices;
		std::unique_ptr< TriangleDataType[]> _vertices;
	};
}