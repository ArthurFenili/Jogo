#include "PlayingState.h"

const float PLATFORM_WIDTH = 64.f;
const float PLATFORM_HEIGHT = 64.f;

const float PLAYER_WIDTH = 32.f * 1.6f;
const float PLAYER_HEIGHT = 35.f * 2.2f;
const float PLAYER_SPRITE_SCALE = 3.f;
const float PLAYER_SPEED = 250.f;
const long int PLAYER_HP = 400000;

const float SKELETON_WIDTH = 32.f * 2.f;
const float SKELETON_HEIGHT = 35.f * 2.6f;
const float SKELETON_SPRITE_SCALE = 3.f;
const float SKELETON_SPEED = 30.f;
const long int SKELETON_HP = 100000;

const float ARCHER_WIDTH = 31.f * 2.f;
const float ARCHER_HEIGHT = 40.f * 2.6f;
const float ARCHER_SPRITE_SCALE = 3.f;
const float ARCHER_SPEED = 30.f;

const float TELEPORT_SPRITE_SCALE = 2.3f;

sf::Vector2f FIRE_SIZE = sf::Vector2f(64.f * 0.3f, 64.f * 0.8f);
sf::Vector2f TELEPORT_SIZE = sf::Vector2f(64.f * 0.4f, 64.f);

PlayingState::PlayingState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt) :
	State(graphicsManager, states, dt)
{
	std::cout << "PlayingState" << std::endl;

	this->dt = dt;
	this->setPhase(new ForestPhase(this->graphicsManager, this->dt, FOREST_PHASE));
	this->exit = false;
	this->score = 0;

	this->createPlayers();
	this->createMap();
	this->createObstacles(FOREST_PHASE);
	this->createEnemies(FOREST_PHASE);

	this->currentPhase->addEntity(this->player1);
}

PlayingState::~PlayingState()
{
	if (this->player1) {
		delete this->player1;
		this->player1 = nullptr;
	}
	this->currentPhase->clearEntityList();
	this->currentPhase->clearPlatformList();
	delete this->currentPhase;
}

void PlayingState::createMap()
{
	this->currentPhase->loadMap("images/forest_map.txt");
}

void PlayingState::createObstacles(int phase)
{
	if (phase == FOREST_PHASE) {
		this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(18.f * 64.f, 21.f * 64.f), FIRE_SIZE, "images/fire_p1.png", "FIRE_P1");
		this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(28.f * 64.f, 20.f * 64.f), FIRE_SIZE, "images/fire_p1.png", "FIRE_P1");
		this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(29.f * 64.f, 20.f * 64.f), FIRE_SIZE, "images/fire_p1.png", "FIRE_P1");
		this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(24.f * 64.f, 10.f * 64.f), FIRE_SIZE, "images/fire_p1.png", "FIRE_P1");
		this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(41.f * 64.f, 15.f * 64.f), FIRE_SIZE, "images/fire_p1.png", "FIRE_P1");
		this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(38.f * 64.f, 8.f * 64.f), FIRE_SIZE, "images/fire_p1.png", "FIRE_P1");

		this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(14.f * 64.f, 22.f * 64.f), TELEPORT_SIZE, "images/teleport_p1.png", "TELEPORT_P1");
		this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(24.f * 64.f, 19.f * 64.f), TELEPORT_SIZE, "images/teleport_p1.png", "TELEPORT_P1");
		this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(36.f * 64.f, 12.f * 64.f), TELEPORT_SIZE, "images/teleport_p1.png", "TELEPORT_P1");
		this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(33.f * 64.f, 8.f * 64.f), TELEPORT_SIZE, "images/teleport_p1.png", "TELEPORT_P1");
		this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(18.f * 64.f, 11.f * 64.f), TELEPORT_SIZE, "images/teleport_p1.png", "TELEPORT_P1");
		this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(10.f * 64.f, 13.f * 64.f), TELEPORT_SIZE, "images/teleport_p1.png", "TELEPORT_P1");
	}

	else if (phase == CASTLE_PHASE) {
		this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(15.f * 64.f, 23.f * 64.f), FIRE_SIZE, "images/fire.png", "FIRE");
		this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(25.f * 64.f, 19.f * 64.f), FIRE_SIZE, "images/fire.png", "FIRE");
		this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(9.f * 64.f, 15.f * 64.f), FIRE_SIZE, "images/fire.png", "FIRE");
		this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(19.f * 64.f, 10.f * 64.f), FIRE_SIZE, "images/fire.png", "FIRE");
		this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(25.f * 64.f, 10.f * 64.f), FIRE_SIZE, "images/fire.png", "FIRE");
		this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(34.f * 64.f, 13.f * 64.f), FIRE_SIZE, "images/fire.png", "FIRE");

		this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(12.f * 64.f, 23.f * 64.f), TELEPORT_SIZE, "images/teleport.png", "TELEPORT");
		this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(30.f * 64.f, 19.f * 64.f), TELEPORT_SIZE, "images/teleport.png", "TELEPORT");
		this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(39.f * 64.f, 23.f * 64.f), TELEPORT_SIZE, "images/teleport.png", "TELEPORT");
		this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(41.f * 64.f, 15.f * 64.f), TELEPORT_SIZE, "images/teleport.png", "TELEPORT");
		this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(33.f * 64.f, 8.f * 64.f), TELEPORT_SIZE, "images/teleport.png", "TELEPORT");
	}
}

void PlayingState::createEnemies(int phase)
{
	if (phase == FOREST_PHASE) {
		this->currentPhase->createEntity(SKELETON, SKELETON_SPRITE_SCALE, sf::Vector2f(950.f, 1400.f), sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), "images/skeleton.png", "SKELETON");
	}
	else if (phase == CASTLE_PHASE) {
		this->currentPhase->createEntity(ARCHER, ARCHER_SPRITE_SCALE, sf::Vector2f(950.f, 1400.f), sf::Vector2f(ARCHER_WIDTH, ARCHER_HEIGHT), "images/archer.png", "ARCHER");
	}
}

void PlayingState::createPlayers()
{
	this->player1 = new Player(this->graphicsManager, this->dt, PLAYER, PLAYER_SPRITE_SCALE, sf::Vector2f(8.f * 64.f, 22.f * 64.f), sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), "images/player.png", "PLAYER", PLAYER_SPEED, PLAYER_HP);
	this->currentPhase->setPlayer(this->player1);
}

void PlayingState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		this->graphicsManager->resetView();
		this->insertState(new PauseState(this->graphicsManager, this->states, this->dt, &this->exit));
		this->updateStateChange();
	}

	if (this->player1->isDead()) {
		this->graphicsManager->resetView();
		this->insertState(new GameOverState(this->graphicsManager, this->states, this->dt), true);
		this->updateStateChange();
	}

	if (this->exit) {
		this->graphicsManager->resetView();
		this->removeCurrentState();
		this->updateStateChange();
	}
}

// Verifica se está ocorrendo colisões entre o jogador e os outros objetos
void PlayingState::updateCollision()
{
	sf::Vector2f directionPlayerTmp;  // Vetor de direções
	sf::Vector2f directionEnemyTmp;

	Entity** platformList = this->currentPhase->getPlatformList(); // PLATAFORMAS (BLOCOS E BACKGROUND E DOOR)
	EntityList* entityList = this->currentPhase->getEntityList(); // PLAYER, ENEMY E OBSTACULOS (FIRE, SLOW, TELEPORT)
	int j;
	for (int i = 0; i < 30; i++) {
		for (j = 0; j < 50; j++) {
			if (platformList[i][j].getId() == BLOCK) {

				if (platformList[i][j].getCollider()->isColliding(this->player1->getCollider(), &directionPlayerTmp)) {
					this->player1->updateCollision(directionPlayerTmp);

					if (directionPlayerTmp.y < 0.f)
						this->player1->setCanJump(true);
				}

				for (int k = 0; k < entityList->getSize() - 1; k++) {
					if (entityList->operator[](k)->getId() == SKELETON || entityList->operator[](k)->getId() == ARCHER) {
						if (platformList[i][j].getCollider()->isColliding(entityList->operator[](k)->getCollider(), &directionEnemyTmp))
							static_cast<Character*>(entityList->operator[](k))->updateCollision(directionEnemyTmp);

						if (this->player1 && this->player1->getSwordHitbox())
							if (this->player1->getSwordHitbox()->getShape()->getGlobalBounds().intersects(entityList->operator[](k)->getShape()->getGlobalBounds()))
								static_cast<Character*>(entityList->operator[](k))->loseHp();

					}
					else if (this->player1) {
						if (entityList->operator[](k)->getId() != FIRE && entityList->operator[](k)->getCollider()->isColliding(this->player1->getCollider(), &directionPlayerTmp)) {
							if (entityList->operator[](k)->getId() == SLOW)
								this->player1->setIsSlow(true);
							else if (entityList->operator[](k)->getId() == TELEPORT) {
								this->player1->setIsSlow(false);
								this->player1->getShape()->setPosition(sf::Vector2f(8.f * 64.f, 22.f * 64.f));
							}
						}
						else if (entityList->operator[](k)->getId() == FIRE && this->player1->getShape()->getGlobalBounds().intersects(entityList->operator[](k)->getShape()->getGlobalBounds())) {
							this->player1->setIsSlow(false);
							this->player1->loseHp();
						}
					}
				}
			}
			else if (platformList[i][j].getId() == CASTLE) {
				if (this->player1->getShape()->getGlobalBounds().intersects(platformList[i][j].getShape()->getGlobalBounds())) {
					this->changeLevel();
					break;
				}

			}
		}
		if (j != 50)
			break;
	}
}

void PlayingState::update(float dt)
{
	this->updateInput();
	this->currentPhase->update();
	this->graphicsManager->updateView(this->player1->getShape());
	this->updateCollision();
}

void PlayingState::render()
{
	this->graphicsManager->clearWindow(this->currentPhase->getId());
	this->graphicsManager->setView();
	this->currentPhase->render();
}

void PlayingState::resetState()
{
}

void PlayingState::changeLevel()
{
	this->currentPhase->clearPlatformList();
	this->currentPhase->clearEntityList();

	delete this->currentPhase;

	this->setPhase(new CastlePhase(this->graphicsManager, this->dt, CASTLE_PHASE));

	this->currentPhase->loadMap("images/castle_map.txt");
	this->currentPhase->setPlayer(this->player1);

	this->createObstacles(CASTLE_PHASE);
	this->createEnemies(CASTLE_PHASE);

	this->currentPhase->addEntity(this->player1);



	this->player1->getShape()->setPosition(sf::Vector2f(700.f, 800.f));
}
