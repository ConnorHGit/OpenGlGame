#include "Character.h"
#include <iostream>

Character::Character(float x, float y, float z, float width, float height, float depth,char* texture) : Body(x,y,z,width,height,depth,texture){
	
}
Character::Character(glm::vec3 pos, glm::vec3 size,char* texture) : Body(pos,size,texture){
	
}
Character::Character() : Body(){
	
}
void Character::draw(glm::mat4 &ViewProjectionMatrix, GLuint program){
	/*
	glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), pos);
	ModelMatrix = glm::scale<float>(ModelMatrix, size);


	glm::mat4 MVP = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1, false, &MVP[0][0]);
	glDrawArrays(GL_QUADS, 0, 24);
	*/
}
void Character::update(float delta){

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
		bool onTopAny = false;
		for (int i = 0; i < (signed)touching.size(); i++){
			Body b = *touching[i];
			//Dont ask why coords are so not fucked
			if (pos.y - size.y / 2 + 0.2 >= b.pos.y + b.size.y / 2){
				onTopAny = true;
				break;
			}
		}
		if (onTopAny){
			jumpRequest = false;
			jumpTime = 0;
			velocity.y += 10;
		}
	}
	Body::update(delta);
}