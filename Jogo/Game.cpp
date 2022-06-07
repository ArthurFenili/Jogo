#include "Game.h"

const float PLATFORM_WIDTH = 64.f;
const float PLATFORM_HEIGHT = 64.f;

const float PLAYER_WIDTH = 32.f * 1.6f;
const float PLAYER_HEIGHT = 35.f * 2.2f;
const float PLAYER_SPRITE_SCALE = 3.f;
const float PLAYER_SPEED = 200.f;
const long int PLAYER_HP = 400000;

const float SKELETON_WIDTH = 32.f * 2.f;
const float SKELETON_HEIGHT = 35.f * 2.6f;
const float SKELETON_SPRITE_SCALE = 3.f;

const float TELEPORT_SPRITE_SCALE = 2.3f;

sf::Vector2f FIRE_SIZE = sf::Vector2f(64.f * 0.3f, 64.f * 0.8f);
sf::Vector2f TELEPORT_SIZE = sf::Vector2f(64.f * 0.4f, 64.f);

Game::Game()
{
	this->phase1 = Phase(&this->graphicsManager, &this->dt, PHASE);

	this->phase1.loadMap("images/map1.txt");

	this->player1 = new Player(&this->graphicsManager, &this->dt, PLAYER, PLAYER_SPRITE_SCALE, sf::Vector2f(704.f, 640.f), sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), "images/player.png", "PLAYER", PLAYER_SPEED, PLAYER_HP);
	this->phase1.setPlayer(this->player1);

	//this->phase1.createEntity(FIRE, 1.f, sf::Vector2f(880.f, 1400.f), FIRE_SIZE, "images/fire.png", "FIRE");
	//this->phase1.createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(500.f, 1400.f), TELEPORT_SIZE, "images/teleport.png", "TELEPORT");
	//this->phase1.createEntity(ENEMY, SKELETON_SPRITE_SCALE, sf::Vector2f(950.f, 1400.f), sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), "images/skeleton.png", "SKELETON");

	this->phase1.addEntity(this->player1);

	execute();
}

Game::~Game()
{
	if (this->player1) {
		delete this->player1;
		this->player1 = nullptr;
	}
	this->phase1.clearPlatformList();
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
	
	Entity** platformList = this->phase1.getPlatformList(); // PLATAFORMAS (BLOCOS E BACKGROUND E DOOR)
	EntityList* entityList = this->phase1.getEntityList(); // PLAYER, ENEMY E OBSTACULOS (FIRE, SLOW, TELEPORT)
	
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 50; j++) {
			if (platformList[i][j].getId() == BLOCK) {
				
				if (platformList[i][j].getCollider()->isColliding(this->player1->getCollider(), &directionPlayerTmp)) {
					this->player1->updateCollision(directionPlayerTmp);

					if (directionPlayerTmp.y < 0.f)
						this->player1->setCanJump(true);
				}
				
				for (int k = 0; k < entityList->getSize() - 1;  k++) {
					if (entityList->operator[](k)->getId() == ENEMY) {
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
								this->player1->getShape()->setPosition(sf::Vector2f(900.f, 1400.f));
							}
						}
						else if (entityList->operator[](k)->getId() == FIRE && this->player1->getShape()->getGlobalBounds().intersects(entityList->operator[](k)->getShape()->getGlobalBounds())) {
							this->player1->setIsSlow(false);
							this->player1->loseHp();
						}
					}
				}
			}		
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