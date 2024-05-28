#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <Shader.h>

#define GLM_ENABLE_EXPERIMENTAL

class Camera
{
public:
	//Camera constructor to set inital values
	Camera(int width, int height, glm::vec3 position, float normalSpeed, float fastSpeed);
	Camera() = default;

	void SetupCamera(int width, int height, glm::vec3 position, float normalSpeed, float fastSpeed);

	glm::vec3 position;
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);

	// Updates and exports the camera matrix to the vertex shader
	void Matrix(Shader& shader, const char* uniform);
	// Handles the Input for the camera
	void HandleInput(GLFWwindow* window);

	//Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	//Stores the width and height of the window
	int width;
	int height;

	//Speed of the camera
	float normalCamSpeed = 0.01f;
	float fastCamSpeed = 0.04f;
	float speed = normalCamSpeed;

	//Stores the sensitivity of the camera
	float sensitivity = 100.0f;
};