#pragma once

#include "Matrices.h"
#include "typedefs.h"

Matrix4 GL_ProjectionMatrixRH(float width, float height, float near, float far);
Matrix4 GL_ProjectionMatrixFovRH(float fovY, float ratio, float near, float far);
Matrix4 GL_LookAtMatrixRH(const Vector3 eye, const Vector3 target, const Vector3 up);

void GL_VertexPush(float x, float y, float z);
void GL_VertexPush(const Vector3 v);
void GL_VertexPush(const Vector4 v);
void GL_SetViewMatrix(const Matrix4 &view);
void GL_SetProjectionMatrix(const Matrix4 &proj);
void GL_Clear();
void GL_Draw();
void GL_VertexFree();