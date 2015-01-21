#include "Body.h"
#include "Manifold.h"
#include "glm/glm.hpp"
#include <vector>
#include <math.h>
#include <iostream>
#include "CollisionResolution.h"
void ResolveVelocity(Manifold m);
void ResolvePenetration(Manifold m);
void CollisionResolution::ResolveManifolds(std::vector<Manifold> manifolds){
	for (Manifold m : manifolds){
		ResolveVelocity(m);
		ResolvePenetration(m);
	}
}
void ResolveVelocity(Manifold m){
	double relVelocityOverNormal = glm::dot(m.a->velocity - m.b->velocity,m.normal);

	double totalIMass = m.a->getInverseMass() + m.b->getInverseMass();

	float moveIMass = (float)(relVelocityOverNormal * -(1.0f + m.restitution) / totalIMass);
	glm::vec3 impulse = m.normal * moveIMass;
	m.a->velocity = m.a->velocity + (impulse * m.a->getInverseMass());
	m.b->velocity = m.b->velocity + (impulse * -m.b->getInverseMass());
	std::cout << m.b->velocity.y << std::endl;
}
void ResolvePenetration(Manifold m){

}