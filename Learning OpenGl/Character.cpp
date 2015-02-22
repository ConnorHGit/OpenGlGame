#include "Character.h"
#include <iostream>

Character::Character(float x, float y, float z, float width, float height, float depth,char* texture) : Body(x,y,z,width,height,depth,texture){
	
}
Character::Character(glm::vec3 pos, glm::vec3 size,char* texture) : Body(pos,size,texture){
	
}
Character::Character() : Body(){
	
}
void Character::draw(glm::mat4 &ViewProjectionMatrix, GLuint program){
	if (MAIN::thirdperson != 0){
		Body::draw(ViewProjectionMatrix, program);
	}
}
void Character::update(float delta){
	Body* ground = getGround();
	jumpTime += delta;
	if (MAIN::KeyDown[' ']){
		jumpRequest = true;
		jumpTime = 0;
	}
	if (jumpTime > delta * 15){
		jumpRequest = false;
		jumpTime = 0;
	}
	if (jumpRequest){
		if (ground != NULL){
			jumpRequest = false;
			jumpTime = 0;
			velocity.y += 20;
		}
	}
	Body::tangible = !MAIN::noclip;
	Body::update(delta);
}
Body* Character::getGround(){
	for (int i = 0; i < (signed)touching.size(); i++){
		Body b = *touching[i];
		if (pos.y - size.y / 2 + 0.2 >= b.pos.y + b.size.y / 2){
			return &b;
		}
	}
	return NULL;
}