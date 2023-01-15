#include <cmath>  // for abs
#include <limits> // for epsilon

#include "Utility.hpp"

bool equalFloat(float x, float y)
{
  float relerr = (fabs(x) - fabs(y)) / fabs(y);
  float epsilon = std::numeric_limits<float>::epsilon();
  return relerr <= epsilon;
}
