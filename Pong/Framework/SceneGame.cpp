#include "pch.h"
#include "SceneGame.h"
#include "SpriteGo.h"
#include "../Ball.h"
#include "../Bat.h"
#include "TextGo.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
}

SceneGame::~SceneGame()
{

}

void SceneGame::Init()
{
	RES_MGR_FONT.Load("fonts/DS-DIGI.ttf");
	Bat* bat = new Bat("bat");
	AddGo(bat);

	Ball* ball = new Ball(*bat ,{ { 0.f, 0.f }, { 1920.f, 1080.f } }, "ball");
	AddGo(ball);

	score = new TextGo("score");
	score->Set(RES_MGR_FONT.Get("fonts/DS-DIGI.ttf"), 40, "Score : 0    lives : 3", sf::Color::White);
	AddGo(score);

	UI = new TextGo("ui");
	UI->Set(RES_MGR_FONT.Get("fonts/DS-DIGI.ttf"), 70, "Press Enter To Start", sf::Color::White);
	UI->SetOrigin(Origins::MC);
	UI->SetPosition({ 1920.f / 2.f , 1080.f / 2.f });
	AddGo(UI);

	for (GameObject* obj : gameObjects)
	{
		obj->Init();
	}

}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();
	SetStatus(Status::Awake);
}

void SceneGame::Exit()
{
	FRAMEWORK.SetTimeScale(1.f);
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	switch (currStatus)
	{
	case Status::Awake:
		UpdateAwake(dt);
		break;
	case Status::Game:
		UpdateGame(dt);
		break;
	case Status::GameOver:
		UpdateGameOver(dt);
		break;
	case Status::Pause:
		UpdatePause(dt);
		break;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num5))
	{
		SCENE_MGR.ChangeScene(SceneIds::SCENEDEV1);
	}
}

void SceneGame::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
		UI->SetActive(false);
	}
}

void SceneGame::UpdateGame(float dt)
{
	GameObject* findBall = FindGo("ball");
	Ball* ball = dynamic_cast<Ball*>(findBall);
	GameObject* findBat = FindGo("bat");
	Bat* bat= dynamic_cast<Bat*>(findBat);

	score->SetString("Score : " + std::to_string(i) + "    Lives : " + std::to_string(life));


	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	//{
	//	std::cout << "hey" << std::endl;
	//}


	if (!isBallActive && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		ball->fire({ -1.f , 1.f }, -1000.f);
		isBallActive = true;
	}

	if (!isBallActive)
	{
		ball->shape.setPosition(bat->shape.getPosition());
	}

	if (ball->isDead)
	{
		isBallActive = false;
		life -= 1;
		ball->fire({ 0.f ,0.f }, 0.f);
	}
	else if (ball->isBoundBat)
	{
		ball->isBoundBat = false;
		i += 100;
	}
	if (life == 0)
	{
		SetStatus(Status::GameOver);
		UI->SetString("Game Over! Press Enter To Restart");
		UI->SetActive(true);
	}


	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
	}
}

void SceneGame::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
		UI->SetActive(false);
		for (GameObject* obj : gameObjects)
		{
			obj->Reset();
		}
		i = 0;
		life = 3;
	}

}

void SceneGame::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::SetStatus(Status newStatus)
{
	Status prevStatus = currStatus;
	currStatus = newStatus;

	switch (currStatus)
	{
	case Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case Status::Game:
		FRAMEWORK.SetTimeScale(1.f);
		break;
	case Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	}
}
