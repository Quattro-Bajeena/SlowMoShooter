#include "stdafx.h"
#include "Game.h"



void Game::UpdateSFMLEvents()
{
    while (window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) {
            window->close();
        }
        if (sfEvent.type == sf::Event::MouseWheelMoved) {
            if (states.empty() == false)
                states.top()->UpdateScrollWheel(sfEvent.mouseWheel.delta);
        }
    }
}

void Game::Update()
{
    dt = dtClock.restart().asSeconds();
    UpdateSFMLEvents();
    if (states.empty() == false) {

        if (window->hasFocus()) {
            //Update State at the top
            states.top()->Update(dt);

            while (states.empty() == false && states.top()->GetQuit()) {//must be in that order so it wont check getQuit on empty stakc
                //deleting state at the top
                delete states.top();
                states.pop();
            }
        }
    }
    //Application end
    else {
        window->close();
    }
}

void Game::LoadConfig()
{
    std::ifstream file("config.txt");

    std::string key, value;
    if (file.is_open() == true) {
        while (file >> key >> value) {
            key.pop_back();

            //std::cout << key << " " << value << "\n";
            config[key] = value;
        }
    }
    else {
        std::cout << "Couldn't open config.txt\n";
        exit(1);
    }

}

void Game::Render() const
{
    window->clear(sf::Color(40, 40, 40));
    if (states.empty() == false) {
        states.top()->Render(*window);
    }
    window->display();
}

// Initalization
Game::Game()
{
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "I hate antichrist", sf::Style::Titlebar | sf::Style::Close);
	window->setVerticalSyncEnabled(true);
	
    icon.loadFromFile("Assets/trollege.jpg");
    window->setIcon(256, 256, icon.getPixelsPtr());

	srand(time(NULL));
	dt = 0;

    LoadConfig();
    states.push(new MenuState(*window, states, config));
}

Game::~Game()
{
	delete window;
	while (states.empty() == false) {
		delete states.top();
		states.pop();
	}
}

void Game::Run()
{
    while (window->isOpen()) {
        Update();
        Render();
    }
}
