#include <GL/gl.h>

#include "Color.hpp"

using namespace Snooker::Graphics;

Color::Color(GLdouble redComponent, GLdouble greenComponent, GLdouble blueComponent)
: r(redComponent), g(greenComponent), b(blueComponent)
{
  // Do nothing
}

GLdouble Color::getR() const
{
  return r;
}

GLdouble Color::getG() const
{
  return g;
}

GLdouble Color::getB() const
{
  return b;
}
