#include "Manifold.h"
#include <math.h>
Manifold::Manifold(Body* a, Body* b, double pen, glm::vec3 normal){
	Manifold::a = a;
	Manifold::b = b;
	Manifold::penetration = pen;
	Manifold::normal = normal;
	Manifold::restitution = fmin(a->restitution, b->restitution);
}
Manifold::Manifold(Body* a, Body* b){
	Manifold::a = a;
	Manifold::b = b;
	Manifold::restitution = fmin(a->restitution, b->restitution);
}
Manifold::Manifold(){

}