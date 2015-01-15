extern "C" {
	#include <stdlib.h>
  #include "fx-monochromelib/include/MonochromeLib.h"
}

#include "FxGL.h"
#include "Matrices.h"

struct Vertex
{
	Vector3 pos;
	struct Vertex *next;
};

struct VertexStack
{
	struct Vertex *first;
};

typedef struct Vertex Vertex;
typedef struct VertexStack VertexStack;

static VertexStack _stack = { (Vertex*) NULL };
static Matrix4 _projection;
static Matrix4 _view;

/**
 * Pushes a vertex in the transform pipeline
 * 
 * @param x The x coord of the vertex
 * @param y The y coord of the vertex
 * @param z The z coord of the vertex
 */
void GL_VertexPush(float x, float y, float z)
{
  Vertex *v = (Vertex*) malloc(sizeof(Vertex)), *ptr;
  if(v == (Vertex*) NULL)
    return;

  if(_stack.first == NULL)
    _stack.first = v;
  else {
    ptr = _stack.first;
    while(ptr->next != NULL) {
      ptr = ptr->next;
    }

    ptr->next = v;
  }

  v->pos.x = x;
  v->pos.y = y;
  v->pos.z = z;
  v->next = NULL;
}

/**
 * Pushes a vertex in the transform pipeline
 * 
 * @param v The 3D coordinates of the vertex
 */
void GL_VertexPush(const Vector3 v)
{
  GL_VertexPush(v.x, v.y, v.z);
}

/**
 * Pushes a vertex in the transform pipeline. w coordinate will be ignored.
 * 
 * @param v The 3D coordinates of the vertex
 */
void GL_VertexPush(const Vector4 v)
{
  GL_VertexPush(v.x, v.y, v.z);
}

/**
 * Sets the view matrix used for the transformations
 * 
 * @param view The 4D view matrix 
 */
void GL_SetViewMatrix(const Matrix4 &view)
{
  _view.set(view.get());
}

/**
 * Sets the view matrix used for the transformations
 * 
 * @param view The 4D view matrix, expressed in column-major convention
 */
void GL_SetViewMatrix(const float view[16])
{
  _view.set(view);
}

/**
 * Sets the projection matrix used for the transformations
 * 
 * @param proj The 4D projection matrix
 */
void GL_SetProjectionMatrix(const Matrix4 &proj)
{
  _projection.set(proj.get());
}

/**
 * Sets the projection matrix used for the transformations
 * 
 * @param proj The 4D projection matrix, expressed in column-major convention
 */
void GL_SetProjectionMatrix(const float proj[16])
{
  _projection.set(proj);
}

/**
 * Clears the screen and the Z-Buffer (TODO)
 */
void GL_Clear()
{
  ML_clear_vram();
}

/**
 * Renders the transformed vertices
 */
void GL_Draw()
{
  int i = 0;
  Vector4 buffer[2];
  Vertex *ptr = _stack.first;

  Matrix4 viewProj = _projection * _view;

  while(ptr != NULL) {
    buffer[i%2].x = ptr->pos.x;
    buffer[i%2].y = ptr->pos.y;
    buffer[i%2].z = ptr->pos.z;
    buffer[i%2].w = 1;

    // Projection
    buffer[i%2] = viewProj * buffer[i%2];

    // NDC
    buffer[i%2] /= buffer[i%2].w;

    buffer[i%2].x += 64;
    buffer[i%2].y += 32;

    if(i%2)
      ML_line(
          (unsigned char) buffer[(i-1)%2].x, (unsigned char) buffer[(i-1)%2].y,
          (unsigned char) buffer[i%2].x, (unsigned char) buffer[i%2].y,
      ML_BLACK);

    ptr = ptr->next;

    i++;
  }

  ML_display_vram();

}

/**
 * Free the vertices array
 */
void GL_VertexFree()
{
  Vertex *ptr = _stack.first, *buffer;

  while(ptr != NULL)
  {
    buffer = ptr->next;
    free(ptr);
    ptr = buffer;
  }

  _stack.first = NULL;
}