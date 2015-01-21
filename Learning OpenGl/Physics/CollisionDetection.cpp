#include "CollisionDetection.h"
#include "CollisionResolution.h"
Manifold detect(Body* a, Body* b);
void CollisionDetection::Broadphase(std::vector<Body>* bodies){
	std::vector<Manifold> manifolds;
	for (signed int i = 0; i < (signed)(bodies->size() - 1); i++){
		for (signed int j = i + 1; j < (signed)(bodies->size()); j++){
			Body* a = &(*bodies)[i];
			Body* b = &(*bodies)[j];
			if (a->getMass() == 0 && b->getMass() == 0)continue;
			Manifold m = detect(a, b);
			if (m.collided){
				//std::cout << "Collided" << std::endl;
				manifolds.push_back(m);
			}
		}
	}
	CollisionResolution::ResolveManifolds(manifolds);
}
Manifold detect(Body* a, Body* b){
	Manifold m = Manifold(a, b);

	m.collided = false;

	if (a->pos.x > b->pos.x + b->size.x || a->pos.x + a->size.x < b->pos.x)return m;
	if (a->pos.y > b->pos.y + b->size.y || a->pos.y + a->size.y < b->pos.y)return m;
	if (a->pos.z > b->pos.z + b->size.z || a->pos.z + a->size.z < b->pos.z)return m;

	m.collided = true;

	glm::vec3 halfExtA = a->size / 2.0f;
	glm::vec3 halfExtB = b->size / 2.0f;

	glm::vec3 centA = a->pos + halfExtA;
	glm::vec3 centB = b->pos + halfExtB;

	double hX = halfExtA.x + halfExtB.x;
	double hY = halfExtA.y + halfExtB.y;
	double hZ = halfExtA.z + halfExtB.z;

	double dX = abs(centA.x - centB.x);
	double dY = abs(centA.y - centB.y);
	double dZ = abs(centA.z - centB.z);

	double oX = abs(dX - hX);
	double oY = abs(dY - hY);
	double oZ = abs(dZ - hZ);

	double max = fmin(fmin(oX, oY), oZ);

	if (max == oX){
		m.penetration = oX - 1;
		if (centA.x > centB.x)
			m.normal = glm::vec3(-1, 0, 0);
		else
			m.normal = glm::vec3(1, 0, 0);
	}
	else if (max == oY){

		m.penetration = oY - 1;
		if (centA.y > centB.y)
			m.normal = glm::vec3(0, -1, 0);
		else
			m.normal = glm::vec3(0, 1, 0);
	}
	else{

		m.penetration = oZ - 1;
		if (centA.z > centB.z)
			m.normal = glm::vec3(0, 0, -1);
		else
			m.normal = glm::vec3(0, 0, 1);
	}
	return m;
}