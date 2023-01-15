#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "Utility.hpp"

namespace Snooker {
namespace Physics {

// Spring constant
const float k = 10.0;
// Sliding friction coefficient
const float muS = 0.01;
// Rolling friction coefficient
const float muR = 0.2;
// Linear velocity
// v_ = -k*t*x/m
inline float linearVelocity(float springDistance, float mass, float time)
{
  return -k*time*springDistance/mass;
}
// Linear space
// s = v_*t/2
inline float linearSpace(float velocity, float time)
{
  return velocity*time/2;
}

} // namespace Physics 
} // namespace Snooker

#endif // ifndef PHYSICS_HPP
