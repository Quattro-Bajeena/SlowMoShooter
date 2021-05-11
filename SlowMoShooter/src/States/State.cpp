#include "stdafx.h"
#include "State.h"

State::State(sf::RenderWindow& window, std::stack<State*>& states)
    :window(window), states(states),
    quit(false), keytime(0), keytimeMax(0.3), clickTime(0), clickTimeMax(0.1),
    scroll(0), scrollActive(false)
{
    window.setMouseCursorVisible(true); 
    gridSize = 192;
}

State::~State()
{
}

const bool State::GetQuit() const
{
    return quit;
}

const bool State::GetKeytime()
{
    if (clickTime >= clickTimeMax) {
        clickTime = 0;
        return true;
    }
    else return false;
}

const bool State::GetClickTime()
{
    if (keytime >= keytimeMax) {
        keytime = 0;
        return true;
    }
    else return false;
}

void State::EndState()
{
    quit = true;
}

void State::UpdateMousePosition(sf::View* view)
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(window);
    
    if (view)
        window.setView(*view);

    mousePosView = window.mapPixelToCoords(mousePosWindow);

    mousePosGrid = sf::Vector2i(
        (int)mousePosView.x / gridSize,
        (int)mousePosView.y / gridSize
    );

    window.setView(window.getDefaultView());
}

void State::UpdateScrollWheel(int ticks)
{
    scroll = ticks;
    scrollActive = true;
}

void State::ResetScrollWheel()
{
    scroll = 0;
    //scrollActive = false; ?
}

void State::UpdateKeytime(const float dt)
{
    if (keytime < keytimeMax) {
        keytime += dt;
    }
    if (clickTime < clickTimeMax) {
        clickTime += dt;
    }
}