#include "Projectile.h"
#include "EnemyProjectile.h"

Projectile::Projectile()
{
	this->user = nullptr;
}

Projectile::~Projectile()
{
}

void Projectile::createProjectile()
{
	projectile = new sf::RectangleShape();
	projectile->setFillColor(sf::Color::Magenta);
	projectile->setSize(sf::Vector2f(10.f, 10.f));

	projectile->setPosition(this->user->getPosition());
	projectiles.push_back(projectile);
}

void Projectile::moveProjectile(int index, float direction)
{
	projectiles[index]->move(direction * 300.f * user->getDT(), 0.f);
}

void Projectile::verifyErase(int index)
{
	if ((projectiles[index]->getPosition().x < 0) || (projectiles[index]->getPosition().x > 1280)) {
		projectiles.erase(projectiles.begin() + index);
	}
}
