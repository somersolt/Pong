#include "pch.h"
#include "SceneDev2.h"

SceneDev2::SceneDev2(SceneIds id) : Scene(id)
{
}

SceneDev2::~SceneDev2()
{
}

void SceneDev2::Init()
{

}

void SceneDev2::Release()
{
}

void SceneDev2::Enter()
{
}

void SceneDev2::Exit()
{
}


void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SCENEGAME);
	}
}