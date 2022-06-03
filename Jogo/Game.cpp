#include "Game.h"

const float WINDOW_WIDTH = 800.f;
const float WINDOW_HEIGHT = 600.f;

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

Game::Game()
{
	this->phase1 = Phase(&this->graphicsManager);

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
	this->phase1.loadMap("images/map.txt");

}

void Game::initPlayers()
{
	this->player1 = new Player(&this->graphicsManager, sf::Vector2f(500.f, 0.f), "images/player.png", "PLAYER", sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), &this->dt, PLAYER_SPRITE_SCALE, PLAYER_SPEED);
	this->phase1.addEntity(this->player1);
}

void Game::initEnemies()
{
	this->phase1.setEnemy(sf::Vector2f(200.f, 0.f), "images/skeleton.png", "SKELETON", sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), &this->dt, SKELETON_SPRITE_SCALE, SKELETON_SPEED, this->player1);
	this->phase1.setEnemy(sf::Vector2f(300.f, 0.f), "images/skeleton.png", "SKELETON", sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), &this->dt, SKELETON_SPRITE_SCALE, SKELETON_SPEED, this->player1);
	this->phase1.setEnemy(sf::Vector2f(400.f, 0.f), "images/skeleton.png", "SKELETON", sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), &this->dt, SKELETON_SPRITE_SCALE, SKELETON_SPEED, this->player1);
	this->phase1.setEnemy(sf::Vector2f(500.f, 0.f), "images/skeleton.png", "SKELETON", sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), &this->dt, SKELETON_SPRITE_SCALE, SKELETON_SPEED, this->player1);
}

// Verifica constantemente v�rias a��es que s�o necess�rias para o bom funcionamento da aplica��o
void Game::update()
{
	this->updateSFMLEvents();
	this->phase1.update();
	this->graphicsManager.updateView(this->player1->getShape());
	this->updateCollision();
}

// Verifica se o usu�rio pediu para fechar a janela
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

	/* Conserta um bug no qual se voc� arrastar a janela com o mouse, o player muda de posi��o */
	if (this->dt > 1.f / 20.f)
		this->dt = 1.f / 20.f;
}

// Verifica se est� ocorrendo colis�es entre o jogador e os outros objetos
void Game::updateCollision()
{
	sf::Vector2f directionPlayerTmp;  // Vetor de dire��es
	sf::Vector2f directionEnemyTmp;

	PlatformList* phasePlatformList = this->phase1.getPlatformList();
	EntityList* phaseEntityList = this->phase1.getEntityList();

	for (int i = 0; i < phasePlatformList->getSize(); i++) {
		// N�O � FIRE
		if (phasePlatformList->operator[](i)->getObstacleType() != 1) {
			
			if (phasePlatformList->operator[](i)->getCollider()->isColliding(this->player1->getCollider(), &directionPlayerTmp) && this->player1) {
				this->player1->updateCollision(directionPlayerTmp);

				if (directionPlayerTmp.y < 0.f)
					this->player1->setCanJump(true);

				if (phasePlatformList->operator[](i)->getObstacleType() == 2) // SLOW
					this->player1->setIsSlow(true);
				else {
					this->player1->setIsSlow(false);
					if (phasePlatformList->operator[](i)->getObstacleType() == 3) // TELEPORT
						this->player1->getShape()->setPosition(sf::Vector2f(500.f, 320.f));
				}
			}

			for (int j = 1; j < phaseEntityList->getSize(); j++) {
				if (phasePlatformList->operator[](i)->getCollider()->isColliding(phaseEntityList->operator[](j)->getCollider(), &directionEnemyTmp))
					static_cast<Character*>(phaseEntityList->operator[](j))->updateCollision(directionEnemyTmp);
				if (this->player1 && this->player1->getSwordHitbox())
					if (this->player1->getSwordHitbox()->getShape()->getGlobalBounds().intersects(phaseEntityList->operator[](j)->getShape()->getGlobalBounds()))
						static_cast<Character*>(phaseEntityList->operator[](j))->loseHp();
			}
		}

		else
			if (this->player1->getShape()->getGlobalBounds().intersects(phasePlatformList->operator[](i)->getShape()->getGlobalBounds()))
				this->player1->loseHp();
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