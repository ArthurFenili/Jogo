#include "Game.h"

const float PLATFORM_WIDTH = 64.f;
const float PLATFORM_HEIGHT = 64.f;

const float PLAYER_WIDTH = 32.f * 1.6f;
const float PLAYER_HEIGHT = 35.f * 2.2f;
const float PLAYER_SPRITE_SCALE = 3.f;
const float PLAYER_SPEED = 200.f;

const float SKELETON_WIDTH = 32.f * 2.f;
const float SKELETON_HEIGHT = 35.f * 2.6f;
const float SKELETON_SPRITE_SCALE = 3.f;
const float SKELETON_SPEED = 30.f;

Game::Game()
{
	this->phase1 = Phase(&this->graphicsManager, &this->dt);

	this->createMap();

	this->initPlayers();
	this->initEnemies();

	execute();
}

Game::~Game()
{
	if (this->player1)
		delete this->player1;
}

void Game::createMap()
{
	this->phase1.loadMap("images/mapa2.txt");

}

void Game::initPlayers()
{
	this->player1 = new Player(&this->graphicsManager, sf::Vector2f(900.f, 1400.f), "images/player.png", "PLAYER", sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), &this->dt, PLAYER_SPRITE_SCALE, PLAYER_SPEED);
	this->phase1.addEntity(this->player1);
}

void Game::initEnemies()
{
	this->phase1.setEnemy(sf::Vector2f(200.f, 0.f), "images/skeleton.png", "SKELETON", sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), &this->dt, SKELETON_SPRITE_SCALE, SKELETON_SPEED, this->player1);
	this->phase1.setEnemy(sf::Vector2f(300.f, 0.f), "images/skeleton.png", "SKELETON", sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), &this->dt, SKELETON_SPRITE_SCALE, SKELETON_SPEED, this->player1);
	this->phase1.setEnemy(sf::Vector2f(400.f, 0.f), "images/skeleton.png", "SKELETON", sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), &this->dt, SKELETON_SPRITE_SCALE, SKELETON_SPEED, this->player1);
	this->phase1.setEnemy(sf::Vector2f(500.f, 0.f), "images/skeleton.png", "SKELETON", sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), &this->dt, SKELETON_SPRITE_SCALE, SKELETON_SPEED, this->player1);
}

// Verifica constantemente várias ações que são necessárias para o bom funcionamento da aplicação
void Game::update()
{
	this->updateSFMLEvents();
	this->phase1.update();
	this->graphicsManager.updateView(this->player1->getShape());
	this->updateCollision();
}

// Verifica se o usuário pediu para fechar a janela
void Game::updateSFMLEvents()
{
	while (this->graphicsManager.pollEvent(&this->sfEvent)) {
		if (this->sfEvent.type == sf::Event::Closed)
			this->graphicsManager.closeWindow();
		if (this->sfEvent.type == sf::Event::Resized)
			this->graphicsManager.resizeView();
	}
}

// Calcula o Delta Time constantemente
void Game::updateDeltaTime()
{
	this->dt = this->dtClock.restart().asSeconds();

	/* Conserta um bug no qual se você arrastar a janela com o mouse, o player muda de posição */
	if (this->dt > 1.f / 20.f)
		this->dt = 1.f / 20.f;
}

// Verifica se está ocorrendo colisões entre o jogador e os outros objetos
void Game::updateCollision()
{
	sf::Vector2f directionPlayerTmp;  // Vetor de direções
	sf::Vector2f directionEnemyTmp;

	Platform** phasePlatformList = this->phase1.getPlatformList();
	EntityList* phaseEntityList = this->phase1.getEntityList();

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 50; j++) {
			if (phasePlatformList[i][j].getObstacleType() != 1 && phasePlatformList[i][j].getObstacleType() != 5 && phasePlatformList[i][j].getObstacleType() != 6) {
				if (phasePlatformList[i][j].getCollider()->isColliding(this->player1->getCollider(), &directionPlayerTmp)) {
					this->player1->updateCollision(directionPlayerTmp);

					if (directionPlayerTmp.y < 0.f)
						this->player1->setCanJump(true);
					if (phasePlatformList[i][j].getObstacleType() == 2)
						this->player1->setIsSlow(true);
					else {
						this->player1->setIsSlow(false);
						if (phasePlatformList[i][j].getObstacleType() == 3)
							this->player1->getShape()->setPosition(sf::Vector2f(900.f, 1400.f));
					}
				}
				for (int k = 1; k < phaseEntityList->getSize();  k++) {
					if (phasePlatformList[i][j].getCollider()->isColliding(phaseEntityList->operator[](k)->getCollider(), &directionEnemyTmp))
						static_cast<Character*>(phaseEntityList->operator[](k))->updateCollision(directionEnemyTmp);
					if (this->player1 && this->player1->getSwordHitbox())
						if (this->player1->getSwordHitbox()->getShape()->getGlobalBounds().intersects(phaseEntityList->operator[](k)->getShape()->getGlobalBounds()))
							static_cast<Character*>(phaseEntityList->operator[](k))->loseHp();
				}
			}
			else if (phasePlatformList[i][j].getObstacleType() == 1 && this->player1->getShape()->getGlobalBounds().intersects(phasePlatformList[i][j].getShape()->getGlobalBounds()))
				this->player1->loseHp();
		}
	}
}

void Game::render()
{
	this->graphicsManager.clearWindow();  // Limpa a janela
	
	this->graphicsManager.setView();

	this->phase1.render();

	this->graphicsManager.displayWindow();  // Imprime todos os objetos que foram renderizados na janela
}

void Game::execute()
{
	while (this->graphicsManager.isWindowOpen()) {
		this->updateDeltaTime();
		this->update();
		this->render();
	}
}