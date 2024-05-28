#define GLM_ENABLE_EXPERIMENTAL
#include "gameLayer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "platformInput.h"
#include "imgui.h"
#include <iostream>
#include <sstream>
#include "imfilebrowser.h"
#include <gl2d/gl2d.h>
#include <platformTools.h>
#include <Shader.h>
#include <Camera.h>

struct GameData
{
	glm::vec2 rectPos = {100,100};

} gameData;

gl2d::Renderer2D renderer;
gl2d::Texture grassTex;
gl2d::Font font;

Shader shaderProgram;
Camera camera;

int width = 0;
int height = 0;

bool initGame()
{
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	//loading the saved data. Loading an entire structure like this makes savind game data very easy.
	platform::readEntireFile(RESOURCES_PATH "gameData.data", &gameData, sizeof(GameData));
	grassTex.loadFromFile(RESOURCES_PATH "test.jpg", true);
	font.createFromFile(RESOURCES_PATH "roboto_black.ttf");
	shaderProgram.CreateFromFile(RESOURCES_PATH "default.vert", RESOURCES_PATH "default.frag");

	width = platform::getFrameBufferSizeX(); //window w
	height = platform::getFrameBufferSizeY(); //window h

	camera.SetupCamera(width, height, glm::vec3(0.0f, 2.0f, 0.0f), 0.005f, 0.02f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	return true;
}

bool gameLogic(float deltaTime)
{
#pragma region init stuff
	int w = 0; int h = 0;
	w = platform::getFrameBufferSizeX(); //window w
	h = platform::getFrameBufferSizeY(); //window h
	
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear screen

	renderer.updateWindowMetrics(w, h);
#pragma endregion


	if (platform::isButtonHeld(platform::Button::A))
	{
		gameData.rectPos.x -= deltaTime * 100;
	}
	if (platform::isButtonHeld(platform::Button::D))
	{
		gameData.rectPos.x += deltaTime * 100;
	}
	if (platform::isButtonHeld(platform::Button::W))
	{
		gameData.rectPos.y -= deltaTime * 100;
	}
	if (platform::isButtonHeld(platform::Button::S))
	{
		gameData.rectPos.y += deltaTime * 100;
	}

	gameData.rectPos = glm::clamp(gameData.rectPos, glm::vec2{0,0}, glm::vec2{w - 100, h - 100});
	//renderer.renderText(glm::vec2(w / 2, h / 2), "blyat cyka", font, { 1.0f, 1.0f, 1.0f, 1.0f });
	renderer.renderRectangle({gameData.rectPos, 100, 100}, grassTex);

	shaderProgram.Activate();

	camera.UpdateMatrix(45.0f, 0.01f, 100.0f);

	renderer.flush();

	//ImGui::ShowDemoWindow();
	ImGui::Begin("Test Imgui");

	ImGui::DragFloat2("Positions", &gameData.rectPos[0]);

	ImGui::End();

	return true;
#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{

	//saved the data.
	platform::writeEntireFile(RESOURCES_PATH "gameData.data", &gameData, sizeof(GameData));

	shaderProgram.Delete();

}