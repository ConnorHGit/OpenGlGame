#pragma once
#include "glm\glm.hpp";
#include "Body.h";

class Manifold{
public:
	Body a, b;
	double penetration;
	glm::vec3 normal;
	Manifold(Body a, Body b, double pen, glm::vec3 normal);
	Manifold(Body a, Body b);
	Manifold();
};