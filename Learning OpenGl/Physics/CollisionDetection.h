#include "Body.h"
#include "Manifold.h"
#include "glm/glm.hpp"
#include <vector>
#include <math.h>
#include <iostream>
class CollisionDetection{
public:
	static void Broadphase(std::vector<Body>* bodies);
};