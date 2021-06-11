#pragma once
#include "State.h"
class GameState;

enum class SelectedButton {play, exit};

class MenuState :
    public State
{
private:
    sf::Sprite background;
    sf::Texture backgroundTexture;

    sf::Text playText;
    sf::Text exitText;
    SelectedButton selectedButton;
    sf::Color selectedColor;
    sf::Color defaultColor;

    sf::Music music;
    sf::Font font;


    void StartGame();


public:

    MenuState(sf::RenderWindow& window, std::stack<State*>& states, std::map<std::string, std::string>& config);
    ~MenuState();

    virtual void UpdateInput(const float dt) override;
    void Update(const float dt) override;
    void Render(sf::RenderTarget& target) const override;

};

