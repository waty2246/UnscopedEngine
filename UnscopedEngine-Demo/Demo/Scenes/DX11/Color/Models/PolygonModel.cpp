#include "PolygonModel.h"

namespace ue
{
	PolygonModel::PolygonModel() :
		_vertexCount(0),
		_vertices(),
		_indexCount(0),
		_indices()
	{
	}

	UINT* PolygonModel::GetIndices() const
	{
		return _indices.get();
	}

	UINT PolygonModel::GetIndexCount() const
	{
		return _indexCount;
	}

	PolygonVertex* PolygonModel::GetVertices() const
	{
		return _vertices.get();
	}

	UINT PolygonModel::GetVertexCount() const
	{
		return _vertexCount;
	}
}
