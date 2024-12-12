#include "Collision.hpp"

bool checkCollision(Player &player, Projectile &projectile)
{
    return player.sprite.getGlobalBounds().intersects(projectile.shape.getGlobalBounds());
}

void handleCollisions(Player &shooter, Player &target, int &score)
{
    auto &projectiles = shooter.projectiles;
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [&](Projectile &p)
                                     {
        if (checkCollision(target, p)) {
            if (target.lives > 0) {
                target.lives--;
                score++;
            }
            return true;
        }
        return false; }),
                      projectiles.end());
}
