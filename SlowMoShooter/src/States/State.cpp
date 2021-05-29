#include "stdafx.h"
#include "State.h"

State::State(sf::RenderWindow& window, std::stack<State*>& states)
    :window(window), states(states),
    quit(false), 
    scroll(0), scrollActive(false)
{
    window.setMouseCursorVisible(true); 
    keyTimer = Timer(0.3);
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
    return keyTimer.Ready();
}

void State::EndState()
{
    music.stop();
    quit = true;
}

void State::UpdateMousePosition(sf::View* view)
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(window);
    
    if (view)
        window.setView(*view);

    mousePosView = window.mapPixelToCoords(mousePosWindow);


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
    keyTimer.Update(dt);
}
