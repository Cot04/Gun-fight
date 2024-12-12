#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#define WIDTH 800
#define HEIGHT 600
#define PLAYER_SIZE 20
#define PROJECTILE_SIZE 6
#define PROJECTILE_SPEED 0.3
#define MOVE_SPEED 0.1f

class Projectile {
public:
    sf::RectangleShape shape;
    sf::Vector2f direction;

    Projectile(sf::Vector2f startPos, sf::Vector2f dir) {
        shape.setSize({PROJECTILE_SIZE, PROJECTILE_SIZE});
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(startPos);
        direction = dir;
    }

    void move() {
        shape.move(direction * (float)PROJECTILE_SPEED);
    }

    bool outOfBounds() {
        sf::Vector2f pos = shape.getPosition();
        return (pos.x < 0 || pos.x > WIDTH || pos.y < 0 || pos.y > HEIGHT);
    }
};

class Player {
public:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f direction = {0, 0};
    std::vector<Projectile> projectiles;
    int lives;
    sf::Clock clock;
    float shootCooldown = 0.2f;
    bool canShoot = true;

    Player(const std::string &texturePath, sf::Vector2f startPos, int initialLives = 10) : lives(initialLives) {
        if (!texture.loadFromFile(texturePath)) {
            std::cerr << "Error loading texture: " << texturePath << std::endl;
            exit(-1);
        }
        sprite.setTexture(texture);
        sprite.setPosition(startPos);
    }

    void move() {
        sf::Vector2f newPosition = sprite.getPosition() + direction * MOVE_SPEED;
        if (newPosition.x < 0) newPosition.x = 0;
        if (newPosition.y < 0) newPosition.y = 0;
        if (newPosition.x + sprite.getGlobalBounds().width > WIDTH)
            newPosition.x = WIDTH - sprite.getGlobalBounds().width;
        if (newPosition.y + sprite.getGlobalBounds().height > HEIGHT)
            newPosition.y = HEIGHT - sprite.getGlobalBounds().height;

        sprite.setPosition(newPosition);
    }

    void shoot(sf::Keyboard::Key fireKey) {
        if (sf::Keyboard::isKeyPressed(fireKey) && canShoot) {
            clock.restart();
            canShoot = false;
            if (direction != sf::Vector2f(0, 0)) {
                sf::Vector2f startPos = sprite.getPosition() +
                                        sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
                projectiles.push_back(Projectile(startPos, direction));
            }
        }

        if (clock.getElapsedTime().asSeconds() >= shootCooldown) {
            canShoot = true;
        }
    }

    void updateProjectiles() {
        for (auto &p : projectiles) {
            p.move();
        }
        projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile &p) {
                          return p.outOfBounds();
                      }),
                      projectiles.end());
    }

    void draw(sf::RenderWindow &window) {
        window.draw(sprite);
        for (auto &p : projectiles) {
            window.draw(p.shape);
        }
    }
};

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text p1LivesText, p2LivesText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Player p1;
    Player p2;
    int redScore = 0;
    int blueScore = 0;
    bool gameOver = false;

public:
    Game()
        : window(sf::VideoMode(WIDTH, HEIGHT), "Gunfight"),
          p1("./assets/images/gunfight.png", {100, HEIGHT / 2}, 10),
          p2("./assets/images/gunfight2.png", {WIDTH - 100, HEIGHT / 2}, 10) {

        if (!font.loadFromFile("./assets/fonts/Ring.ttf")) {
            std::cerr << "Unable to load font!" << std::endl;
            exit(-1);
        }

        p1.sprite.setScale(0.2f, 0.2f);
        p2.sprite.setScale(0.2f, 0.2f);

        setupText(p1LivesText, {0, 0});
        setupText(p2LivesText, {0, 60});

        if (!backgroundTexture.loadFromFile("assets/images/Background.png")) {
            std::cerr << "Unable to load background texture!" << std::endl;
            exit(-1);
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(float(WIDTH) / backgroundTexture.getSize().x, float(HEIGHT) / backgroundTexture.getSize().y);
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            if (!gameOver) {
                update();
            }
            render();
        }
    }

private:
    void setupText(sf::Text &text, sf::Vector2f position) {
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(position);
    }

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                reset(); // Reiniciar el juego al presionar 'R'
            }
        }
    }

    void update() {
        handlePlayerInput();

        p1.move();
        p2.move();

        p1.updateProjectiles();
        p2.updateProjectiles();

        handleCollisions(p1, p2, redScore);
        handleCollisions(p2, p1, blueScore);

        if (p1.lives <= 0 || p2.lives <= 0) {
            gameOver = true;
        }

        p1LivesText.setString("Player 1 Lives: " + std::to_string(p1.lives));
        p2LivesText.setString("Player 2 Lives: " + std::to_string(p2.lives));
    }

    void render() {
        window.clear();

        //window.draw(backgroundSprite);
        p1.draw(window);
        p2.draw(window);

        window.draw(p1LivesText);
        window.draw(p2LivesText);

        if (gameOver) {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(30);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setString((p1.lives == 0) ? "Player 2 Wins!" : "Player 1 Wins!");
            gameOverText.setPosition(WIDTH / 2 - gameOverText.getLocalBounds().width / 2, HEIGHT / 2);
            window.draw(gameOverText);
        }

        window.display();
    }

    void reset() {
        p1 = Player("./assets/images/gunfight.png", {100, HEIGHT / 2}, 10);
        p2 = Player("./assets/images/gunfight2.png", {WIDTH - 100, HEIGHT / 2}, 10);

        p1.sprite.setScale(0.2f, 0.2f);
        p2.sprite.setScale(0.2f, 0.2f);

        redScore = 0;
        blueScore = 0;
        gameOver = false;
    }

    void handlePlayerInput() {
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

        p1.shoot(sf::Keyboard::Space);
        p2.shoot(sf::Keyboard::Enter);
    }

    void handleCollisions(Player &shooter, Player &target, int &score) {
        auto &projectiles = shooter.projectiles;

        projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [&](Projectile &p) {
            if (target.sprite.getGlobalBounds().intersects(p.shape.getGlobalBounds())) {
                if (target.lives > 0) {
                    target.lives--;
                    score++;
                }
                return true;
            }
            return false;
        }), projectiles.end());
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}