#include "localWindow.h"

using namespace XE;

void LocalWindow::initializeScene()
{
	glClearColor(0.0f, 0.28f, 0.57f, 1.0f);

	try
	{
		//auto& sm = ShaderManager::getInstance();
		auto& spm = ShaderProgramManager::getInstance();
		auto& tm = TextureManager::getInstance();

		//sm.loadShaders("simple", "../shaders/figure3D");

		spm.createShaderProgram("figure3D", "../shaders/common/figure3D");
		//simpleProgram.addShadersToProgram("../shaders/figure3D");
		//simpleProgram.addShaderToProgram(sm.getVertexShader("simple"));
		//simpleProgram.addShaderToProgram(sm.getFragmentShader("simple"));
		//spm.linkAllPrograms();

		SamplerManager::getInstance().createSampler("main", MAG_FILTER_BILINEAR, MIN_FILTER_TRILINEAR);
		tm.loadTexture2D("diamond", "../textures/diamond.png");
		tm.loadTexture2D("ice", "../textures/ice.png");

		//auto& sm = ShaderManager::getInstance();
		//auto& spm = ShaderProgramManager::getInstance();
		//auto& tm = TextureManager::getInstance();

		//sm.loadVertexShader("figures", "../shaders/figures.vert");
		//sm.loadFragmentShader("figures", "../shaders/figures.frag");

		//auto& mainShaderProgram = spm.createShaderProgram("main");
		//mainShaderProgram.addShaderToProgram(sm.getVertexShader("figures"));
		//mainShaderProgram.addShaderToProgram(sm.getFragmentShader("figures"));
		//spm.linkAllPrograms();
		//SamplerManager::getInstance().createSampler("main", MAG_FILTER_BILINEAR, MIN_FILTER_TRILINEAR);

		//TextureManager::getInstance().loadTexture2D("diamond", "../textures/diamond.png");
		//TextureManager::getInstance().loadTexture2D("metal", "../textures/metal.png");
		//TextureManager::getInstance().loadTexture2D("ice", "../textures/ice.png");

		Cubo = std::make_unique<Cube>();
		Cubo->scale(10);
		Cubo->translate(glm::vec3(0,5,0));

		Conejo = std::make_unique<Model>("../models/house/medieval_house.obj", "medieval_house_diff.png", true, true, true);
		Conejo->scale(0.1);
		Conejo->translate(glm::vec3(0, 0, 0));
		//Pyramid = std::make_unique<static_meshes_3D::Pyramid>(true, true, false);
		//Torus = std::make_unique<static_meshes_3D::Torus>(50, 50, 3.0f, 1.5f, true, true, false);
		//PlainGround = std::make_unique<static_meshes_3D::PlainGround>(true, true, false);
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << "Error occured during initialization: " << ex.what() << std::endl;
		closeWindow(true);
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
}

void LocalWindow::renderScene()
{
	const auto& spm = ShaderProgramManager::getInstance();
	const auto& tm = TextureManager::getInstance();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up some common properties in the main shader program
	auto& mainProgram = spm.getShaderProgram("figure3D");
	mainProgram.useProgram();
	SamplerManager::getInstance().getSampler("main").bind();

	mainProgram[ShaderConstants::projectionMatrix()] = getProjectionMatrix();
	mainProgram[ShaderConstants::viewMatrix()] = Camera.getViewMatrix();

	//porfa->render();
	//TextureManager::getInstance().getTexture("ice").bind(0);
	//Conejo->render();

	//mainProgram[ShaderConstants::modelMatrix()] = glm::translate(Cubo->getModelMatrix(), glm::vec3(15,0,0));
	TextureManager::getInstance().getTexture("ice").bind(0);
	TextureManager::getInstance().getTexture("diamond").bind(1);
	Cubo->setDiffuse("diamond");
	Cubo->render();


	//// Render icy ground
	//TextureManager::getInstance().getTexture("ice").bind(0);
	//PlainGround->render();

	//for (const auto& position : objectPositions)
	//{
	//	// Render diamond pyramid on bottom
	//	const auto pyramidSize = 10.0f;
	//	auto posModelMatrix = glm::translate(glm::mat4(1.0f), position);
	//	auto model = glm::translate(posModelMatrix, glm::vec3(0.0f, pyramidSize / 2.0f, 0.0f));
	//	model = glm::scale(model, glm::vec3(pyramidSize, pyramidSize, pyramidSize));
	//	mainProgram[ShaderConstants::modelMatrix()] = model;

	//	TextureManager::getInstance().getTexture("diamond").bind(0);
	//	Pyramid->render();

	//	// Render metal torus on top of the pyramid
	//	const auto torusOffset = pyramidSize + Torus->getMainRadius() + Torus->getTubeRadius();
	//	model = glm::translate(posModelMatrix, glm::vec3(0.0f, torusOffset, 0.0f));
	//	model = glm::rotate(model, rotationAngleRad, glm::vec3(0.0f, 1.0f, 0.0f));
	//	mainProgram[ShaderConstants::modelMatrix()] = model;

	//	TextureManager::getInstance().getTexture("metal").bind(0);
	//	Torus->render();
	//}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Test");
	ImGui::Text("Hello World");
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void LocalWindow::updateScene()
{
	if (keyPressedOnce(GLFW_KEY_ESCAPE))
	{
		closeWindow();
	}

	if (keyPressedOnce(GLFW_KEY_F3)) 
	{
		setVerticalSynchronization(!isVerticalSynchronizationEnabled());
	}

	int posX, posY, width, height;
	glfwGetWindowPos(getWindow(), &posX, &posY);
	glfwGetWindowSize(getWindow(), &width, &height);
	Camera.setWindowCenterPosition(glm::i32vec2(posX + width / 2, posY + height / 2));

	Camera.update();

	std::string windowTitleWithFPS = "X Engine: " + std::to_string(getFPS()) 
	    + ", VSync: " + (isVerticalSynchronizationEnabled() ? "On" : "Off") + " (Press F3 to toggle)"
		+ " (Press F3 to toggle)";
	glfwSetWindowTitle(getWindow(), windowTitleWithFPS.c_str());

	// Update rotation angle
	rotationAngleRad += sof(glm::radians(135.0f));
}

void LocalWindow::releaseScene()
{
	ShaderManager::getInstance().clearShaderCache();
	ShaderProgramManager::getInstance().clearShaderProgramCache();
	TextureManager::getInstance().clearTextureCache();
	SamplerManager::getInstance().clearSamplerCache();

	//Pyramid.reset();
	//Torus.reset();
	//PlainGround.reset();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

}
