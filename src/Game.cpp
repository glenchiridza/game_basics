#include "Game.h";

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initEnemy();
}

Game::~Game()
{
    delete this->window;
}

//private functions

void Game::initVariables()
{
    this->window = nullptr;
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 8;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    // this->videoMode.getDesktopMode
    this->window = new sf::RenderWindow(sf::VideoMode(this->videoMode),"Glenc Arts",sf::Style::Titlebar | sf::Style::Close);
    
    this->window->setFramerateLimit(60);
}

void Game::initEnemy()
{
    this->enemy.setPosition(10.f,10.f);
    this->enemy.setSize(sf::Vector2f(100.f,100.f));
    this->enemy.setScale(sf::Vector2f(0.5f,0.5f));
    this->enemy.setFillColor(sf::Color::Red);
    // this->enemy.setOutlineColor(sf::Color::Green);
    // this->enemy.setOutlineThickness(1.f);


}

//Accessors

const bool Game::running() const 
{
    return this->window->isOpen();
}

//public functions

void Game::spawnEnemy()
{
    //spawns enemies and set their color and positions
    
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    this->enemy.setFillColor(sf::Color::Green);
    //spawn the enemy
    this->enemies.push_back(this->enemy);
    

}

void Game::pollEvents()
{

    while (this->window->pollEvent(this->event))
        {
            switch (this->event.type)
            {
            case sf::Event::Closed:
                this->window->close();
                break;
                case sf::Event::KeyPressed:
                if(this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
            }
        }
}

void Game::updateMousePos()
{
    /*
    updates mouse positions
        --mouse position relative to window vector2i
    */

   this->mousePosWindow =  sf::Mouse::getPosition(*this->window);
   this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update()
{
     this->pollEvents();

     this->updateMousePos();

    this->updateEnemies();

     //update mouse pos
    //  //relative to screen
    //  std::cout<<"mouse pos "<<sf::Mouse::getPosition().x <<" "<< sf::Mouse::getPosition().y <<"\n";
    //  //relative to window
    //  std::cout<<"mouse pos "<<sf::Mouse::getPosition(*this->window).x <<" "<< sf::Mouse::getPosition(*this->window).y <<"\n";
}

void Game::updateEnemies()
{
   
    //update timer for enemy spwaning
    if(this->enemies.size() < this->maxEnemies)
    {
     if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
     {
         //spawn enemy and reset the timer 
        this->spawnEnemy();
        this->enemySpawnTimer = 0.f;
     }else{
         this->enemySpawnTimer += 1.f;
     }
    }

    //remove enemy at edge of the screen
    //move the enemies
    // for(auto &e : this->enemies)
    // {
    //     e.move(0.f, 1.f); //moving downwards from 0.f, 1.f is the speed
    // }

//move and update enemies
    for(int i =0; i < this->enemies.size(); i++)
    {
        bool deleted = false;
        
        this->enemies[i].move(0.f,1.f);

        //check if clicked upon
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
            {
                deleted = true;

                //game points
                this->points =+ 10.f;
            }
            
        }

//if enemie is past bottom screen
        if(this->enemies[i].getPosition().y > this->window->getSize().y){
            deleted = true;
        }

        if (deleted)
        {
            this->enemies.erase(this->enemies.begin() + i);
        }
        

    }


}

void Game::renderEnemies()
{
    //render all the enemies
    for(auto &e : this->enemies)
    {
        this->window->draw(e);
    }

    

}

void Game::render()
{
    /* 
        renders game objects

        --clear old  frame
        --render objects
        --display frame in window
    */
    this->window->clear();

    //draw game objects
    // this->window->draw(this->enemy);
    this->renderEnemies(); 

    this->window->display();
}



