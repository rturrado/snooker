#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <GL/gl.h>

namespace Snooker {
namespace Graphics {

class Vertex
{
  GLdouble x;
  GLdouble y;
  GLdouble z;
public:
  Vertex();
  Vertex(GLdouble xCoord, GLdouble yCoord, GLdouble zCoord);
  GLdouble getX() const;
  GLdouble getY() const;
  GLdouble getZ() const;
  void setX(GLdouble newX);
  void setY(GLdouble newY);
  void setZ(GLdouble newZ);
};

} // namespace Graphic 
} // namespace Snooker

#endif // ifndef VERTEX_HPP
