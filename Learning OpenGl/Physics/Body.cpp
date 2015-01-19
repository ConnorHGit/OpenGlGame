#pragma once
#include "Body.h"

Body::Body(glm::vec3 pos, glm::vec3 size){
	Body::pos = pos;
	Body::size = size;
}
Body::Body(int x, int y, int z, int width, int height, int depth){
	pos = glm::vec3(x, y, z);
	size = glm::vec3(width, height, depth);
}
Body::~Body(){

}
void Body::update(float delta){
	velocity += acceleration * delta;
	pos += velocity * inverseMass;
}
void Body::draw(glm::mat4 &ProjectionViewMatrix,GLuint program,Models::GameModels* gameModels){
	glBindVertexArray(gameModels->GetModel("cube1"));
	glm::mat4 ModelMatrix = glm::scale(glm::mat4(1.0f), size) * glm::translate(glm::mat4(1.0f),pos);
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