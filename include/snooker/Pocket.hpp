#ifndef POCKET_HPP
#define POCKET_HPP

#include <boost/shared_ptr.hpp>
#include <GL/gl.h>

#include "Vertex.hpp"

namespace Snooker {
namespace Graphics {

class Pocket;
typedef boost::shared_ptr<Pocket> PocketPtr;

const int pocketRadius = 45;

class Pocket 
{
  Vertex vertex;
public:
  Pocket(const Vertex& aVertex);
  void draw() const;
};

} // namespace Graphic 
} // namespace Snooker

#endif // ifndef POCKET_HPP
