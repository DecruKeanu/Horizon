#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace Horizon;

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

GameObject* Horizon::Scene::GetGameObject(const std::string& identifier)
{
	for (GameObject* const pGameObject : m_pObjects)
	{
		if (pGameObject->GetName() == identifier)
			return pGameObject;
	}

	Logger::LogWarning("Scene::GetGameObject >> GameObject with identifier could not be found, returning nullptr");
	return nullptr;
}

std::vector<GameObject*> Horizon::Scene::GetGameObjects(const std::string& identifier)
{
	std::vector<GameObject*> pIdentifierObjects{};

	for (GameObject* const pGameObject : m_pObjects)
	{
		if (pGameObject->GetName() == identifier)
			pIdentifierObjects.push_back(pGameObject);
	}

	return pIdentifierObjects;
}

