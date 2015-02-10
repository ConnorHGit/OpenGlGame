#ifndef MAIN
#define MAIN
#include <map>
#include "GL/glew.h"

extern std::map<char*,GLuint> textures;
extern bool KeyDown[127];
extern float delta;
void LoadTexture(char* textname, char* imgpath);

#endif