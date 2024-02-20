#include "pch.h"
#include "Scene.h"

Scene::Scene(SceneIds id) : id(id) , texResMgr(ResourceMgr<sf::Texture>::Instance()), fontResMgr(ResourceMgr<sf::Font>::Instance())
{
}

void Scene::Release()
{
	for (auto& obj : gameObjects)
	{
		delete obj;
	}
	gameObjects.clear();
}

void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
}

void Scene::Update(float dt)
{
	for (auto& obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	for (auto& obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}
}

GameObject* Scene::FindGo(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->name == name)
		{
			return obj;
		}
	}
	return nullptr;
}

bool Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list)
{
	bool isFind = false;
	list.clear();
	for (auto obj : gameObjects)
	{
		if (obj->name == name)
		{
			list.push_back(obj);
		}
	}
	return list.size();
}

GameObject* Scene::AddGo(GameObject* obj)
{
	if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
	{
		gameObjects.push_back(obj);
		return obj;
	}
	return nullptr;
}

void Scene::RemoveGo(GameObject* obj)
{

	gameObjects.remove(obj);
}
