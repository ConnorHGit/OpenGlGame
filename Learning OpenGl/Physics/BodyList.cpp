#include "BodyList.h"
std::vector<Body*> bodies;


Body* BodyList::operator[](int i){
	return bodies[i];
}

Body* BodyList::add(float x, float y, float z, float width, float height, float depth,char* text){

	bodies.push_back(new Body(x, y, z, width, height, depth,text));
	return bodies[bodies.size() - 1];
}
Body* BodyList::add( glm::vec3 pos, glm::vec3 size, char* text){
	bodies.push_back(new Body(pos, size, text));
	return bodies[bodies.size() - 1];
}
Body* BodyList::add(float x, float y, float z, float width, float height, float depth, float dx, float dy, float dz, char* text){
	Body* b = new Body(x, y, z, width, height, depth,text);
	b->velocity = glm::vec3(dx, dy, dz);
	bodies.push_back(b);
	return bodies[bodies.size() - 1];
}
Body* BodyList::add(glm::vec3 pos, glm::vec3 size, glm::vec3 speed, char* text){
	Body* b = new Body(pos, size, text);
	b->velocity = speed;
	bodies.push_back(b);
	return bodies[bodies.size() - 1];
}
Body* BodyList::add(float x, float y, float z, float width, float height, float depth, float dx, float dy, float dz, float ax, float ay, float az, char* text){
	Body* b = new Body(x, y, z, width, height, depth, text);
	b->velocity = glm::vec3(dx, dy, dz);
	b->acceleration = glm::vec3(ax, ay, az);
	bodies.push_back(b);
	return bodies[bodies.size() - 1];
}
Body* BodyList::add(glm::vec3 pos, glm::vec3 size, glm::vec3 speed, glm::vec3 acceleration, char* text){
	Body* b = new Body(pos, size, text);
	b->velocity = speed;
	b->acceleration = acceleration;
	bodies.push_back(b);
	return bodies[bodies.size() - 1];
}
Body* BodyList::add( Body* b){
	bodies.push_back(b);
	return bodies[bodies.size() - 1];
}
void BodyList::updateBodies(float delta){
	for (int i = 0; i < bodies.size(); i++){
		bodies[i]->update(delta);
	}
}
void BodyList::drawBodies(glm::mat4 &ProjectionViewMatrix, GLuint program){
	for (int i = 0; i < bodies.size(); i++){
		bodies[i]->draw(ProjectionViewMatrix, program);
	}
}
BodyList::~BodyList(){
	for (int i = 0; i < bodies.size(); i++){
		delete bodies[i];
	}
}
BodyList::BodyList(){

}