#pragma once
#include <map>
#include <vector>
#include "Body.h"
class BodyList{
private:
	std::vector<Body*> bodies;
public:
	Body* operator[](char* name);
	Body* operator[](int i);

	Body* add( float x, float y, float z, float width, float height, float depth, char* text);
	Body* add( glm::vec3 pos, glm::vec3 size, char* text);
	Body* add( float x, float y, float z, float width, float height, float depth, float dx, float dy, float dz, char* text);
	Body* add( glm::vec3 pos, glm::vec3 size, glm::vec3 speed, char* text);
	Body* add( float x, float y, float z, float width, float height, float depth, float dx, float dy, float dz, float ax, float ay, float az, char* text);
	Body* add( glm::vec3 pos, glm::vec3 size, glm::vec3 speed, glm::vec3 acceleration, char* text);
	Body* add( Body* b);
	void updateBodies(float delta);
	void drawBodies(glm::mat4 &ProjectionViewMatrix, GLuint program);

	BodyList();
	~BodyList();

	operator std::vector<Body*>*(){
		return &bodies;
	}
};