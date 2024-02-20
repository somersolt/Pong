#pragma once
class TextGo;

class SceneGame : public Scene
{

public:
	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};

protected:

	Status currStatus;

	float timer = 0.f;
	float duration = 3.f;
	int i = 0;
	int life = 3;
	TextGo* score = nullptr;
	TextGo* UI = nullptr;

public:
	bool isBallActive = false;

	SceneGame(SceneIds id);
	virtual ~SceneGame() override;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void UpdateAwake(float dt) ;
	void UpdateGame(float dt) ;
	void UpdateGameOver(float dt) ;
	void UpdatePause(float dt) ;


	void Draw(sf::RenderWindow& window) override;

	void SetStatus(Status newStatus);

};

