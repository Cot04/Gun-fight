/// Code written by Bordeanu Calin

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>

#define WIDTH 800
#define HEIGHT 600
#define PLAYER_SIZE 20
#define PROJECTILE_SIZE 6
#define PROJECTILE_SPEED 0.3
#define MOVE_SPEED 0.1f

// const int WIDTH = BLOCKS * blockSize;
// const int HEIGHT = BLOCKS * blockSize;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gunfight");

bool gameOver = false;
// bool keyPressedLastFrame[250] = {false};

int redScore = 0;
int blueScore = 0;

class Projectile
{
public:
    sf::RectangleShape shape;
    sf::Vector2f direction;

    Projectile(sf::Vector2f startPos, sf::Vector2f dir)
    {
        shape.setSize({PROJECTILE_SIZE, PROJECTILE_SIZE});
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(startPos);
        direction = dir;
    }

    void move()
    {
        shape.move(direction * (float)PROJECTILE_SPEED);
    }

    bool outofBounds()
    {
        sf::Vector2f pos = shape.getPosition();
        return (pos.x < 0 || pos.x > WIDTH || pos.y < 0 || pos.y > HEIGHT);
    }
};

class Player
{
public:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f direction = {0, 0};
    std::vector<Projectile> projectiles;
    int lives; // Vidas
    sf::Clock clock;
    float shootTime = 0.2f;
    bool shootRunning = false;

    Player(const std::string &texturePath, sf::Vector2f startPos, int initialLives = 10) : lives(initialLives)
    {
        if (!texture.loadFromFile(texturePath))
        {
            std::cerr << "Error al cargar la textura" << texturePath << std::endl;
            exit(-1);
        }
        sprite.setTexture(texture);
        sprite.setPosition(startPos);
    }

    void Move()
    {
        sf::Vector2f newPosition = sprite.getPosition() + direction * MOVE_SPEED;

        // Restringir limites de pantalla
        if (newPosition.x < 0)
            newPosition.x = 0;
        if (newPosition.y < 0)
            newPosition.y = 0;
        if (newPosition.x + sprite.getGlobalBounds().width > WIDTH)
            newPosition.x = WIDTH - sprite.getGlobalBounds().width;
        if (newPosition.y + sprite.getGlobalBounds().height > HEIGHT)
            newPosition.y = HEIGHT - sprite.getGlobalBounds().height;

        sprite.setPosition(newPosition);
    }

    void shoot(sf::Keyboard::Key fireKey)
    {
        if (sf::Keyboard::isKeyPressed(fireKey) && !shootRunning)
        {
            clock.restart();
            shootRunning = true;

            if (direction != sf::Vector2f(0, 0))
            {
                sf::Vector2f startpos = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
                projectiles.push_back(Projectile(startpos, direction));
            }
        }

        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= shootTime)
        {
            shootRunning = false;
        }
    }
    void draw()
    {
        window.draw(sprite);
        for (auto &p : projectiles)
        {
            window.draw(p.shape);
        }
    }

    void updateProjectiles()
    {
        for (auto &p : projectiles)
        {
            p.move();
        }
        // Eliminar proyectiles fuera de la pantalla
        projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile &p)
                                         { return p.outofBounds(); }),
                          projectiles.end());
    }
};

bool checkCollision(Player &player, Projectile &projectile)
{
    return player.sprite.getGlobalBounds().intersects(projectile.shape.getGlobalBounds());
}

void handleCollisions(Player &shooter, Player &target, int &score)
{
    auto &projectiles = shooter.projectiles;

    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [&](Projectile &p)
                                     {
        if (checkCollision(target, p)){
            if(target.lives > 0){
                target.lives --; //restar una vida
                score ++; //incrementar puntuacion
                std::cout <<" Press 'R' to go to the next round ";
            }
            return true; //Eliminar el proyectil
         }
        return false; }),
                      projectiles.end());
}

int main()
{
    gameOver = false;
    // system("cls");

    // mostrar texto
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Ring.ttf"))
    {
        std::cout << "No se puede cargar la fuente\n";
        return -1;
    }

    // crear textos
    sf::Text p1LivesText, p2LivesText;
    p1LivesText.setFont(font);
    p2LivesText.setFont(font);
    p2LivesText.setPosition(0, 60);
    p1LivesText.setCharacterSize(24);
    p2LivesText.setCharacterSize(24);
    p1LivesText.setFillColor(sf::Color::White);
    p2LivesText.setFillColor(sf::Color::White);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/images/Background.png"))
    {
        std::cout << "No se pudo cargar la textura de fondo. \n";
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // Escalar el fondo al tamaño de la ventana
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    backgroundSprite.setScale(float(windowSize.x) / textureSize.x, float(windowSize.y) / textureSize.y);

    // crear jugadores
    Player p1("./assets/images/gunfight.png", {100, HEIGHT / 2}, 10);
    Player p2("assets/images/gunfight2.png", {WIDTH - 100, HEIGHT / 2}, 10);

    p1.sprite.setScale(0.2f, 0.2f);
    p2.sprite.setScale(0.2f, 0.2f);

    while (window.isOpen())
    {
        window.clear();
        window.draw(backgroundSprite);
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                main();
        }

        // Controles de los jugadores
        p1.direction = {0, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            p1.direction.y = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            p1.direction.y = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            p1.direction.x = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            p1.direction.x = 1;

        p2.direction = {0, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            p2.direction.y = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            p2.direction.y = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            p2.direction.x = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            p2.direction.x = 1;

        // Disparos
        p1.shoot(sf::Keyboard::Space);
        p2.shoot(sf::Keyboard::Enter);

        // Actualizar posiciones y proyectiles
        p1.Move();
        p2.Move();
        p1.updateProjectiles();
        p2.updateProjectiles();
        // colisiones
        handleCollisions(p1, p2, redScore); // Los disparos de p1 afectan a p2
        handleCollisions(p2, p1, blueScore);

        // comprobar vidas
        if (p1.lives == 0 || p2.lives == 0)
        {
            gameOver = true;
            std::cout << " Game Over!";
            if (p1.lives <= 0)
            {
                std::cout << "Player 2 Wins!\n";
            }
            else
            {
                std::cout << "Player 1 Wins!\n";
            }
        }

        // Actualizar textos de vidas
        p1LivesText.setString("Player 1 Lives " + std::to_string(p1.lives));
        p2LivesText.setString("Player 2 Lives " + std::to_string(p2.lives));

        // Dibujar
        window.clear(sf::Color::Black);
        p1.draw();
        p2.draw();
        window.draw(p1LivesText);
        window.draw(p2LivesText);

        if (gameOver)
        {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(30);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setString((p1.lives == 0) ? "Player 2 wins" : "Player 1 Wins");
            gameOverText.setPosition(WIDTH / 2 - gameOverText.getLocalBounds().width / 2, HEIGHT / 2);
            window.draw(gameOverText);
        }
        window.display();
        // continue;

        // for (int i = 0; i < 256; i++)
        // {
        //     keyPressedLastFrame[i] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
        // }
    }
}
