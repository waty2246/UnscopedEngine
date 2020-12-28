#include"Graphics/Image.h"
#include "TerrainModel.h"

namespace ue
{
	TerrainModel::TerrainModel(const std::string& heightMapPath) :
		TerrainModel(std::string(heightMapPath))
	{
	}

	TerrainModel::TerrainModel(std::string&& heightMapPath) :
		_heightMapScale(5.0f),
		_heightMapPath(heightMapPath),
		_indexCount(0),
		_vertexCount(0),
		_indices(),
		_vertices()
	{
	}

	void TerrainModel::Init(uintptr_t state)
	{
		auto image = std::make_unique<Image>(_heightMapPath, ImageType::BITMAP, ImageColorFormat::R8G8B8);
		image->Init(InitializeState::UNSPECIFIED);

		auto imageWidth = image->GetImageWidth();
		auto imageHeight = image->GetImageHeight();
		auto imageData = image->GetImageData();

		_vertexCount = (imageWidth - 1) * (imageHeight - 1) * 6;
		_indexCount = _vertexCount;
		_vertices = std::make_unique<TerrainVertex[]>(_vertexCount);
		_indices = std::make_unique<UINT[]>(_indexCount);

		UINT vertexIndex = 0;
		UINT indexIndex = 0;
		float halfHeight = imageHeight / 2.0f;
		float halfWidth = imageWidth / 2.0f;

		for (UINT row = 0; row < imageHeight-1; ++row)
		{
			for (UINT col = 0; col < imageWidth-1; ++col)
			{
				UINT topLeftIndex = (imageWidth * row + col) * 3;
				UINT topRightIndex = (imageWidth * row + col + 1) * 3;
				UINT bottomLeftIndex = (imageWidth * (row + 1) + col) * 3;
				UINT bottomRightIndex = (imageWidth * (row + 1) + col + 1) * 3;

				_vertices[vertexIndex].Position.x = static_cast<float>(col) - halfWidth;
				_vertices[vertexIndex].Position.z = static_cast<float>(row) - halfHeight;
				_vertices[vertexIndex].Position.y = (imageData[topLeftIndex]) / _heightMapScale;
				_indices[indexIndex++] = vertexIndex;

				++vertexIndex;
				_vertices[vertexIndex].Position.x = static_cast<float>(col+1) - halfWidth;
				_vertices[vertexIndex].Position.z = static_cast<float>(row) - halfHeight;
				_vertices[vertexIndex].Position.y = (imageData[topRightIndex]) / _heightMapScale;
				_indices[indexIndex++] = vertexIndex;

				++vertexIndex;
				_vertices[vertexIndex].Position.x = static_cast<float>(col) - halfWidth;
				_vertices[vertexIndex].Position.z = static_cast<float>(row+1) - halfHeight;
				_vertices[vertexIndex].Position.y = (imageData[bottomLeftIndex]) / _heightMapScale;
				_indices[indexIndex++] = vertexIndex;

				++vertexIndex;
				_vertices[vertexIndex].Position.x = static_cast<float>(col) - halfWidth;
				_vertices[vertexIndex].Position.z = static_cast<float>(row+1) - halfHeight;
				_vertices[vertexIndex].Position.y = (imageData[bottomLeftIndex]) / _heightMapScale;
				_indices[indexIndex++] = vertexIndex;

				++vertexIndex;
				_vertices[vertexIndex].Position.x = static_cast<float>(col+1) - halfWidth;
				_vertices[vertexIndex].Position.z = static_cast<float>(row) - halfHeight;
				_vertices[vertexIndex].Position.y = (imageData[topRightIndex]) / _heightMapScale;
				_indices[indexIndex++] = vertexIndex;

				++vertexIndex;
				_vertices[vertexIndex].Position.x = static_cast<float>(col+1) - halfWidth;
				_vertices[vertexIndex].Position.z = static_cast<float>(row+1) - halfHeight;
				_vertices[vertexIndex].Position.y = (imageData[bottomRightIndex]) / _heightMapScale;
				_indices[indexIndex++] = vertexIndex;

				++vertexIndex;
			}
		}
	}

	UINT* TerrainModel::GetIndices() const
	{
		return _indices.get();
	}

	UINT TerrainModel::GetIndexCount() const
	{
		return _indexCount;
	}

	const TerrainVertex* TerrainModel::GetVertices() const
	{
		return _vertices.get();
	}

	UINT TerrainModel::GetVertexCount() const
	{
		return _vertexCount;
	}
}

