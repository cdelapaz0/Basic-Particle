
struct VS_Input
{
	float3 pos : POSITION;
	float4 col : COLOR;
	float  size : SIZE;
};

struct VS_Output
{
	float4 pos : SV_POSITION;
	float4 col	: COLOR;
	float  size : SIZE;
};

//cbuffer Object : register(b0)
//{
//	float4x4 worldmatrix;
//};
//
//cbuffer Camera : register(b1)
//{
//	float4x4 viewMatrix;
//	float4x4 projectionMatrix;
//};

VS_Output main(VS_Input input)
{
	VS_Output output = (VS_Output)0;

	output.pos = float4(input.pos, 1.0f);

	output.col = input.col;
	output.size = input.size;

	return output;
}