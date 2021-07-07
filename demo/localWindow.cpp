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

		House = std::make_unique<static_meshes_3D::House>();
		Snowground = std::make_unique<static_meshes_3D::SnowCoveredPlainGround>(true, true, true);

		HUD = std::make_unique<HUD010>(*this);
		spm.linkAllPrograms();

		SamplerManager::getInstance().createSampler("main", MAG_FILTER_BILINEAR, MIN_FILTER_TRILINEAR);
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
	mm.setOrthoProjectionMatrix(getOrthoProjectionMatrix());
	mm.setViewMatrix(Camera.getViewMatrix());

	Snowground->render();

	// Render all houses
	auto& mainProgram = spm.getShaderProgram("main");
	mainProgram.useProgram();
	SamplerManager::getInstance().getSampler("main").bind();
	mainProgram[ShaderConstants::projectionMatrix()] = getProjectionMatrix();
	mainProgram[ShaderConstants::viewMatrix()] = Camera.getViewMatrix();
	mainProgram[ShaderConstants::color()] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	mainProgram[ShaderConstants::sampler()] = 0;

	for (auto& houseTransformation : houseTransformations)
	{
		House->render(houseTransformation.position, houseTransformation.angle);
	}

	// Render HUD
	HUD->renderHUD();
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

	if (keyPressedOnce(GLFW_KEY_F4))
	{
		HUD->toggleBlending();
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
		+ +", Blending: " + (HUD->isBlendingEnabled() ? "On" : "Off") + " (Press F4 to toggle)";
	glfwSetWindowTitle(getWindow(), windowTitleWithFPS.c_str());
}

void LocalWindow::releaseScene()
{
	ShaderManager::getInstance().clearShaderCache();
	ShaderProgramManager::getInstance().clearShaderProgramCache();
	TextureManager::getInstance().clearTextureCache();
	SamplerManager::getInstance().clearSamplerCache();

	House.reset();
	Snowground.reset();
	//HUD.reset();

}
