#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) :
	m_Name(name),
	m_IsInitialized{ false }
{

}

Scene::~Scene()
{
	for (size_t idx{}; idx < m_pObjects.size(); idx++)
		SafeDelete<GameObject>(m_pObjects[idx]);
}

void Scene::Add(GameObject* object)
{
	if (m_IsInitialized)
		object->Initialize();

	m_pObjects.push_back(object);
}

void Scene::RootInitialize()
{
	Initialize();

	for (GameObject* const object : m_pObjects)
		object->Initialize();
}

void Scene::RootFixedUpdate()
{
	FixedUpdate();

	for (GameObject* const object : m_pObjects)
		object->FixedUpdate();
}

void Scene::RootUpdate()
{
	Update();

	for (GameObject* const object : m_pObjects)
		object->Update();
}

void Scene::RootLateUpdate()
{
	LateUpdate();

	for (GameObject* const object : m_pObjects)
		object->LateUpdate();
}

void Scene::RootRender() const
{
	Render();

	for (GameObject* const object : m_pObjects)
	{
		object->Render();
	}
}

