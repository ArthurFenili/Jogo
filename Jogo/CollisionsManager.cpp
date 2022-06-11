#include "CollisionsManager.h"
#include "Phase.h"
#include "PlayingState.h"

CollisionsManager::CollisionsManager(EntityList* entityList, Entity** platformList)
{
	this->entityList = entityList;
	this->platformlist = platformList;
}

CollisionsManager::~CollisionsManager()
{
	
}

void CollisionsManager::updateCollision()
{
	sf::Vector2f playerDirection;
	sf::Vector2f enemyDirection;
	sf::Vector2f* genericDirection;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 30; j++) {
			for (int k = 0; k < this->entityList->getSize(); k++) {

				if (this->entityList->operator[](k)->getId() != FIRE && this->entityList->operator[](k)->getId() != TELEPORT && this->entityList->operator[](k)->getId() != SLOW) {

					if (entityList->operator[](k)->getId() == PLAYER)
						genericDirection = &playerDirection;
					else
						genericDirection = &enemyDirection;

					if (this->platformlist[i][j].getId() == BLOCK || this->platformlist[i][j].getId() == SLOW) {

						if (this->player1 && this->platformlist[i][j].getId() != SLOW)
							this->player1->setIsSlow(false);

						if (PlayingState::twoPlayers && this->player2)
							if (this->platformlist[i][j].getId() != SLOW)
								this->player2->setIsSlow(false);

						// Colisão dos inimigos e dos players com as plataformas (chão e parede)
						if (this->platformlist[i][j].getCollider()->isColliding(this->entityList->operator[](k)->getCollider(), genericDirection)) {
							static_cast<Character*>(this->entityList->operator[](k))->updateCollision(*genericDirection);

							if (this->entityList->operator[](k)->getId() == PLAYER) {
								// Colisão com o chão
								if (genericDirection->y < 0.f)
									static_cast<Player*>(this->entityList->operator[](k))->setCanJump(true);
							}
						}
					}	

					else if (this->player1 && this->platformlist[i][j].getId() == CASTLE && this->platformlist[i][j].getShape()->getGlobalBounds().intersects(this->player1->getShape()->getGlobalBounds())) {
						this->player1->setInCastle(true);
						break;
					}
						
				}
			}
		}
		if (this->player1 && this->player1->getInCastle())
			break;
	}

	/* COLISÃO DO PLAYER COM OS OBSTÁCULOS E INIMIGOS */

	for (int k = 0; k < this->entityList->getSize(); k++) {

		if (this->player1 && this->player1->getInCastle())
			break;

		if (this->entityList->operator[](k)->getId() != PLAYER) {

			if (this->player1) {

				// colisão de entidades com o player
				if (this->entityList->operator[](k)->getId() == TELEPORT && this->entityList->operator[](k)->getCollider()->isColliding(this->player1->getCollider(), &playerDirection)) {
					this->player1->getShape()->setPosition(sf::Vector2f(4.f * 64.f, 15.f * 64.f));

					if (PlayingState::twoPlayers)
						this->player2->getShape()->setPosition(sf::Vector2f(5.f * 64.f, 15.f * 64.f));
				}

				if (PlayingState::twoPlayers) {
					if (this->entityList->operator[](k)->getId() == TELEPORT && this->entityList->operator[](k)->getCollider()->isColliding(this->player2->getCollider(), &playerDirection)) {
						this->player1->getShape()->setPosition(sf::Vector2f(4.f * 64.f, 15.f * 64.f));
						this->player2->getShape()->setPosition(sf::Vector2f(5.f * 64.f, 15.f * 64.f));
					}
				}

				if (this->player1->getShape()->getGlobalBounds().intersects(entityList->operator[](k)->getShape()->getGlobalBounds())) {
					if (entityList->operator[](k)->getId() == SLOW) {
						this->player1->setIsSlow(true);
						this->player1->setSpeed(250.f * static_cast<Slow*>(entityList->operator[](k))->getSlowCoefficient());
					}
					else {
						this->player1->setIsSlow(false);
						if (entityList->operator[](k)->getId() == FIRE)
							this->player1->loseHp(static_cast<Fire*>(this->entityList->operator[](k))->getBurningDamage());
						else if (entityList->operator[](k)->getId() == SKELETON)
							this->player1->loseHp(static_cast<Skeleton*>(this->entityList->operator[](k))->getDamage());
						else if (entityList->operator[](k)->getId() == DARKKNIGHT)
							this->player1->loseHp(static_cast<DarkKnight*>(this->entityList->operator[](k))->getDamage());

					}
				}

				if (PlayingState::twoPlayers && this->player2) {
					if (this->player2->getShape()->getGlobalBounds().intersects(entityList->operator[](k)->getShape()->getGlobalBounds())) {
						if (entityList->operator[](k)->getId() == SLOW) {
							this->player2->setIsSlow(true);
							this->player2->setSpeed(250.f * static_cast<Slow*>(entityList->operator[](k))->getSlowCoefficient());
						}
						else {
							this->player2->setIsSlow(false);
							if (entityList->operator[](k)->getId() == FIRE)
								this->player2->loseHp(static_cast<Fire*>(this->entityList->operator[](k))->getBurningDamage());
							else if (entityList->operator[](k)->getId() == SKELETON)
								this->player2->loseHp(static_cast<Skeleton*>(this->entityList->operator[](k))->getDamage());
							else if (entityList->operator[](k)->getId() == DARKKNIGHT)
								this->player2->loseHp(static_cast<DarkKnight*>(this->entityList->operator[](k))->getDamage());
						}
					}
				}

				if (entityList->operator[](k)->getId() == SKELETON || entityList->operator[](k)->getId() == ARCHER) {
					if (this->player1->getSwordHitbox() && this->player1->getShape()->getGlobalBounds().intersects(entityList->operator[](k)->getShape()->getGlobalBounds())) {
						static_cast<Character*>(entityList->operator[](k))->loseHp(1);
					}
					if (PlayingState::twoPlayers && this->player2) {
						if (this->player2->getSwordHitbox() && this->player2->getShape()->getGlobalBounds().intersects(entityList->operator[](k)->getShape()->getGlobalBounds())) {
							static_cast<Character*>(entityList->operator[](k))->loseHp(1);
						}
					}
				}
				if (entityList->operator[](k)->getId() == DARKKNIGHT) {
					if (this->player1->getSwordHitbox() && this->player1->getShape()->getGlobalBounds().intersects(entityList->operator[](k)->getShape()->getGlobalBounds())) {
						static_cast<Character*>(entityList->operator[](k))->loseHp(1);
						DarkKnight::gotHit++;
					}
					if (static_cast<DarkKnight*>(entityList->operator[](k))->getSwordHitbox() && entityList->operator[](k)->getShape()->getGlobalBounds().intersects(this->player1->getShape()->getGlobalBounds())) {
						this->player1->loseHp(200);
					}
				}
				
				

				if (this->entityList->operator[](k)->getId() == ARCHER) {
					Archer* currentArcher = static_cast<Archer*>(this->entityList->operator[](k));
					for (int l = 0; l < currentArcher->getArrowsVector()->size(); l++) {
						if (currentArcher->getArrowsVector()->operator[](l)->getShape()->getGlobalBounds().intersects(this->player1->getShape()->getGlobalBounds()))
							this->player1->loseHp(1);
						if (PlayingState::twoPlayers && this->player2)
							if (currentArcher->getArrowsVector()->operator[](l)->getShape()->getGlobalBounds().intersects(player2->getShape()->getGlobalBounds()))
								player2->loseHp(1);
					}
				}
			}
			
		}
	}
}