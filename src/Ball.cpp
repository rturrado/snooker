#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include <unistd.h>

#include "Ball.hpp"
#include "Physics.hpp"
#include "Trajectory.hpp"
#include "Utility.hpp"
#include "Vertex.hpp"

using namespace Snooker::Graphics;
using namespace Snooker::Physics;

Ball::Ball(const GLdouble aRadius, const Vertex& aVertex, const Color& aColour)
: radius(aRadius), vertex(aVertex), color(aColour)
{
  // Do nothing
}

void Ball::draw() const
{
  glPushMatrix();
  glColor3d(color.getR(), color.getG(), color.getB());
  glTranslated(vertex.getX(), vertex.getY(), vertex.getZ());
  glutSolidSphere(radius, slices, stacks);
  glPopMatrix();
}

const Vertex& Ball::getPosition() const
{
  return vertex;
}

void Ball::move(const Vertex& newVertex)
{
  vertex = newVertex;
}

bool Ball::move(const Trajectory& trajectory, float springDistance, float timeIncr)
{
  float v = linearVelocity(springDistance, ballMass, timeIncr);
  if (equalFloat(v, 0.0))
  {
    return false;
  }
  float s = linearSpace(v, timeIncr);
  float sX = s*cos(trajectory.getAngle()*pi/180);
  float sZ = s*sin(trajectory.getAngle()*pi/180);
  GLdouble newX = vertex.getX() + sX;
  GLdouble oldY = vertex.getY();
  GLdouble newZ = vertex.getZ() + sZ;
  move(Vertex(newX, oldY, newZ));
  return true;
}
