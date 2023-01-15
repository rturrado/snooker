#ifndef BALL_HPP
#define BALL_HPP

#include <boost/shared_ptr.hpp>
#include <GL/gl.h>

#include "Color.hpp"
#include "Trajectory.hpp"
#include "Vertex.hpp"

namespace Snooker {
namespace Graphics {

class Ball;
typedef boost::shared_ptr<Ball> BallPtr;

const int slices = 32;
const int stacks = 32;
// Ball mass in Kg
const float ballMass = 0.250;

class Ball
{
  const GLdouble radius;
  Vertex vertex;
  Color color;
public:
  Ball(const GLdouble radius, const Vertex& aVertex, const Color& aColour);
  void draw() const;
  const Vertex& getPosition() const;
  void move(const Vertex& newVertex);
  bool move(const Trajectory& trajectory, float springDistance, float timeIncr);
};

} // namespace Graphic 
} // namespace Snooker

#endif // ifndef BALL_HPP
