#include <cmath>
#include <GL/gl.h>

#include "Pocket.hpp"
#include "Utility.hpp"

using namespace Snooker::Graphics;

Pocket::Pocket(const Vertex& aVertex)
: vertex(aVertex)
{
  // Do nothing
}

void Pocket::draw() const
{
  glColor3d(0.1, 0.1, 0.1);
  glPushMatrix();
  glTranslated(vertex.getX(), vertex.getY(), vertex.getZ());
  glBegin(GL_TRIANGLE_FAN);
    for (int angle = 0; angle <= 360; angle++)
    {
      glVertex3d(pocketRadius * cos(angle*pi/180),
                 0,
                 pocketRadius * sin(angle*pi/180));
    }
  glEnd();
  glPopMatrix();
}
