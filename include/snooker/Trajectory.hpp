#ifndef TRAJECTORY_HPP
#define TRAJECTORY_HPP

#include "Vertex.hpp"

namespace Snooker {
namespace Graphics {

class Trajectory
{
  Vertex vertex;
  float angle;
public:
  Trajectory(const Vertex& aVertex, float anAngle);
  float getAngle() const;
};

} // namespace Graphics 
} // namespace Snooker

#endif // ifndef TRAJECTORY_HPP
