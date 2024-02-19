#include "pch.h"
#include "InputMgr.h"

std::map<Axis, AxisInfo> InputMgr::axisInfoMap;
std::list<sf::Keyboard::Key> InputMgr::downList;
std::list<sf::Keyboard::Key> InputMgr::upList;
std::list<sf::Keyboard::Key> InputMgr::ingList;

void InputMgr::Init()
{
    // Horizontal
    AxisInfo infoH;
    infoH.axis = Axis::Horizontal;
    infoH.positives.push_back(sf::Keyboard::D);
    infoH.positives.push_back(sf::Keyboard::Right);
    infoH.negatives.push_back(sf::Keyboard::A);
    infoH.negatives.push_back(sf::Keyboard::Left);
    infoH.sensi = 10.0;
    infoH.value = 0.f;

    axisInfoMap.insert({ infoH.axis, infoH });

    AxisInfo infoV;
    infoV.axis = Axis::vertical;
    infoV.positives.push_back(sf::Keyboard::S);
    infoV.positives.push_back(sf::Keyboard::Down);
    infoV.negatives.push_back(sf::Keyboard::W);
    infoV.negatives.push_back(sf::Keyboard::Up);
    infoV.sensi = 10.0;
    infoV.value = 0.f;

    axisInfoMap.insert({ infoV.axis, infoV });

}

void InputMgr::UpdateEvent(const sf::Event& ev)
{
    
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        if (!GetKey(ev.key.code))
        {
            ingList.push_back(ev.key.code);
            downList.push_back(ev.key.code);
        }
        break;
    case sf::Event::KeyReleased:
        ingList.remove(ev.key.code);
        upList.push_back(ev.key.code);
        break;

    case sf::Event::MouseButtonPressed:
        if (!GetMouseButton(ev.mouseButton.button))
        {
            ingList.push_back(ev.key.code);
            downList.push_back(ev.key.code);
        }
        break;
    case sf::Event::MouseButtonReleased:
        ingList.remove(ev.key.code);
        upList.push_back(ev.key.code);
        break;
    }
}

void InputMgr::Update(float dt)
{
    for (auto& pair : axisInfoMap) // 여기랑
    {
        AxisInfo& axisInfo = pair.second; // 여기는 컨테이너를 수정할 용도로 &붙이기 안붙이면 복사됨
        float raw = GetAxisRaw(axisInfo.axis); // -1 0 1
        float speed = raw;  
        if (speed == 0.f && axisInfo.value != 0.f) // 입력이 없고 속도가 있으면, 0에 가까워지게 속도 떨어짐
        {
            speed = axisInfo.value > 0.f ? -1.f : 1.f;
        }
        axisInfo.value += speed * axisInfo.sensi * dt; // speed 라지만 입력(방향) * 예민도 * dt 
        axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f); // -1 , 1 못넘게 막음

        if (raw == 0.f && abs(axisInfo.value) < 1.f / 60.f)  // 0에 가까워질때, 입력이 없으면 0으로 고정. raw는 입력임
        {
            axisInfo.value = 0.f;
        }
    }




    if (InputMgr::GetMouseButton(sf::Mouse::Button::Left))
    {
        ingList.push_back(sf::Keyboard::Left);
        downList.push_back(sf::Keyboard::Left);
    }
    if (InputMgr::GetMouseButtonUp(sf::Mouse::Button::Left))
    {
        ingList.remove(sf::Keyboard::Left);
        upList.push_back(sf::Keyboard::Left);
    }
    if (InputMgr::GetMouseButton(sf::Mouse::Button::Right))
    {
        ingList.push_back(sf::Keyboard::Right);
        downList.push_back(sf::Keyboard::Right);
    }
    if (InputMgr::GetMouseButtonUp(sf::Mouse::Button::Right))
    {
        ingList.remove(sf::Keyboard::Right);
        upList.push_back(sf::Keyboard::Right);
    }
}

void InputMgr::Clear()
{
    downList.clear();
    upList.clear();
}

float InputMgr::GetAxisRaw(Axis axis)
{
    auto findInfo = axisInfoMap.find(axis);
    if (findInfo == axisInfoMap.end())
        return 0.f;
    const AxisInfo& info = findInfo->second;
    auto it = ingList.rbegin();
    while (it != ingList.rend())
    {
        sf::Keyboard::Key key = *it;
        if (std::find(info.positives.begin(), info.positives.end(), key)
            != info.positives.end())
        {
            return 1.0f;
        }
        if (std::find(info.negatives.begin(), info.negatives.end(), key)
            != info.negatives.end())
        {
            return -1.0f;
        }
        ++it;
    }

    return 0.0f;
}

float InputMgr::GetAxis(Axis axis)
{
    auto findInfo = axisInfoMap.find(axis);
    if (findInfo == axisInfoMap.end())
        return 0.f;

    return findInfo->second.value;
}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
    return std::find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
    return std::find(upList.begin(), upList.end(), key) != upList.end();
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
    return std::find(ingList.begin(), ingList.end(), key) != ingList.end();
}



const sf::Vector2f& InputMgr::GetMousePos()
{
    sf::Vector2f temp(sf::Mouse::getPosition());
    std::cout << "{" << temp.x << "," << temp.y << "}" << std::endl;

    return temp;
}

bool InputMgr::GetMouseButtonDown(sf::Mouse::Button key)
{
    return std::find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputMgr::GetMouseButtonUp(sf::Mouse::Button key)
{
    return std::find(upList.begin(), upList.end(), key) != upList.end();
}

bool InputMgr::GetMouseButton(sf::Mouse::Button key)
{
    return std::find(ingList.begin(), ingList.end(), key) != ingList.end();
}

