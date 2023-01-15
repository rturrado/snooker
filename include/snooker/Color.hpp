#ifndef COLOR_HPP
#define COLOR_HPP

#include <GL/gl.h>

namespace Snooker {
namespace Graphics {

class Color 
{
  GLdouble r;
  GLdouble g;
  GLdouble b;
public:
  Color(GLdouble redComponent, GLdouble greenComponent, GLdouble blueComponent);
  GLdouble getR() const;
  GLdouble getG() const;
  GLdouble getB() const;
};

} // namespace Graphic 
} // namespace Snooker

#endif // ifndef COLOR_HPP
