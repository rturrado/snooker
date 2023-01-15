#include "Trajectory.hpp"

using namespace Snooker::Graphics;

Trajectory::Trajectory(const Vertex& aVertex, float anAngle)
: vertex(aVertex), angle(anAngle)
{
  // Do nothing
}

float Trajectory::getAngle() const
{
  return angle;
}
