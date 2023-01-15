#include <GL/gl.h>

#include "Vertex.hpp"

using namespace Snooker::Graphics;

Vertex::Vertex()
: x(0.0), y(0.0), z(0.0)
{
  // Do nothing
}

Vertex::Vertex(GLdouble xCoord, GLdouble yCoord, GLdouble zCoord)
: x(xCoord), y(yCoord), z(zCoord)
{
  // Do nothing
}

GLdouble Vertex::getX() const
{
  return x;
}

GLdouble Vertex::getY() const
{
  return y;
}

GLdouble Vertex::getZ() const
{
  return z;
}

void Vertex::setX(GLdouble newX)
{
  x = newX;
}

void Vertex::setY(GLdouble newY)
{
  y = newY;
}

void Vertex::setZ(GLdouble newZ)
{
  z = newZ;
}
