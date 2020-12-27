#pragma once

#include"Graphics/DX11/DX11Common.h"
#include"Core/IInitializable.h"

namespace ue
{
	struct TerrainVertex
	{
		DirectX::XMFLOAT3 Position;
	};

	class TerrainModel : public IInitializable
	{
	public:
		TerrainModel(const std::string& heightMapPath);
		TerrainModel(std::string&& heightMapPath);

		virtual void Init(uintptr_t state) override;

		UINT* GetIndices() const;
		UINT GetIndexCount()const;

		const TerrainVertex* GetVertices()const;
		UINT GetVertexCount()const;
	private:
		const float _heightMapScale;
		std::string _heightMapPath;
		UINT _indexCount;
		UINT _vertexCount;
		std::unique_ptr<UINT[]> _indices;
		std::unique_ptr<TerrainVertex[]> _vertices;

	};
}