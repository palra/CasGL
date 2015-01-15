#include "FxGL.h"
#include "Matrices.h"

#include <mathf.h>

/**
 * Returns a projection matrix of a right-handed coordinate system
 *
 * @param width  The width of the viewport
 * @param height The height of the viewport
 * @param near   The near clipping distance
 * @param far    The far clipping distance
 */
Matrix4 GL_ProjectionMatrixRH(float width, float height, float near, float far)
{
  Matrix4 mat;

  mat[0] = (2*near) / width;
  mat[5] = (2*near) / height;
  mat[10] = far / (near - far);
  mat[11] = (near * far) / (near - far);
  mat[14] = -1;
  mat[15] = 0;

  return mat;
}

/**
 * Returns a projection matrix of a right-handed coordinate system, calculated
 * from a given field of view.
 *
 * @param fovY  The vertical field of view, in radians.
 * @param ratio The ratio between the vertical fov and the horizontal one given
 * by `fovX = fovY / ratio`.
 * @param near  The near clipping distance
 * @param far   The far clipping distance
 */
Matrix4 GL_ProjectionMatrixFovRH(float fovY, float ratio, float near, float far)
{
  Matrix4 mat;

  mat[5] = 1 / tanf(0.5f * fovY);
  mat[0] = mat[5] / ratio;
  mat[10] = far / (near - far);
  mat[11] = (near * far) / (near - far);
  mat[14] = -1;
  mat[15] = 0;

  return mat;
}

/**
 * Returns a view matrix from a given point of view, to a given target and 
 * using a global up vector (usually (0,1,0))
 *
 * @param eye    The position vector
 * @param target The target vector
 * @param up     The up vector
 */
Matrix4 GL_LookAtMatrixRH(const Vector3 eye, const Vector3 target, const Vector3 up)
{
  Vector3 zaxis = -(eye - target).normalize();
  Vector3 xaxis = up.cross(zaxis).normalize();
  Vector3 yaxis = zaxis.cross(xaxis);

  Matrix4 mat(
    xaxis.x, xaxis.y, xaxis.z, 0, // 1st column
    yaxis.x, yaxis.y, yaxis.z, 0, // 2nd column
    zaxis.x, zaxis.y, zaxis.z, 0, // 3rd column
    -xaxis.dot(eye)  , -yaxis.dot(eye),   -zaxis.dot(eye),   1  // 4th column
  );

  return mat;
}