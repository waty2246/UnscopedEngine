#pragma once

#include"Graphics/DX11/DX11Common.h"
#include"Core/IInitializable.h"

namespace ue
{
	struct PolygonVertex
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT4 Color;
	};

	class PolygonModel : public IInitializable
	{
	public:
		PolygonModel();

		UINT* GetIndices() const;
		UINT GetIndexCount()const;

		PolygonVertex* GetVertices()const;
		UINT GetVertexCount()const;
	protected:
		UINT _indexCount;
		UINT _vertexCount;
		std::unique_ptr<UINT[]> _indices;
		std::unique_ptr< PolygonVertex[]> _vertices;
	};
}