#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

Horizon::SceneManager::~SceneManager()
{
	for (auto& scene : m_pScenes)
		SafeDelete(scene);
}

void Horizon::SceneManager::Initialize()
{
	for (auto& scene : m_pScenes)
		scene->RootInitialize();

	m_Initialized = true;
}

void Horizon::SceneManager::FixedUpdate()
{
	if (m_pActiveScene)
		m_pActiveScene->RootFixedUpdate();
	//for (auto& scene : m_pScenes)
	//	scene->RootFixedUpdate();
}

void Horizon::SceneManager::Update()
{
	if (m_pActiveScene)
		m_pActiveScene->RootUpdate();
	//for (auto& scene : m_pScenes)
	//	scene->RootUpdate();
}

void Horizon::SceneManager::LateUpdate()
{
	if (m_pActiveScene)
		m_pActiveScene->RootLateUpdate();
	//for (auto& scene : m_pScenes)
	//	scene->RootLateUpdate();
}

void Horizon::SceneManager::Render()
{
	if (m_pActiveScene)
		m_pActiveScene->RootRender();
}

void Horizon::SceneManager::AddScene(Scene* pScene)
{
	const auto it = find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it == m_pScenes.end())
	{
		m_pScenes.push_back(pScene);

		if (m_Initialized)
			pScene->RootInitialize();

		if (m_pActiveScene == nullptr)
			m_pActiveScene = pScene;
	}
}

void Horizon::SceneManager::RemoveScene(Scene* pScene)
{
	const auto it = find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it != m_pScenes.end())
	{
		delete* it;
		m_pScenes.erase(it);
	}
}

void Horizon::SceneManager::SetActiveScene(Scene* pScene)
{
	const auto it = find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it != m_pScenes.end())
	{
		m_pActiveScene = pScene;
	}
}

Horizon::Scene* Horizon::SceneManager::GetActiveScene() const
{
	return m_pActiveScene;
}

void Horizon::SceneManager::NextScene()
{
	for (unsigned int i = 0; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i] == m_pActiveScene)
		{
			const auto nextScene = ++i % m_pScenes.size();
			m_pActiveScene = m_pScenes[nextScene];
			break;
		}
	}
}
//
//void dae::SceneManager::PreviousScene()
//{
//}
