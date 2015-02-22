
#include "Physics/Body.h"
#include "Main.h"
class Character : public Body{
public:
	using Body::pos;
	using Body::size;
	Character();
	Character(float x, float y, float z, float width, float height, float depth,char* texture);
	Character(glm::vec3 pos, glm::vec3 size,char* texture);
	virtual void draw(glm::mat4 &ViewProjectionMatrix, GLuint program);
	virtual void update(float delta);
	bool jumpRequest;
	long jumpTime;
private:
	Body* getGround();
};