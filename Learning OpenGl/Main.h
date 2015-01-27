#ifndef MAIN
#define MAIN
#include <map>
#include "GL/glew.h"

extern std::map <std::string, GLuint> textures;
void LoadTexture(char* textname, char* imgpath);

#endif