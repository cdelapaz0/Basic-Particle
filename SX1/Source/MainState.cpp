#include "MainState.h"

#include "D3D.h"
#include "Input.h"
#include "Utilities.h"
#include "ParticleVertex.h"


MainState::MainState(D3D* _d3d) : IBaseState(StateID::Main)
{
	pD3D = _d3d;
	clearColor = Colors::Black.v;
	
	emitter = nullptr;
}

MainState::~MainState()
{

}

void MainState::Enter()
{
	//Init camera
	mainCamera.SetViewport(0.0f, 0.0f, pD3D->GetWidth(), pD3D->GetHeight());
	mainCamera.SetPerspectiveProjection(90.0f, pD3D->GetWidth(), pD3D->GetHeight(), pD3D->GetNearPlane(), pD3D->GetFarPlane());
	mainCamera.SetOrthographicProjection(pD3D->GetWidth(), pD3D->GetHeight(), pD3D->GetNearPlane(), pD3D->GetFarPlane());
	mainCamera.SetViewport(0.0f, 0.0f, pD3D->GetWidth(), pD3D->GetHeight());
	mainCamera.SetPosition(Vector3(0, 0, -5));

	//Init vertex buffer
	ParticleVertex verts[2] = {};
	verts[0].position = Vector3(0.0f, 2.0f, 0.0f);
	verts[0].color = Colors::SkyBlue.v;
	verts[0].size = 1;

	verts[1].position = Vector3(0.0f, -2.0f, 5.0f);
	verts[1].color = Colors::LimeGreen.v;
	verts[1].size = 2;

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(ParticleVertex) * 2;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = verts;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;

	pD3D->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer);

	//Init shaders
	HRESULT result;
	ID3DBlob* errorMessage;
	ID3DBlob* vertexShaderBuffer;
	ID3DBlob* pixelShaderBuffer;
	ID3DBlob* geoShaderBuffer;

	unsigned int flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_ENABLE_STRICTNESS;

	// Vertex Shader
	result = D3DCompileFromFile(L"Resource/ParticleVS.hlsl", NULL, NULL, "main", "vs_4_0",
		flags, 0, &vertexShaderBuffer, &errorMessage);

	// Create the vertex shader from the buffer.
	result = pD3D->GetDevice()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), 
		vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);

	// Pixel Shader
	result = D3DCompileFromFile(L"Resource/ParticlePS.hlsl", NULL, NULL, "main", "ps_4_0",
		flags, 0, &pixelShaderBuffer, &errorMessage);

	// Create the pixel shader from the buffer.
	result = pD3D->GetDevice()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);

	// Geometry Shader
	result = D3DCompileFromFile(L"Resource/ParticleGS.hlsl", NULL, NULL, "main", "gs_4_0",
		flags, 0, &geoShaderBuffer, &errorMessage);

	// Create the geometry shader from the buffer.
	result = pD3D->GetDevice()->CreateGeometryShader(geoShaderBuffer->GetBufferPointer(),
		geoShaderBuffer->GetBufferSize(), NULL, &geometryShader);

	//Init input layout
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements;

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "SIZE";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	result = pD3D->GetDevice()->CreateInputLayout(polygonLayout, numElements,
		vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &inputLayout);

	pD3D->GetDeviceContext()->IASetInputLayout(inputLayout);

	SAFE_RELEASE(vertexShaderBuffer);
	SAFE_RELEASE(pixelShaderBuffer);
	SAFE_RELEASE(geoShaderBuffer);

	//Init Constant Buffers
	D3D11_BUFFER_DESC cbufferCameraDesc;
	ZeroMemory(&cbufferCameraDesc, sizeof(cbufferCameraDesc));

	cbufferCameraDesc.Usage = D3D11_USAGE_DEFAULT;
	cbufferCameraDesc.ByteWidth = sizeof(CameraCBuffer);
	cbufferCameraDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbufferCameraDesc.CPUAccessFlags = 0;
	cbufferCameraDesc.MiscFlags = 0;
	cbufferCameraDesc.StructureByteStride = 0;

	cbufferCamera.viewMatrix = mainCamera.GetViewMatrix();
	cbufferCamera.projectionMatrix = mainCamera.GetPerspProjectionMatrix();

	D3D11_SUBRESOURCE_DATA cbufferCameraData;
	ZeroMemory(&cbufferCameraData, sizeof(cbufferCameraData));
	cbufferCameraData.pSysMem = &cbufferCamera;
	cbufferCameraData.SysMemPitch = 0;
	cbufferCameraData.SysMemSlicePitch = 0;

	pD3D->GetDevice()->CreateBuffer(&cbufferCameraDesc, &cbufferCameraData, &cameraCBuffer);

	///////
	D3D11_BUFFER_DESC cbufferObjectDesc;
	ZeroMemory(&cbufferObjectDesc, sizeof(cbufferObjectDesc));

	cbufferObjectDesc.Usage = D3D11_USAGE_DEFAULT;
	cbufferObjectDesc.ByteWidth = sizeof(ObjectCBuffer);
	cbufferObjectDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbufferObjectDesc.CPUAccessFlags = 0;
	cbufferObjectDesc.MiscFlags = 0;
	cbufferObjectDesc.StructureByteStride = 0;

	cbufferObject.worldMatrix = XMMatrixIdentity();

	D3D11_SUBRESOURCE_DATA cbufferObjectData;
	ZeroMemory(&cbufferObjectData, sizeof(cbufferObjectData));
	cbufferObjectData.pSysMem = &cbufferObject;
	cbufferObjectData.SysMemPitch = 0;
	cbufferObjectData.SysMemSlicePitch = 0;

	pD3D->GetDevice()->CreateBuffer(&cbufferObjectDesc, &cbufferObjectData, &objectCBuffer);

	/////// Emitter
	D3D11_BUFFER_DESC emitterVertexBufferDesc;
	ZeroMemory(&emitterVertexBufferDesc, sizeof(emitterVertexBufferDesc));

	emitterVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	emitterVertexBufferDesc.ByteWidth = sizeof(ParticleVertex) * 2;
	emitterVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	emitterVertexBufferDesc.CPUAccessFlags = 0;
	emitterVertexBufferDesc.MiscFlags = 0;
	emitterVertexBufferDesc.StructureByteStride = 0;

	pD3D->GetDevice()->CreateBuffer(&emitterVertexBufferDesc, nullptr, &emitterVertexBuffer);

	emitter = new ParticleEmitter();
	emitter->Initialize(50, 2, 1, Colors::Red.v, Colors::Orange.v, Vector3(0, 1, 0), 
		Vector3(0, 1, 0), Vector3(0, -2, 0), 1.0f, 1.4f);
}

void MainState::Exit()
{
	SAFE_RELEASE(objectCBuffer);
	SAFE_RELEASE(cameraCBuffer);
	SAFE_RELEASE(inputLayout);
	SAFE_RELEASE(geometryShader);
	SAFE_RELEASE(pixelShader);
	SAFE_RELEASE(vertexShader);
	SAFE_RELEASE(vertexBuffer);
}

bool MainState::Input()
{
	if (Input::KeyPressed('R'))
	{
		//Randomize color here
		clearColor = ColorTools::RandomColor();
	}

	return true;
}

bool MainState::Update(float _fDT)
{
	//cbuff
	emitter->Update(0.166f);

	return true;
}

bool MainState::Render()
{
	// Clear the buffers to begin the scene.
	pD3D->BeginScene(clearColor);

	// Set Viewport
	pD3D->GetDeviceContext()->RSSetViewports(1, &mainCamera.GetViewport());

	// Set Camera Constant Buffer
	pD3D->GetDeviceContext()->GSSetConstantBuffers(0, 1, &cameraCBuffer);

	// Set Other Constant Buffers
	pD3D->GetDeviceContext()->GSSetConstantBuffers(1, 1, &objectCBuffer);

	// Set Vertex/Index Buffers
	unsigned int stride = sizeof(ParticleVertex);
	unsigned int offset = 0;
	pD3D->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// Set Input Topology
	pD3D->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// Set Input Layout
	pD3D->GetDeviceContext()->IASetInputLayout(inputLayout);

	// Set Vertex/Geometry/Pixels Shaders
	pD3D->GetDeviceContext()->VSSetShader(vertexShader, nullptr, 0);
	pD3D->GetDeviceContext()->GSSetShader(geometryShader, nullptr, 0);
	pD3D->GetDeviceContext()->PSSetShader(pixelShader, nullptr, 0);

	// Draw
	pD3D->GetDeviceContext()->Draw(2, 0);

	pD3D->EndScene();

	return true;
}