#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) 
{

}

Scene::~Scene()
{
	for (size_t idx{}; idx < m_pObjects.size(); idx++)
		SafeDelete<GameObject>(m_pObjects[idx]);
}

void Scene::Add(GameObject* object)
{
	m_pObjects.push_back(object);
}

void Scene::BeginPlay()
{
	for (auto& object : m_pObjects)
		object->BeginPlay();
}

void Scene::FixedUpdate()
{
	for(auto& object : m_pObjects)
		object->FixedUpdate();
}

void Scene::Update()
{
	for (auto& object : m_pObjects)
		object->Update();
}

void Scene::LateUpdate()
{
	for (auto& object : m_pObjects)
		object->LateUpdate();
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

