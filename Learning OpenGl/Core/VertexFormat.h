#pragma once

#include "glm\glm.hpp"

struct VertexFormat{
	
	glm::vec3 position;
	glm::vec4 color;

	VertexFormat(const glm::vec3 &pos, const glm::vec4 &icolor){
		position = pos;
		color = icolor;
	}

};
