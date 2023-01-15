#include <cmath>
#include <GL/gl.h>

#include "PlayingSurface.hpp"
#include "Utility.hpp"

using namespace Snooker::Graphics;

PlayingSurface::PlayingSurface(const Color& aColour)
: vertex0(-psWidth/2, 0,  psLength/2),
  vertex1( psWidth/2, 0,  psLength/2),
  vertex2( psWidth/2, 0, -psLength/2),
  vertex3(-psWidth/2, 0, -psLength/2),
  color(aColour)
{
  // Do nothing
}

void PlayingSurface::draw() const
{
  GLdouble zBaulkLine = psLength/2-bottomCushionToBaulkLine;

  // Baulk line
  glColor3d(0.9, 0.9, 0.9);
  glBegin(GL_LINES);
    glVertex3d(vertex0.getX(), vertex0.getY(), zBaulkLine);
    glVertex3d(vertex1.getX(), vertex1.getY(), zBaulkLine);
  glEnd();

  // D area
  glBegin(GL_LINE_STRIP);
    for (int angle = 0; angle <= 180; angle++)
    {
      glVertex3d(dRadius * cos(angle*pi/180),
                 vertex0.getY(),
                 dRadius * sin(angle*pi/180) + zBaulkLine);
    }
  glEnd();

  // Cloth
  glBegin(GL_QUADS);
    glColor3d(color.getR(), color.getG(), color.getB());
    glVertex3d(vertex0.getX(), vertex0.getY(), vertex0.getZ());
    glVertex3d(vertex1.getX(), vertex1.getY(), vertex1.getZ());
    glVertex3d(vertex2.getX(), vertex2.getY(), vertex2.getZ());
    glVertex3d(vertex3.getX(), vertex3.getY(), vertex3.getZ());
  glEnd();
}
