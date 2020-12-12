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
	float2 tex : TEXCOORD0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;

	input.position.w = 1.0f;

	output.position = mul(input.position, wvpMatrix);

	output.tex = input.tex;

	return output;
}