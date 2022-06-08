#include "Projectile.h"
#include "Archer.h"

Projectile::Projectile(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, Archer* archer) :
	Entity(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName)
{
	this->archer = archer;
}

Projectile::Projectile() :
	Entity()
{
	this->archer = nullptr;
}

Projectile::~Projectile()
{
	this->archer = nullptr;
}

void Projectile::createProjectile()
{
	this->body.setFillColor(sf::Color::Magenta);
	this->body.setPosition(this->archer->getPosition());
}

void Projectile::moveProjectile(float direction)
{
	this->body.move(direction * 300.f * (*this->dt), 0.f);
}

bool Projectile::verifyErase()
{
	if ((this->body.getPosition().x < 0) || (this->body.getPosition().x > 1280))
		return true;
	return false;
}
