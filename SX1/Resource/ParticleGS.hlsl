#pragma pack_matrix( row_major )

struct GS_Output
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
};

struct GS_Input
{
	float4 pos : SV_POSITION;
	float4 col	: COLOR;
	float  size : SIZE;
};

//cbuffer Object : register(b0)
//{
//	float4x4 worldMatrix;
//};

cbuffer Camera : register(b0)
{
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
};

[maxvertexcount(6)]
void main(point GS_Input input[1], inout TriangleStream< GS_Output > output)
{
	GS_Output verts[4];
	float halfSize = input[0].size / 2;

	verts[0].pos = input[0].pos;
	verts[0].pos.x -= halfSize;
	verts[0].pos.y += halfSize;

	verts[1].pos = input[0].pos;
	verts[1].pos.x += halfSize;
	verts[1].pos.y += halfSize;

	verts[2].pos = input[0].pos;
	verts[2].pos.x += halfSize;
	verts[2].pos.y -= halfSize;

	verts[3].pos = input[0].pos;
	verts[3].pos.x -= halfSize;
	verts[3].pos.y -= halfSize;

	[unroll]
	for (int i = 0; i < 4; ++i)
	{
		verts[i].col = input[0].col;

		float4 local = verts[i].pos;
		local = mul(local, viewMatrix);
		local = mul(local, projectionMatrix);

		verts[i].pos = local;
	}

	output.Append(verts[0]);
	output.Append(verts[1]);
	output.Append(verts[3]);

	output.RestartStrip();

	output.Append(verts[1]);
	output.Append(verts[2]);
	output.Append(verts[3]);
}
