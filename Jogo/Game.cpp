#include "Game.h"

const float PLAYER_WIDTH = 32.f * 2.f;
const float PLAYER_HEIGHT = 35.f * 2.6f;
const float PLAYER_SPRITE_SCALE = 3.f;
const float PLAYER_SPEED = 200.f;
const float PLATFORM_WIDTH = 64.f;
const float PLATFORM_HEIGHT = 64.f;

const float SKELETON_WIDTH = 50.f * 3.f;
const float SKELETON_HEIGHT = 48.f * 3.f;
const float SKELETON_SPRITE_SCALE = 1.f;
const float SKELETON_SPEED = 100.f;

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
	delete this->enemy1;
	delete this->enemy2;
	delete this->player1;
}

void Game::createMap()
{
	for (int x = 0; x <= 1280; x += 64) {
		this->phase1.setPlatform(sf::Vector2f((float)x, 512.f), "images/grass.png", "GRASS", sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
		this->phase1.setPlatform(sf::Vector2f((float)x, 512.f), "images/ground1.png", "GROUND_1", sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));

		this->phase1.setPlatform(sf::Vector2f((float)x, 576.f), "images/ground2.png", "GROUND_2", sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
		this->phase1.setPlatform(sf::Vector2f((float)x, 640.f), "images/ground2.png", "GROUND_2", sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
	}
}

void Game::initPlayers()
{
	this->player1 = new Player(&this->graphicsManager, sf::Vector2f(200.f, 0.f), "images/playerTeste.png", "PLAYER", sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), &this->dt, PLAYER_SPRITE_SCALE, PLAYER_SPEED);
}

void Game::initEnemies()
{
	std::srand(time(NULL));
	for (int i = 0; i < (3 + rand() % (10 + 1 - 3)); i++) {
		float pos = std::rand() % 1280;
		skeletonList.addEntity(new Enemy(&this->graphicsManager, sf::Vector2f(pos, 0.f), "images/skeleton.png", "SKELETON", sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), &this->dt, SKELETON_SPRITE_SCALE, SKELETON_SPEED));
		static_cast<Enemy*>(this->skeletonList[i])->setPlayer(this->player1);
	}

	for (int i = 0; i < (3 + rand() % (10 + 1 - 3)); i++) {
		float pos = std::rand() % 1280;
		archerList.addEntity(new EnemyProjectile(&this->graphicsManager, sf::Vector2f(pos, 0.f), "images/archer.png", "ARCHER", sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), &this->dt, SKELETON_SPRITE_SCALE, SKELETON_SPEED));
		static_cast<EnemyProjectile*>(this->archerList[i])->setPlayer(this->player1);
	}
}

// Verifica constantemente várias ações que são necessárias para o bom funcionamento da aplicação
void Game::update()
{
	this->updateSFMLEvents();
	this->player1->update();
	this->updateEnemies();
	this->updateCollision();
}

void Game::updateEnemies() {
	for (int i = 0; i < skeletonList.getSize(); i++) {
		static_cast<Enemy*>(this->skeletonList[i])->update();
	}

	for (int i = 0; i < archerList.getSize(); i++) {
		static_cast<EnemyProjectile*>(this->archerList[i])->update();
	}
}

// Verifica se o usuário pediu para fechar a janela
void Game::updateSFMLEvents()
{
	while (this->graphicsManager.pollEvent(&this->sfEvent))
		if (this->sfEvent.type == sf::Event::Closed)
			this->graphicsManager.closeWindow();
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
	Collider* colliderPlayerTmp = this->player1->getCollider();  // Objeto Collider do player
	

	// Verifica colisão dos esqueletos
	for (int i = 0; i < skeletonList.getSize(); i++) {
		sf::Vector2f directionSkeletonTmp;
		Collider* colliderSkeletonTmp = this->skeletonList[i]->getCollider();
		for (int j = 0; j < this->phase1.getPlatformList()->getSize(); j++) {
			if (this->phase1.getPlatformList()->operator[](j)->getCollider()->isColliding(colliderSkeletonTmp, &directionSkeletonTmp))
				static_cast<Enemy*>(this->skeletonList[i])->updateCollision(directionSkeletonTmp);
		}
	}

	// Verifica colisão dos arqueiros
	for (int i = 0; i < archerList.getSize(); i++) {
		sf::Vector2f directionArcherTmp;
		Collider* colliderArcherTmp = this->archerList[i]->getCollider();
		for (int j = 0; j < this->phase1.getPlatformList()->getSize(); j++) {
			if (this->phase1.getPlatformList()->operator[](j)->getCollider()->isColliding(colliderArcherTmp, &directionArcherTmp))
				static_cast<EnemyProjectile*>(this->archerList[i])->updateCollision(directionArcherTmp);
		}
	}

	for (int i = 0; i < this->phase1.getPlatformList()->getSize(); i++) {
		/* Se verdadeiro, o player colidiu com algum bloco */
		if (this->phase1.getPlatformList()->operator[](i)->getCollider()->isColliding(colliderPlayerTmp, &directionPlayerTmp))
			this->player1->updateCollision(directionPlayerTmp);
	}

}

// Desenha todos os objetos do jogo na janela
void Game::render()
{
	this->graphicsManager.clearWindow();  // Limpa a janela

	// Desenha os blocos do mapa
	for (int i = 0; i < this->phase1.getPlatformList()->getSize(); i++)
		this->phase1.renderShape(i);

	// Desenha o player
	this->player1->renderSprite();
	//this->player1->renderSwordHitBox_TMP();


	for (int i = 0; i < skeletonList.getSize(); i++) {
		this->graphicsManager.renderShape(this->skeletonList[i]->getShape());
		static_cast<Enemy*>(this->skeletonList[i])->renderSprite();
	}

	for (int i = 0; i < archerList.getSize(); i++) {
		this->graphicsManager.renderShape(this->archerList[i]->getShape());
		static_cast<EnemyProjectile*>(this->archerList[i])->renderSprite();
		static_cast<EnemyProjectile*>(this->archerList[i])->renderArrowHitbox_TMP();
	}

	this->graphicsManager.displayWindow();  // Imprime todos os objetos que foram renderizados na janela
}

// Loop principal do jogo
void Game::execute()
{
	while (this->graphicsManager.isWindowOpen()) {
		this->updateDeltaTime();
		this->update();
		this->render();
	}
}