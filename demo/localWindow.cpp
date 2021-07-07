#include "localWindow.h"

using namespace XE;

void LocalWindow::initializeScene()
{
	glClearColor(0.0f, 0.28f, 0.57f, 1.0f);

	try
	{
		auto& sm = ShaderManager::getInstance();
		auto& spm = ShaderProgramManager::getInstance();
		auto& tm = TextureManager::getInstance();

		sm.loadVertexShader("figures", "../shaders/figures.vert");
		sm.loadFragmentShader("figures", "../shaders/figures.frag");

		auto& mainShaderProgram = spm.createShaderProgram("main");
		mainShaderProgram.addShaderToProgram(sm.getVertexShader("figures"));
		mainShaderProgram.addShaderToProgram(sm.getFragmentShader("figures"));
		spm.linkAllPrograms();
		SamplerManager::getInstance().createSampler("main", MAG_FILTER_BILINEAR, MIN_FILTER_TRILINEAR);

		TextureManager::getInstance().loadTexture2D("diamond", "../textures/diamond.png");
		TextureManager::getInstance().loadTexture2D("metal", "../textures/metal.png");
		TextureManager::getInstance().loadTexture2D("ice", "../textures/ice.png");

		Pyramid = std::make_unique<static_meshes_3D::Pyramid>(true, true, false);
		Torus = std::make_unique<static_meshes_3D::Torus>(50, 50, 3.0f, 1.5f, true, true, false);
		PlainGround = std::make_unique<static_meshes_3D::PlainGround>(true, true, false);
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
	auto& mm = MatrixManager::getInstance();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set matrices in matrix manager
	mm.setProjectionMatrix(getProjectionMatrix());
	mm.setViewMatrix(Camera.getViewMatrix());

	// Set up some common properties in the main shader program
	auto& mainProgram = spm.getShaderProgram("main");
	mainProgram.useProgram();
	SamplerManager::getInstance().getSampler("main").bind();
	mainProgram[ShaderConstants::projectionMatrix()] = getProjectionMatrix();
	mainProgram[ShaderConstants::viewMatrix()] = Camera.getViewMatrix();
	mainProgram[ShaderConstants::modelMatrix()] = glm::mat4(1.0f);
	mainProgram[ShaderConstants::color()] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	mainProgram[ShaderConstants::sampler()] = 0;

	// Render icy ground
	TextureManager::getInstance().getTexture("ice").bind(0);
	PlainGround->render();

	for (const auto& position : objectPositions)
	{
		// Render diamond pyramid on bottom
		const auto pyramidSize = 10.0f;
		auto posModelMatrix = glm::translate(glm::mat4(1.0f), position);
		auto model = glm::translate(posModelMatrix, glm::vec3(0.0f, pyramidSize / 2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(pyramidSize, pyramidSize, pyramidSize));
		mainProgram[ShaderConstants::modelMatrix()] = model;

		TextureManager::getInstance().getTexture("diamond").bind(0);
		Pyramid->render();

		// Render metal torus on top of the pyramid
		const auto torusOffset = pyramidSize + Torus->getMainRadius() + Torus->getTubeRadius();
		model = glm::translate(posModelMatrix, glm::vec3(0.0f, torusOffset, 0.0f));
		model = glm::rotate(model, rotationAngleRad, glm::vec3(0.0f, 1.0f, 0.0f));
		mainProgram[ShaderConstants::modelMatrix()] = model;

		TextureManager::getInstance().getTexture("metal").bind(0);
		Torus->render();
	}
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

	Camera.update([this](int keyCode) {return this->keyPressed(keyCode); },
		[this]() {double curPosX, curPosY; glfwGetCursorPos(this->getWindow(), &curPosX, &curPosY); return glm::u32vec2(curPosX, curPosY); },
		[this](const glm::i32vec2& pos) {glfwSetCursorPos(this->getWindow(), pos.x, pos.y); },
		[this](float f) {return this->sof(f); });

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

	Pyramid.reset();
	Torus.reset();
	PlainGround.reset();

}
