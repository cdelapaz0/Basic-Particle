#pragma once

#include "D3DInclude.h"
#include "DXTKInclude.h"

class Camera
{
public:
	Camera();

	D3D11_VIEWPORT GetViewport() const;
	void SetViewport(D3D11_VIEWPORT _vp);
	void SetViewport(float _x, float _y, float _w, float _h);

	void TranslateLocal(Vector3 xyz);
	void TranslateGlobal(Vector3 xyz);
	void SetPosition(Vector3 position);

	void RotateXLocal(float deg);
	void RotateYLocal(float deg);
	void RotateZLocal(float deg);

	void RotateXGlobal(float deg);
	void RotateYGlobal(float deg);
	void RotateZGlobal(float deg);

	void LookAt(Vector3 target);

	void SetWorldMatrix(Matrix world);

	void SetOrthographicProjection(float _w, float _h, float _near, float _far );
	void SetPerspectiveProjection(float _fov, float _w, float _h, float _near, float _far);

	Matrix GetWorldMatrix();
	Matrix GetViewMatrix();
	Matrix GetPerspProjectionMatrix();
	Matrix GetOrthoProjectionMatrix();

private:

	D3D11_VIEWPORT viewPort;

	Matrix worldMatrix;
	Matrix perspectiveProjection;
	Matrix orthographicProjection;
};
