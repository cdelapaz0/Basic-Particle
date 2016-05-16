#include "Camera.h"

Camera::Camera()
{

}

D3D11_VIEWPORT Camera::GetViewport() const
{
	return viewPort;
}

void Camera::SetViewport(D3D11_VIEWPORT _vp)
{
	viewPort = _vp;
}

void Camera::SetViewport(float _x, float _y, float _w, float _h)
{
	viewPort.TopLeftX = _x;
	viewPort.TopLeftY = _y;
	viewPort.Width = _w;
	viewPort.Height = _h;
	viewPort.MinDepth = 0;
	viewPort.MaxDepth = 1.0f;
}

void Camera::TranslateLocal(Vector3 xyz)
{
	Matrix translation = Matrix::CreateTranslation(xyz);
	worldMatrix = translation * worldMatrix;
}

void Camera::TranslateGlobal(Vector3 xyz)
{
	Matrix translation = Matrix::CreateTranslation(xyz);
	worldMatrix = worldMatrix * translation;
}

void Camera::SetPosition(Vector3 position)
{
	worldMatrix._41 = position.x;
	worldMatrix._42 = position.y;
	worldMatrix._43 = position.z;
}

void Camera::RotateXLocal(float deg)
{
	float radians = XMConvertToRadians(deg);
	Matrix rotation = Matrix::CreateRotationX(radians);

	worldMatrix = rotation * worldMatrix;
}

void Camera::RotateYLocal(float deg)
{
	float radians = XMConvertToRadians(deg);
	Matrix rotation = Matrix::CreateRotationY(radians);

	worldMatrix = rotation * worldMatrix;
}

void Camera::RotateZLocal(float deg)
{
	float radians = XMConvertToRadians(deg);
	Matrix rotation = Matrix::CreateRotationZ(radians);

	worldMatrix = rotation * worldMatrix;
}

void Camera::RotateXGlobal(float deg)
{
	float radians = XMConvertToRadians(deg);
	Matrix rotation = Matrix::CreateRotationX(radians);

	worldMatrix = worldMatrix * rotation; 
}

void Camera::RotateYGlobal(float deg)
{
	float radians = XMConvertToRadians(deg);
	Matrix rotation = Matrix::CreateRotationY(radians);

	worldMatrix = worldMatrix * rotation;
}

void Camera::RotateZGlobal(float deg)
{
	float radians = XMConvertToRadians(deg);
	Matrix rotation = Matrix::CreateRotationZ(radians);

	worldMatrix = worldMatrix * rotation;
}

void Camera::LookAt(Vector3 target)
{
	//TODO: Implement Look at Algorithm;
}

void Camera::SetWorldMatrix(Matrix world)
{
	worldMatrix = world;
}

void Camera::SetOrthographicProjection(float _w, float _h, float _near, float _far)
{
	orthographicProjection = Matrix::CreateOrthographic(_w, _h, _near, _far);
}

void Camera::SetPerspectiveProjection(float _fov, float _w, float _h, float _near, float _far)
{
	perspectiveProjection = Matrix::CreatePerspectiveFieldOfView(XMConvertToRadians(_fov), _w/_h, _near, _far);
}

Matrix Camera::GetWorldMatrix()
{
	return worldMatrix;
}

Matrix Camera::GetViewMatrix()
{
	return worldMatrix.Invert();
}

Matrix Camera::GetPerspProjectionMatrix()
{
	return perspectiveProjection;
}

Matrix Camera::GetOrthoProjectionMatrix()
{
	return orthographicProjection;
}
