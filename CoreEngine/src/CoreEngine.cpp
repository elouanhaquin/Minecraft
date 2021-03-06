// CoreEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <CoreEngine.h>
#include <MeshRenderer.h>
#include <ShaderCore.h>
#include <Player.h>
#include <SphereCollider.h>
#include <Time.h>
#include <BoxCollider.h>
#include <RigidBody.h>
#include <Chunk.h>

using namespace CoreEngineNS;
using namespace PhysicsEngineNS;
using namespace ChunkNS;

CoreEngine::CoreEngine() : m_renderEngine(nullptr), m_isRunning{ true }, fps{ 0 }
{
	m_currentState = STATE::MENU;
	std::cout << "CoreEngine On" << std::endl;

	world = new World(13, 1);
	world->Populate();
}

CoreEngine::~CoreEngine()
{
	delete m_physicsEngine;
	std::cout << "CoreEngine Off" << std::endl;
}


void CoreEngine::LoadResources()
{
	//Load All Resources needed Flyweight
	ResourceManager::Instance().LoadModel("Cube", "primitives/Cube.obj");

	ResourceManager::Instance().LoadShader("Nano", "NanoSuit/NanoSuit.vert", "NanoSuit/NanoSuit.frag");
	ResourceManager::Instance().LoadShader("WaterEffect", "NanoSuit/waterEffects.vert", "NanoSuit/waterEffects.frag");
	ResourceManager::Instance().LoadShader("LeavesEffect", "NanoSuit/leavesEffects.vert", "NanoSuit/leavesEffects.frag");
	ResourceManager::Instance().LoadShader("SkyBox", "NanoSuit/SkyBox.vert", "NanoSuit/SkyBox.frag");
	ResourceManager::Instance().LoadShader("simpleDepthShader", "NanoSuit/simpleDepthShader.vert", "NanoSuit/simpleDepthShader.frag");
	ResourceManager::Instance().LoadShader("Sun", "NanoSuit/Sun.vert", "NanoSuit/Sun.frag");

	ResourceManager::Instance().LoadTexture("Dirt", "cube.jpg", "Texture");
	//ResourceManager::Instance().LoadTexture("DecorationAtlas", "decorationAtlas.png", "Texture");
	ResourceManager::Instance().LoadTexture("DecorationAtlas", "decorationAtlas2.png", "Texture");
	ResourceManager::Instance().LoadTexture("Atlas", "atlas.jpg", "Texture");
	ResourceManager::Instance().LoadTexture("Sky", "sky.jpg", "Texture");


	ResourceManager::Instance().LoadTexture("NewGame", "Play.jpg", "Texture");
	ResourceManager::Instance().LoadTexture("LoadMap", "LoadMap.png", "Texture");
	ResourceManager::Instance().LoadTexture("Quit", "Quit.jpg", "Texture");


}

void CoreEngine::Setup()
{
	//Bind Input
	BindInput();
	LoadResources();

	if (m_currentState == STATE::PLAY)
	{
		glfwSetInputMode(m_renderEngine->GetWindow()->WindowGLFW(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);	//Disable mouse cursor

																										//Loading Resources
																										//LoadResources();

																										//Create GameObjects
																										//Player 1
		GameObject& player1 = m_scene.AddGameObject<Player>();
		player1.AddComponent<Transform>();
		MeshRenderer& meshRenderer = player1.AddComponent<MeshRenderer>();
		meshRenderer.SetMesh(ResourceManager::Instance().GetModel("Cube"));
		player1.AddComponent<SphereCollider>(1.2f);
		ShaderCore& shader = player1.AddComponent<ShaderCore>();
		shader.SetShader(ResourceManager::Instance().GetShader("Nano"));
		RigidBody& rb = player1.AddComponent<RigidBody>(1);

		//Platform 
		//Todo Need to remove theses and fix ShaderBinding
		GameObject& platform1(m_scene.AddEntity());
		MeshRenderer& platform1Renderer = platform1.AddComponent<MeshRenderer>();
		platform1Renderer.SetMesh(ResourceManager::Instance().GetModel("Cube"));
		ShaderCore& platform1Shader = platform1.AddComponent<ShaderCore>();
		platform1Shader.SetShader(ResourceManager::Instance().GetShader("Nano"));
		platform1.AddComponent<BoxCollider>(glm::vec3(-10, -0.5f, -10), glm::vec3(10, 0.5f, 10));

		GameObject& platform2(m_scene.AddEntity());
		MeshRenderer& platform2Renderer = platform2.AddComponent<MeshRenderer>();
		platform2Renderer.SetMesh(ResourceManager::Instance().GetModel("Cube"));
		ShaderCore& platform2Shader = platform2.AddComponent<ShaderCore>();
		platform2Shader.SetShader(ResourceManager::Instance().GetShader("WaterEffect"));
		platform2.AddComponent<BoxCollider>(glm::vec3(-10, -0.5f, -10), glm::vec3(10, 0.5f, 10));

		GameObject& platform3(m_scene.AddEntity());
		MeshRenderer& platform3Renderer = platform3.AddComponent<MeshRenderer>();
		platform3Renderer.SetMesh(ResourceManager::Instance().GetModel("Cube"));
		ShaderCore& platform3Shader = platform3.AddComponent<ShaderCore>();
		platform3Shader.SetShader(ResourceManager::Instance().GetShader("LeavesEffect"));
		platform3.AddComponent<BoxCollider>(glm::vec3(-10, -0.5f, -10), glm::vec3(10, 0.5f, 10));


		GameObject& platform4(m_scene.AddEntity());
		MeshRenderer& platform4Renderer = platform4.AddComponent<MeshRenderer>();
		platform4Renderer.SetMesh(ResourceManager::Instance().GetModel("Cube"));
		ShaderCore& platform4Shader = platform4.AddComponent<ShaderCore>();
		platform4Shader.SetShader(ResourceManager::Instance().GetShader("SkyBox"));
		platform4.AddComponent<BoxCollider>(glm::vec3(-10, -0.5f, -10), glm::vec3(10, 0.5f, 10));

		GameObject& platform5(m_scene.AddEntity());
		MeshRenderer& platform5Renderer = platform5.AddComponent<MeshRenderer>();
		platform5Renderer.SetMesh(ResourceManager::Instance().GetModel("Cube"));
		ShaderCore& platform5Shader = platform5.AddComponent<ShaderCore>();
		platform5Shader.SetShader(ResourceManager::Instance().GetShader("Sun"));
		platform5.AddComponent<BoxCollider>(glm::vec3(-10, -0.5f, -10), glm::vec3(10, 0.5f, 10));



		RigidBody& platform1RigidBody = platform1.AddComponent<RigidBody>(5);
		platform1RigidBody.IsKinematic() = true;

		m_sceneHierarchy = m_scene.Hierarchy();

		for (auto& gameObject : m_sceneHierarchy)
			gameObject->Awake();

		player1.GetComponent<Transform>().SetPosition(glm::ivec3((world->getWidth() * CHUNK_SIZE) / 2, 50, (world->getWidth() * CHUNK_SIZE) / 2));
		platform4.GetComponent<Transform>().SetPosition(glm::ivec3((world->getWidth() * CHUNK_SIZE) / 2, 50, (world->getWidth() * CHUNK_SIZE) / 2));
		buffPlayerPos = glm::ivec3((world->getWidth() * CHUNK_SIZE) / 2, 50, (world->getWidth()* CHUNK_SIZE) / 2);
		//Transform& platform1Transform = platform1.GetComponent<Transform>();
		//platform1Transform.SetPosition(glm::vec3(0, 10, 0));

		glm::vec3 view = m_renderEngine->GetCamera()->GetFront();
		world->Render(player1.GetComponent<Transform>().GetPosition(), view);
	

	}
	else if (m_currentState == STATE::MENU)
	{
		GameObject& buttonPlay = m_SceneMenu.AddGameObject<UIButton>();
		MeshRenderer& buttonPlayRenderer = buttonPlay.AddComponent<MeshRenderer>();
		buttonPlayRenderer.SetMesh(ResourceManager::Instance().GetModel("Cube"));
		ShaderCore& buttonPlayShader = buttonPlay.AddComponent<ShaderCore>();
		buttonPlayShader.SetShader(ResourceManager::Instance().GetShader("Nano"));

		m_sceneHierarchy = m_SceneMenu.Hierarchy();
		m_Menu = new UIMenu(3, false);

		m_Menu->GetButton(0).SetTexture("NewGame");
		m_Menu->GetButton(1).SetTexture("LoadMap");
		m_Menu->GetButton(2).SetTexture("Quit");
		
	}

}

void CoreEngine::IgniteRenderEngine(const int& p_width, const int& p_height, bool isFullScreen)
{
	m_renderEngine = std::make_unique<RenderEngine>();

	m_renderEngine->SetupWindow(p_width, p_height, isFullScreen);

	Setup();
}

void CoreEngine::IgnitePhysicsEngine()
{
	m_physicsEngine = new PhysicsEngine(&TimeNS::Time::deltaTime);
}

void CoreEngine::Run()
{
	double frameCap = 60;
	double renderTimer = 0;

	double physicsStep = 300;
	double physicsTimer = 0;

	double fpsTimerCount = 0;



	while (m_isRunning && glfwWindowShouldClose(m_renderEngine->GetWindow()->WindowGLFW()) == 0)
	{
		TimeNS::Time::UpdateTime();
		Input::MouseCallBack(m_renderEngine->GetWindow()->WindowGLFW());

		InputHandle();

		//Physics Checks
		if (physicsTimer >= (1 / physicsStep))
		{
			//Fixed Update
			FixedUpdate();
			physicsTimer -= (1 / physicsStep); //Reset
		}

		if (m_currentState == STATE::PLAY)
		{
			//Update Player Forward with Camera ==> DIRTY but what do you want
			m_sceneHierarchy[0]->GetComponent<Transform>().SetForward(m_renderEngine->GetCamera()->GetFront());

			for (auto& gameObject : m_sceneHierarchy)
				gameObject->Update();

			//Update Camera
			m_renderEngine->UpdateCamera(m_sceneHierarchy[0]->GetComponent<Transform>().GetPosition(),
						Input::GetXOffset(), Input::GetYOffset(), Input::GetMovementDirection(),
						m_sceneHierarchy[0]->GetComponent<RigidBody>().IsOnTheFloor(),Input::Sprint(), 
						Input::CreativeMode());
		}

		Update();

		renderTimer += TimeNS::Time::deltaTime;
		physicsTimer += TimeNS::Time::deltaTime;

		fps++;
		if (TimeNS::Time::time - fpsTimerCount >= 1)
		{
			std::cout << "FPS : " << fps << "\n";
			fps = 0;
			fpsTimerCount = TimeNS::Time::time;
		}

		if (TimeNS::Time::deltaTime < 1.0f / frameCap)
		{
			double timerCount = glfwGetTime();
			while (glfwGetTime() - timerCount <= (1 / frameCap) - TimeNS::Time::deltaTime);
		}
	}

	
}

void CoreEngine::Update()
{
	m_renderEngine->BeginFrame();

	//if(m_currentState == STATE::PLAY)
	for (auto& gameObject : m_sceneHierarchy)
		m_renderEngine->Render(gameObject->GetComponent<MeshRenderer>().GetMesh(), gameObject->GetComponent<ShaderCore>().GetShader(), gameObject->GetComponent<Transform>().GetPosition());

	//MEMO C'EST LE SHADER QUI FAIT PRINT LES TRUCS

	if (m_currentState == STATE::MENU)
	{
		if (m_Menu->GetButton(0).isPressed())
			ChangeState("PLAY");
		else if (m_Menu->GetButton(1).isPressed())
		{
			ChangeState("PLAY");
			LoadGame();
		}
		else if (m_Menu->GetButton(2).isPressed())
			ChangeState("QUIT");

		m_Menu->Render();
	}

	if (m_currentState == STATE::PLAY)
	{
		if ((buffPlayerPos.x  < m_sceneHierarchy[0]->GetComponent<Transform>().GetPosition().x
			|| buffPlayerPos.x  > m_sceneHierarchy[0]->GetComponent<Transform>().GetPosition().x)
			|| (buffPlayerPos.z < m_sceneHierarchy[0]->GetComponent<Transform>().GetPosition().z
				|| buffPlayerPos.z > m_sceneHierarchy[0]->GetComponent<Transform>().GetPosition().z)) {

			world->removeChunkAwayFromPlayer(m_sceneHierarchy[0]->GetComponent<Transform>().GetPosition(), m_renderEngine->m_camera->GetFront());
			buffPlayerPos = m_sceneHierarchy[0]->GetComponent<Transform>().GetPosition();
		}

		buffPlayerPos = m_sceneHierarchy[0]->GetComponent<Transform>().GetPosition();

		m_sceneHierarchy[4]->GetComponent<Transform>().SetPosition(glm::vec3(buffPlayerPos.x, 50, buffPlayerPos.z));

		glm::vec3 view = m_renderEngine->GetCamera()->GetFront();
		glm::vec3 pPos = buffPlayerPos;

		world->Draw( view, pPos);
		
	}

	m_renderEngine->EndFrame();
	Input::Reset();
}

void CoreEngine::FixedUpdate()
{

	if (m_currentState != STATE::PLAY)
		return;

	
	std::vector<RigidBody*> rbs = m_scene.GetAllRigidBodies();


	for (auto& gameObject : m_sceneHierarchy)
		gameObject->FixedUpdate();

	for (auto it = m_sceneHierarchy.begin(); it != m_sceneHierarchy.end(); ++it)
	{
		//Apply gravity
		if ((*it)->HasComponent<RigidBody>())
			m_physicsEngine->ApplyGravity((*it)->GetComponent<RigidBody>().GetData());
	}

	
	//buffPlayerPos = m_sceneHierarchy[0]->GetComponent<Transform>().GetPosition();
	

	//world->generateChunkAroundPlayer(m_sceneHierarchy[0]->GetComponent<Transform>().GetPosition());


	// Check collision with block
	/*for (int i = 0; i < world->GetChunks().size(); i++)
	{
		glm::vec3 pos = m_sceneHierarchy[0]->GetComponent<Transform>().GetPosition()  ;
		Block* currBlock = world->GetChunks()[i]->GetBlockAtPosition(pos ) != nullptr && world->GetChunks()[i]->GetBlockAtPosition(pos)->GetID() == ID::Air ? nullptr : world->GetChunks()[i]->GetBlockAtPosition(pos);

		if (currBlock != nullptr) {
			//std::cout << "re" << std::endl;		
			m_sceneHierarchy[0]->GetComponent<RigidBody>().IsOnTheFloor() = true;
			m_sceneHierarchy[0]->GetComponent<RigidBody>().HasGravity() = false;
			m_sceneHierarchy[0]->GetComponent<RigidBody>().IsKinematic() = true;
			//m_sceneHierarchy[0]->GetComponent<RigidBody>().Velocity() = glm::vec3(0, -m_sceneHierarchy[0]->GetComponent<RigidBody>().Velocity().y + 1515,0);
			m_sceneHierarchy[0]->GetComponent<Transform>().SetPositionY(world->GetChunks()[i]->GetPositionArray()[i].y);			
		}
		else {
			m_sceneHierarchy[0]->GetComponent<RigidBody>().IsOnTheFloor() = false;
			m_sceneHierarchy[0]->GetComponent<RigidBody>().HasGravity() = true;
			m_sceneHierarchy[0]->GetComponent<RigidBody>().IsKinematic() = false;
		}
			
	}*/
}

void CoreEngine::FreeResources()
{
	ResourceManager::Instance().FreeResources();
}

void CoreEngine::BindInput()
{
	Input::SetWindowSize(m_renderEngine->WindowWidth(), m_renderEngine->WindowHeight());
	glfwSetKeyCallback(m_renderEngine->GetWindow()->WindowGLFW(), Input::KeyCallBack);
}

void CoreEngine::InputHandle()
{
	if (Input::ShouldClose())
	{
		SaveGame(m_sceneHierarchy[0]->GetComponent<Transform>().GetPosition());
		glfwSetWindowShouldClose(m_renderEngine->GetWindow()->WindowGLFW(), GL_TRUE);
		m_isRunning = false;
	}
}

void CoreEngine::ChangeState(std::string p_Scene)
{

	if (p_Scene == "PLAY" && m_currentState != STATE::PLAY)
	{
		Input::IsMenu() = false;
		m_currentState = STATE::PLAY;
		m_Menu->GetButton(0).setPressed(false);
		m_sceneHierarchy = std::vector<std::shared_ptr<GameObject>>();	//DIRTY MUST DO ANOTHER SCENE
	}
	else if (p_Scene == "MENU" && m_currentState != STATE::MENU)
		m_currentState = STATE::MENU;
	else if (p_Scene == "QUIT")
	{
		glfwSetWindowShouldClose(m_renderEngine->GetWindow()->WindowGLFW(), GL_TRUE);
	}
	else if (p_Scene == "PAUSE")
		return;

	Setup();

}

void CoreEngineNS::CoreEngine::SaveGame(glm::vec3 playerPos)
{
	std::ofstream myfile;
	myfile.open("Saves/PlayerPositionSave.ini");
	myfile << playerPos.x << " " << playerPos.y << " " << playerPos.z;
	myfile.close();
}

void CoreEngineNS::CoreEngine::LoadGame()
{
	std::string playerPos;
	std::ifstream  myfile;
	myfile.open("Saves/PlayerPositionSave.ini");
	float x, y, z;

	myfile >> x >> y >> z ;

	m_sceneHierarchy[0]->GetComponent<Transform>().SetPosition(glm::vec3(x, y, z));
	myfile.close();
}
