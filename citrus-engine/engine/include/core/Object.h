#pragma once

#include <glad/glad.h>
#include "core/Transform.h"

namespace citrus::core {
class Object {
public:
	Object();
	~Object();

	void LoadModel();

	void Draw();

private:
	GLuint VAO;
};
}