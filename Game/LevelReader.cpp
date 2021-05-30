#include "GamePCH.h"
#include "LevelReader.h"
#include <iostream>
#include <Prefab.h>
#include "Cube.h"
#include "QBert.h"
#include "rapidjson.h"
#include "document.h"
#include "stream.h"
#include "filereadstream.h"

using namespace dae;

LevelReader::LevelReader() :
	m_pPrefabs{}
{
	m_Factory.RegisterPrefab<Cube>();
	m_Factory.RegisterPrefab<QBert>();
}

LevelReader::~LevelReader()
{
	for (Prefab* const m_pPrefab : m_pPrefabs)
		SafeDelete(m_pPrefab);
}

//class needs to include namespace and needs to be the same name as cpp 
void LevelReader::ParseLevel(const std::wstring& fileName)
{
	const std::wstring dataPath = L"../Game/Resources/Data/";
	const std::wstring fullPath = dataPath + fileName;

	FILE* pIFile = nullptr;
	_wfopen_s(&pIFile, fullPath.c_str(), L"r");

	if (!pIFile)
	{
		Logger::LogWarning(L"LevelReader::ParseLevel: " + fullPath + L", File could not found");
		return;
	}

	fseek(pIFile, 0, SEEK_END);
	size_t size = ftell(pIFile);
	fseek(pIFile, 0, SEEK_SET);
	char* const readBuffer = new char[size];
	rapidjson::FileReadStream stream(pIFile, readBuffer, size);
	rapidjson::Document doc;
	doc.ParseStream(stream);
	delete[] readBuffer;
	fclose(pIFile);

	using rapidjson::Value;

	const std::string level = doc["level"].GetString();
	const Value::Array& gameObjects = doc["gameObjects"].GetArray();

	for (const rapidjson::Value& gameObject : gameObjects)
		m_pPrefabs.push_back(m_Factory.GetPrefab(gameObject));

	fclose(pIFile);
}

const std::vector<Prefab*>& LevelReader::GetPrefabs() const
{
	return m_pPrefabs;
}