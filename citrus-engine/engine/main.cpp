#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <chrono>
#include <cstdint>

#include "gfx/Shader.h"
#include "gfx/Texture.h"
#include "gfx/TESTING.h"
#include "gfx/Camera.h"
#include "app/CameraController.h"
#include "core/Cube.h"



using namespace citrus;

//float vertices[] = {
//	//-.5f, -.5f, .0f,
//	// .5f, -.5f, .0f,
//	// .0f,  .5f, .0f
//	 0.5f,  0.5f, 0.0f,  // top right
//	 0.5f, -0.5f, 0.0f,  // bottom right
//	-0.5f, -0.5f, 0.0f,  // bottom left
//	//-0.5f,  0.5f, 0.0f   // top left 
//};

float vertices[] = {
	// positions			// colours			// texture coordinates
	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.5f, 1.0f,
};

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	//1, 2, 3    // second triangle
};

float texCoord[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.5f, 1.0f
};

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"	FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

#define WINDOW_WIDTH 800.f
#define WINDOW_HEIGHT 600.f

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// setup window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "citrus", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}
	
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// z-depth

	glEnable(GL_DEPTH_TEST);

	citrus::gfx::Shader* shad = new citrus::gfx::Shader("test shader");
	shad
		->Attach("assets/shaders/shader.vert")
		->Attach("assets/shaders/shader.frag")
		->Link();

	citrus::gfx::Shader* lightShad = new citrus::gfx::Shader("light shader");
	lightShad
		->Attach("assets/shaders/shader.vert")
		->Attach("assets/shaders/lightshader.frag")
		->Link();

	//objects

	core::Cube* cube = new core::Cube();
	core::Cube* lightCube = new core::Cube();
	lightCube->GetTransform().SetScale(0.5f);
	lightCube->GetTransform().SetPosition(glm::vec3(1.f, 1.f, -1.f));

	// cameras
	citrus::gfx::Camera* camera = new citrus::gfx::Camera(60.0f, WINDOW_WIDTH / WINDOW_HEIGHT);
	app::CameraController cameraController{ *camera };
	camera->Translate({ 0.f,0.f,3.0f });

	using Clock = std::chrono::steady_clock;

	Clock::time_point last = Clock::now();
	double delta = 0.0f;


	// run loop
	while (!glfwWindowShouldClose(window)) {
		
		// time.tick
		const auto now = Clock::now();
		float raw = std::chrono::duration<float>(now - last).count();
		last = now;
		delta = raw;
		//printf("%f\n", delta);

		// update
		//model = glm::rotate(model, (float)delta * glm::radians(100.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		cube->GetTransform().Rotate(delta * glm::radians(100.f), glm::vec3(0.5f, 1.0f, 0.0f));

		//std::cout << glm::to_string(cube->GetTransform().Rotation()) << std::endl;

		// input handling
		processInput(window);
		cameraController.Update(window, delta);

		// rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shad->Bind();
		//shad->Set("transform", trans);
		cube->Draw(*shad);

		lightShad->Bind();
		//lightShad->Set("objectColour", glm::vec3(1.0f, 0.5f, 0.31f));
		//lightShad->Set("lightColour", glm::vec3(1.0f, 1.0f, 1.0f));
		lightCube->Draw(*lightShad);
		camera->Apply(*lightShad);
		//shad->Set("view", view);

		shad->Bind();
		camera->Apply(*shad);
		//shad->Set("projection", projection);
		//float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//glm::vec4 c = { .0f, greenValue, .0f, 1.f, };
		shad->Set("colour", glm::vec4(1.f,1.f,1.f,1.f));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
