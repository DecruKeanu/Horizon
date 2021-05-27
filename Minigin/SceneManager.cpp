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
	if (m_pActiveScene)
		m_pActiveScene->RootRender();
}

void dae::SceneManager::AddScene(Scene* pScene)
{
	const auto it = find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it == m_pScenes.end())
	{
		m_pScenes.push_back(pScene);

		if (m_pActiveScene == nullptr)
			m_pActiveScene = pScene;
	}
}

void dae::SceneManager::RemoveScene(Scene* pScene)
{
	const auto it = find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it != m_pScenes.end())
	{
		delete* it;
		m_pScenes.erase(it);
	}
}

void dae::SceneManager::SetActiveScene(Scene* pScene)
{
	const auto it = find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it != m_pScenes.end())
	{
		m_pActiveScene = pScene;
	}
}

//void dae::SceneManager::NextScene()
//{
//	for (unsigned int i = 0; i < m_pScenes.size(); ++i)
//	{
//		const auto nextScene = ++i % m_pScenes.size();
//		m_pActiveScene = m_pScenes[nextScene];
//		break;
//	}
//}
//
//void dae::SceneManager::PreviousScene()
//{
//}
