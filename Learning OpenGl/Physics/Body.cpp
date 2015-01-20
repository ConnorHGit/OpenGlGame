#pragma once
#include "Body.h"
#include <stdlib.h>
#include <iostream>
Body::Body(glm::vec3 pos, glm::vec3 size){
	Body::pos = pos;
	Body::size = size;
}
Body::Body(float x, float y, float z, float width, float height, float depth){
	pos = glm::vec3(x, y, z);
	size = glm::vec3(width, height, depth);
	setMass(size.x * size.y * size.z * 10);
	velocity = glm::vec3(rand() % 30000 / 10000.0f, rand() % 30000 / 10000.0f, rand() % 30000 / 10000.0f);
}
Body::~Body(){

}
Body::Body(){

}
void Body::update(float delta){
	velocity += acceleration * delta;
	pos += velocity * inverseMass;
}
void Body::draw(glm::mat4 &ProjectionViewMatrix,GLuint program){
	glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), pos);
	ModelMatrix = glm::scale<float>(ModelMatrix, size);
	glm::mat4 MVP = ProjectionViewMatrix * ModelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1, false, &MVP[0][0]);
	glDrawArrays(GL_QUADS, 0, 24);
}
void Body::setMass(float mass){
	Body::mass = mass;
	if (mass == 0)inverseMass = 0;
	else inverseMass = 1 / mass;
}
float Body::getMass(){
	return mass;
}
float Body::getInverseMass(){
	return inverseMass;
}