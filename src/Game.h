#pragma once
/*
Game engine class
*/

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

class Game
{
public:
    Game();
    virtual ~Game();

    //accessors
    const bool running() const;

    //functions
    void spawnEnemy();

    void pollEvents();
    void updateMousePos();
    void updateEnemies();
    void update();

    void renderEnemies();
    void render();

private:
    //variables

    //window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;

    //Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //game logic
    int points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;


    //game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;


    //functions
    void initVariables();
    void initWindow();
    void initEnemy();
};