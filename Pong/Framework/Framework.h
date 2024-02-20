#pragma once
#include "singleton.h"
//게임의 메인 형태를 함수로 만드는 클래스

// 1. 초기화 / 메인루프 / 정리 (릴리즈)
// 2. 시간 관련 기능
// 3. ...Mgr 초기화 ,정리 등등의 관리

class Framework : public Singleton<Framework>
{
	friend class Singleton<Framework>;

protected:
	Framework() = default;
	virtual ~Framework() = default;

	sf::RenderWindow window;
	sf::Vector2i windowSize;
	
	sf::Clock clock;
	float timeScale = 1.f;

	sf::Time realTime; //게임 시작부터 경과시간
	sf::Time time; //게임 시작부터 경과시간 (timeScale 적용된)
	
	sf::Time realDeltaTime;
	sf::Time deltaTime;

public:
	sf::RenderWindow& GetWindow() { return window; } // !!
	const sf::Vector2i& GetWindowSize() const { return windowSize; }
	float GetDT() const { return deltaTime.asSeconds(); };
	float GetRealDT() const { return realDeltaTime.asSeconds(); };
	
	float GetTime() const { return time.asSeconds(); };
	float GetRealTime() const { return realTime.asSeconds(); };

	float GetTimeScale() const { return timeScale; }
	void SetTimeScale(float scale) { timeScale = scale; }

	virtual void Init(int width, int height, const std::string& name = "Game");
	virtual void Do();
	virtual void Release();

};

#define FRAMEWORK (Singleton<Framework>::Instance())