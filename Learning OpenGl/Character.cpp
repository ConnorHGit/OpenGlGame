#include "Character.h"
Character::Character(float x, float y, float z, float width, float height, float depth) : Body(x,y,z,width,height,depth){
	isVisible = false;
}
Character::Character(glm::vec3 pos, glm::vec3 size) : Body(pos,size){
	isVisible = false;
}
Character::Character() : Body(){
	isVisible = false;
}