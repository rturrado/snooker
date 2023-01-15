#ifndef PLAYING_SURFACE_HPP
#define PLAYING_SURFACE_HPP

#include <GL/gl.h>

#include "Vertex.hpp"
#include "Color.hpp"

namespace Snooker {
namespace Graphics {

// Playing surface
const GLdouble psLength = 3569;
const GLdouble psWidth  = 1778;
const GLdouble bottomCushionToBaulkLine = 737;
const GLdouble dRadius                  = 292;

class PlayingSurface
{
  Vertex vertex0;
  Vertex vertex1;
  Vertex vertex2;
  Vertex vertex3;
  Color color;
public:
  PlayingSurface(const Color& aColour);
  void draw() const;
};

} // namespace Graphic 
} // namespace Snooker

#endif // ifndef PLAYING_SURFACE_HPP
