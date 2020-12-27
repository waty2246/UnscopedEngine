cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix wvpMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;

	input.position.w = 1.0f;

	output.position = mul(input.position, wvpMatrix);

	return output;
}