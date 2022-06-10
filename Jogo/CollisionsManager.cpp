#include "CollisionsManager.h"
#include "Phase.h"
#include "PlayingState.h"

CollisionsManager::CollisionsManager(Phase* phase)
{
	this->phase = phase;
}

CollisionsManager::~CollisionsManager()
{
	this->phase = nullptr;
}

void CollisionsManager::updateCollision()
{
	sf::Vector2f playerDirections;
	sf::Vector2f enemyDirections;

	Collider* collider1;
	Collider* collider2;

	Entity** platformList = this->phase->getPlatformList(); // PLATAFORMAS (BLOCOS E BACKGROUND E DOOR)
	EntityList* entityList = this->phase->getEntityList(); // PLAYER, ENEMY E OBSTACULOS (FIRE, SLOW, TELEPORT)

	Player* player1 = this->phase->getPlayer1();

	Player* player2 = this->phase->getPlayer2();

	int j;
	for (int i = 0; i < 20; i++) {
		for (j = 0; j < 30; j++) {
			if (platformList[i][j].getId() == BLOCK || platformList[i][j].getId() == SLOW) {

				collider1 = platformList[i][j].getCollider();

				if (collider1->isColliding(player1->getCollider(), &playerDirections)) {
					player1->updateCollision(playerDirections);

					if (playerDirections.y < 0.f)
						player1->setCanJump(true);

					if (platformList[i][j].getId() == SLOW)
						player1->setIsSlow(true);
					else
						player1->setIsSlow(false);
				}
				if (PlayingState::twoPlayers) {
					if (collider1->isColliding(player2->getCollider(), &playerDirections)) {
						player2->updateCollision(playerDirections);

						if (playerDirections.y < 0.f)
							player2->setCanJump(true);

						if (platformList[i][j].getId() == SLOW)
							player2->setIsSlow(true);
						else
							player2->setIsSlow(false);
					}
				}

				for (int k = 0; k < entityList->getSize() - 2; k++) {

					collider2 = entityList->operator[](k)->getCollider();

					if (entityList->operator[](k)->getId() == SKELETON || entityList->operator[](k)->getId() == ARCHER) {

						if (collider1->isColliding(collider2, &enemyDirections)) {
							static_cast<Character*>(entityList->operator[](k))->updateCollision(enemyDirections);
						}


						if (player1 && player1->getSwordHitbox())
							if (player1->getSwordHitbox()->getShape()->getGlobalBounds().intersects(entityList->operator[](k)->getShape()->getGlobalBounds()))
								static_cast<Character*>(entityList->operator[](k))->loseHp();

						if (PlayingState::twoPlayers) {
							if (player2 && player2->getSwordHitbox())
								if (player2->getSwordHitbox()->getShape()->getGlobalBounds().intersects(entityList->operator[](k)->getShape()->getGlobalBounds()))
									static_cast<Character*>(entityList->operator[](k))->loseHp();
						}
					}
					else {

						if (player1) {
							if (entityList->operator[](k)->getId() != FIRE && entityList->operator[](k)->getId() != SLOW && collider2->isColliding(player1->getCollider(), &playerDirections)) {
								if (entityList->operator[](k)->getId() == TELEPORT) {
									player1->setIsSlow(false);
									player1->getShape()->setPosition(sf::Vector2f(4.f * 64.f, 15.f * 64.f));
									if (PlayingState::twoPlayers)
										player2->getShape()->setPosition(sf::Vector2f(5.f * 64.f, 15.f * 64.f));
								}
							}
							else if (entityList->operator[](k)->getId() == FIRE && player1->getShape()->getGlobalBounds().intersects(entityList->operator[](k)->getShape()->getGlobalBounds())) {
								player1->loseHp();
							}
						}
						
						if (player2) {
							if (entityList->operator[](k)->getId() != FIRE && entityList->operator[](k)->getId() != SLOW && collider2->isColliding(player2->getCollider(), &playerDirections)) {
								if (entityList->operator[](k)->getId() == TELEPORT) {
									player2->setIsSlow(false);
									player1->getShape()->setPosition(sf::Vector2f(4.f * 64.f, 15.f * 64.f));
									player2->getShape()->setPosition(sf::Vector2f(5.f * 64.f, 15.f * 64.f));
								}
							}
							else if (entityList->operator[](k)->getId() == FIRE && player2->getShape()->getGlobalBounds().intersects(entityList->operator[](k)->getShape()->getGlobalBounds())) {
								player2->loseHp();
							}
						}
						

					}
				}
			}
			else if (platformList[i][j].getId() == CASTLE) {
				if (player1->getShape()->getGlobalBounds().intersects(platformList[i][j].getShape()->getGlobalBounds())) {
					this->phase->setPhaseEnd(true);
					break;
				}
			}
		}
		if (j != 30)
			break;
	}
}