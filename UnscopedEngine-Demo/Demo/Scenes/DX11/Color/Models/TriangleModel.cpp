#include"TriangleModel.h"

namespace ue
{
	void TriangleModel::Init(uintptr_t state)
	{
		_vertexCount = 3;
		_vertices = std::make_unique<PolygonVertex[]>(_vertexCount);

		_vertices[0].Position = { -1.0f, -1.0f, 0.0f };  // Bottom left.
		_vertices[0].Color = { 0.0f, 1.0f, 0.0f, 1.0f };

		_vertices[1].Position = { 0.0f, 1.0f, 0.0f };  // Top middle.
		_vertices[1].Color = { 1.0f, 1.0f, 0.0f, 1.0f };

		_vertices[2].Position = { 1.0f, -1.0f, 0.0f };  // Bottom right.
		_vertices[2].Color = { 0.0f, 1.0f, 1.0f, 1.0f };

		_indexCount = 3;
		_indices = std::make_unique<UINT[]>(_indexCount);
		_indices[0] = 0;  // Bottom left.
		_indices[1] = 1;  // Top middle.
		_indices[2] = 2;  // Bottom right.
	}
}