#include "Framework/pch.h"
#include "Bat.h"
#include "Ball.h"
#include "Framework/SceneGame.h"
#include <SFML/Graphics.hpp>


int main()
{
    FRAMEWORK.Init(1920, 1080, "Pong");
    FRAMEWORK.Do();
    FRAMEWORK.Release();
    }
