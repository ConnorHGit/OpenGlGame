#pragma once
#include "glm\glm.hpp";
#include "glm\gtc\matrix_access.hpp"
#include<glm\gtc\matrix_transform.hpp>
#include <GL/glew.h>
#include "../Core/GameModels.h"
class Body{
public:
	Body(glm::vec3 pos,glm::vec3 size);
	Body(int x, int y, int z, int width, int height, int depth);
	~Body();
	void update(float delta);
	void draw(glm::mat4 ViewProjectionMatrix, GLuint program, Models::GameModels* gameModels);
	void setMass(float mass);
	float getMass();
	float getInverseMass();
	glm::vec3 pos;
	glm::vec3 size;
	glm::vec3 velocity;
	glm::vec3 acceleration;
private:
	float mass;
	float inverseMass;
};