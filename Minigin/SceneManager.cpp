#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

dae::SceneManager::~SceneManager()
{
	for (auto& scene : m_pScenes)
		SafeDelete(scene);
}


void dae::SceneManager::Initialize()
{
	for (auto& scene : m_pScenes)
		scene->RootInitialize();
}

void dae::SceneManager::FixedUpdate()
{
	for (auto& scene : m_pScenes)
		scene->RootFixedUpdate();
}

void dae::SceneManager::Update()
{
	for (auto& scene : m_pScenes)
		scene->RootUpdate();
}

void dae::SceneManager::LateUpdate()
{
	for (auto& scene : m_pScenes)
		scene->RootLateUpdate();
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_pScenes)
		scene->RootRender();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	m_pScenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::AddScene(Scene* pScene)
{
	const auto it = find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it == m_pScenes.end())
	{
		m_pScenes.push_back(pScene);

		//if (m_IsInitialized)
		//	pScene->RootInitialize(m_pDevice, m_pDeviceContext);

		//if (m_ActiveScene == nullptr && m_NewActiveScene == nullptr)
		//	m_NewActiveScene = pScene;
	}
}
