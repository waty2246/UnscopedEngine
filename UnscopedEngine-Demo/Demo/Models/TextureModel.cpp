#include "TextureModel.h"

namespace ue
{
	TextureModel::TextureModel():
		_vertexCount(0),
		_vertices(),
		_indexCount(0),
		_indices()
	{
	}

	void TextureModel::Init(uintptr_t state)
	{
		_vertexCount = 3;
		_vertices = std::make_unique<TextureDataType[]>(_vertexCount);

		_vertices[0].Position = { -1.0f, -1.0f, 0.0f };  // Bottom left.
		_vertices[0].Tex = { 0.0f,1.0f };

		_vertices[1].Position = { 0.0f, 1.0f, 0.0f };  // Top middle.
		_vertices[1].Tex = { 0.5f,0.0f };

		_vertices[2].Position = { 1.0f, -1.0f, 0.0f };  // Bottom right.
		_vertices[2].Tex = {1.0f,1.0f };

		_indexCount = 3;
		_indices = std::make_unique<UINT[]>(_indexCount);
		_indices[0] = 0;  // Bottom left.
		_indices[1] = 1;  // Top middle.
		_indices[2] = 2;  // Bottom right.
	}

	UINT* TextureModel::GetIndices() const
	{
		return _indices.get();
	}

	UINT TextureModel::GetIndexCount() const
	{
		return _indexCount;
	}

	TextureDataType* TextureModel::GetVertices() const
	{
		return _vertices.get();
	}

	UINT TextureModel::GetVertexCount() const
	{
		return _vertexCount;
	}
}

