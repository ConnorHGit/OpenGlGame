#include "Body.h"
#include "Manifold.h"
#include "glm/glm.hpp"
#include <vector>
#include <math.h>
#include <iostream>
class CollisionResolution{
public:
	static void ResolveManifolds(std::vector<Manifold> manifolds);
};