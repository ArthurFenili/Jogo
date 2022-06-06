#include "PlayingState.h"

const float WINDOW_WIDTH = 1280.f;
const float WINDOW_HEIGHT = 720.f;

const float PLATFORM_WIDTH = 64.f;
const float PLATFORM_HEIGHT = 64.f;

const float PLAYER_WIDTH = 32.f * 2.f;
const float PLAYER_HEIGHT = 35.f * 2.6f;
const float PLAYER_SPRITE_SCALE = 3.f;
const float PLAYER_SPEED = 200.f;

const float SKELETON_WIDTH = 32.f * 2.f;
const float SKELETON_HEIGHT = 35.f * 2.6f;
const float SKELETON_SPRITE_SCALE = 3.f;
const float SKELETON_SPEED = 30.f;

const float ARCHER_WIDTH = 31.f * 2.f;
const float ARCHER_HEIGHT = 40.f * 2.6f;
const float ARCHER_SPRITE_SCALE = 3.f;
const float ARCHER_SPEED = 30.f;

PlayingState::PlayingState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt):
	State(graphicsManager, states, dt)
{
	std::cout << "PlayingState" << std::endl;

	this->dt = dt;
	this->phase1 = Phase(this->graphicsManager);

	this->createMap();

	this->initPlayers();
	this->initEnemies();
}

PlayingState::~PlayingState()
{
	delete this->player1;

}

void PlayingState::createMap()
{
	for (int x = 0; x <= (int)WINDOW_WIDTH; x += (int)PLATFORM_WIDTH) {
		if (x <= (int)WINDOW_WIDTH / 2)
			this->phase1.setPlatform(sf::Vector2f((float)x, 384.f), "images/ground1.png", "GROUND_1", sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
		else
			this->phase1.setPlatform(sf::Vector2f((float)x, 384.f), "images/slime_floor.png", "SLOW", sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
		this->phase1.setPlatform(sf::Vector2f((float)x, 448.f), "images/ground2.png", "GROUND_2", sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
		this->phase1.setPlatform(sf::Vector2f((float)x, 512.f), "images/ground2.png", "GROUND_2", sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
		this->phase1.setPlatform(sf::Vector2f((float)x, 576.f), "images/ground2.png", "GROUND_2", sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
		this->phase1.setPlatform(sf::Vector2f((float)x, 640.f), "images/ground2.png", "GROUND_2", sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
	}

	this->phase1.setPlatform(sf::Vector2f(80.f, 384.f - 64.f), "images/fire.png", "FIRE", sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
	this->phase1.setPlatform(sf::Vector2f(300.f, 384.f - 64.f), "images/teleport.png", "TELEPORT", sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));

}

void PlayingState::initPlayers()
{
	this->player1 = new Player(this->graphicsManager, sf::Vector2f(500.f, 0.f), "images/player.png", "PLAYER", sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), this->dt, PLAYER_SPRITE_SCALE, PLAYER_SPEED);
	this->phase1.addEntity(this->player1);
}

void PlayingState::initEnemies()
{
	std::srand(time(NULL));
	//for (int i = 0; i < (3 + rand() % (4 + 1 - 3)); i++) {
	//	float pos = (float)(std::rand() % 1280);
	//	this->phase1.setEnemy(sf::Vector2f(pos, 0.f), "images/skeleton.png", "SKELETON", sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), &this->dt, SKELETON_SPRITE_SCALE, SKELETON_SPEED, this->player1);
	//}

	for (int i = 0; i < (3 + rand() % (4 + 1 - 3)); i++) {
		float pos = (float)(std::rand() % 1280);
		this->phase1.setEnemy2(sf::Vector2f(pos, 0.f), "images/archer.png", "ARCHER", sf::Vector2f(ARCHER_WIDTH, ARCHER_HEIGHT), this->dt, ARCHER_SPRITE_SCALE, ARCHER_SPEED, this->player1);
	}
}

void PlayingState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		this->graphicsManager->resetView();
		//aqui vai chamar a state de pause
		this->removeCurrentState();
		this->updateStateChange();
	}
}

// Verifica se está ocorrendo colisões entre o jogador e os outros objetos
void PlayingState::updateCollision()
{
	sf::Vector2f directionPlayerTmp;  // Vetor de direções
	sf::Vector2f directionEnemyTmp;

	PlatformList* phasePlatformList = this->phase1.getPlatformList();
	EntitiesList* phaseEntitiesList = this->phase1.getEntityList();

	for (int i = 0; i < (int)phasePlatformList->getSize(); i++) {
		if (phasePlatformList->operator[](i)->getCollider()->isColliding(this->player1->getCollider(), &directionPlayerTmp) && this->player1) {
			this->player1->updateCollision(directionPlayerTmp);

			/* FAZER UMA FUNÇÃO NA CLASSE DO PLAYER PARA ESSAS OPERAÇÕES: */
			if (directionPlayerTmp.y < 0.f)
				this->player1->setCanJump(true);

			if (phasePlatformList->operator[](i)->getObstacleType() == 2) // SLOW
				this->player1->setIsSlow(true);
			else {
				this->player1->setIsSlow(false);
				if (phasePlatformList->operator[](i)->getObstacleType() == 1) // FIRE
					this->player1->loseHp(1);
				else if (phasePlatformList->operator[](i)->getObstacleType() == 3) // TELEPORT
					this->player1->getShape()->setPosition(sf::Vector2f(340.f, 0.f));
			}
		}

		for (int j = 1; j < (int)phaseEntitiesList->getSize(); j++) {
			if (phasePlatformList->operator[](i)->getCollider()->isColliding(phaseEntitiesList->operator[](j)->getCollider(), &directionEnemyTmp))
				static_cast<Character*>(phaseEntitiesList->operator[](j))->updateCollision(directionEnemyTmp);
			if (this->player1 && this->player1->getSwordHitbox())
				if (this->player1->getSwordHitbox()->getShape()->getGlobalBounds().intersects(phaseEntitiesList->operator[](j)->getShape()->getGlobalBounds()))
					static_cast<Character*>(phaseEntitiesList->operator[](j))->loseHp(1);

			// COLISÃO COM SKELETON
			if (phaseEntitiesList->operator[](j)->getEntityType() == 2) // SKELETON
				if (this->player1->getCollider()->isColliding(phaseEntitiesList->operator[](j)->getCollider(), &directionEnemyTmp))
					this->player1->loseHp(2);
		}
	}
}

void PlayingState::update(float dt)
{
	this->updateInput();
	this->phase1.update();
	this->graphicsManager->updateView(this->player1->getShape());
	this->updateCollision();

}

void PlayingState::render()
{
	this->graphicsManager->setView();
	this->phase1.render();
}

void PlayingState::resetState()
{
}
