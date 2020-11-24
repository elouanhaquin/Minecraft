#pragma once

#include "CoreEngineAPI.h"
#include <RenderEngine.h>
#include <Input.h>
#include <GameObject.h>
#include <Transform.h>
#include <Scene.h>
#include <ResourceManager.h>	//Singleton
#include <PhysicsEngine.h>
#include <Chunk.h>
#include <World.h>
#include "UIMenu.h"

using namespace RenderEngineNS;
using namespace PhysicsEngineNS;
using namespace ChunkNS;
using namespace WorldNS;

namespace CoreEngineNS
{
	class COREENGINE_API CoreEngine
	{
	private:
		std::unique_ptr<RenderEngine> m_renderEngine;
		PhysicsEngine* m_physicsEngine;
		Scene m_scene;
		Scene m_SceneMenu;
		UIMenu* m_Menu;
		std::vector<std::shared_ptr<GameObject>> m_sceneHierarchy;

		Chunk* chunk;
		World* world;

		bool m_isRunning;

		enum STATE { MENU, PLAY, PAUSE };
		STATE m_currentState;

		int fps;

	public:
		
		CoreEngine();
		~CoreEngine();
		
		

		void Setup();
		void IgniteRenderEngine(const int& p_width, const int& p_height, bool isFullScreen);
		void IgnitePhysicsEngine();
		void Run();
		void Update();
		void FixedUpdate();

		void LoadResources();
		void FreeResources();

		void BindInput();
		void InputHandle();

		void ChangeState(std::string p_Scene);

		void SaveGame(glm::vec3 playerPos);
		void LoadGame();
	};
}