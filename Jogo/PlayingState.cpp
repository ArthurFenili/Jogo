#include "PlayingState.h"

const float PLATFORM_WIDTH = 64.f;
const float PLATFORM_HEIGHT = 64.f;

const float PLAYER_WIDTH = 32.f * 1.6f;
const float PLAYER_HEIGHT = 35.f * 2.2f;
const float PLAYER_SPRITE_SCALE = 3.f;
const float PLAYER_SPEED = 250.f;
const long int PLAYER_HP = 90000;

const float SKELETON_WIDTH = 32.f * 2.f;
const float SKELETON_HEIGHT = 35.f * 2.6f;
const float SKELETON_SPRITE_SCALE = 3.f;

const float ARCHER_WIDTH = 31.f * 2.f;
const float ARCHER_HEIGHT = 40.f * 2.6f;
const float ARCHER_SPRITE_SCALE = 3.f;
const float ARCHER_SPEED = 30.f;

const float TELEPORT_SPRITE_SCALE = 2.3f;

sf::Vector2f FIRE_SIZE = sf::Vector2f(64.f * 0.3f, 64.f * 0.8f);
sf::Vector2f TELEPORT_SIZE = sf::Vector2f(64.f * 0.4f, 55.f);

int PlayingState::score(0);
bool PlayingState::twoPlayers(false);

PlayingState::PlayingState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt, bool twoP) :
	State(graphicsManager, states, dt)
{
	this->dt = dt;
	this->setPhase(new ForestPhase(this->graphicsManager, this->dt, FOREST_PHASE));
	this->exit = false;
	this->score = 0;
	this->twoPlayers = twoP;

	this->createPlayers();
	this->createMap();

	srand((unsigned)time(0));

	this->createObstacles(FOREST_PHASE);
	this->createEnemies(FOREST_PHASE);

	this->currentPhase->addEntity(this->player1);

	if (PlayingState::twoPlayers)
		this->currentPhase->addEntity(this->player2);
}

PlayingState::~PlayingState()
{
	if (this->player1) {
		delete this->player1;
		this->player1 = nullptr;
	}

	if (this->player2) {
		delete this->player2;
		this->player2 = nullptr;
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

		int obstacle1, obstacle2;
		obstacle1 = rand() % 3;
		obstacle2 = obstacle1;
		while (obstacle2 == obstacle1)
			obstacle2 = rand() % 3;

		int fireAmount = (rand() % 3) + 3;
		int teleportAmount = (rand() % 2) + 3;
		int slowAmount = (rand() % 5) + 3;

		//fogo
		if (obstacle1 == 0 || obstacle2 == 0) {
			this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(16.f * 64.f, 14.f * 64.f), FIRE_SIZE, "images/fire_p1.png", "FIRE_P1");
			this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(17.f * 64.f, 14.f * 64.f), FIRE_SIZE, "images/fire_p1.png", "FIRE_P1");
			this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(20.f * 64.f, 13.f * 64.f), FIRE_SIZE, "images/fire_p1.png", "FIRE_P1");
			if (fireAmount > 3)
				this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(19.f * 64.f, 6.f * 64.f), FIRE_SIZE, "images/fire_p1.png", "FIRE_P1");
			if (fireAmount > 4)
				this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(14.f * 64.f, 77.f * 64.f), FIRE_SIZE, "images/fire_p1.png", "FIRE_P1");
		}
		//teleport
		if (obstacle1 == 1 || obstacle2 == 1) {
			this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(9.f * 64.f, 15.f * 64.f + 9.f), TELEPORT_SIZE, "images/teleport_p1.png", "TELEPORT_P1");
			this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(22.f * 64.f, 15.f * 64.f + 9.f), TELEPORT_SIZE, "images/teleport_p1.png", "TELEPORT_P1");
			this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(25.f * 64.f, 15.f * 64.f + 9.f), TELEPORT_SIZE, "images/teleport_p1.png", "TELEPORT_P1");
			if (teleportAmount > 3)
				this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(12.f * 64.f, 6.f * 64.f + 9.f), TELEPORT_SIZE, "images/teleport_p1.png", "TELEPORT_P1");
		}
		//slow
		if (obstacle1 == 2 || obstacle2 == 2) {
			this->currentPhase->getPlatformList()[16][7] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(7.f * 64.f, 16.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow_p1.png", "SLOW_P1");
			this->currentPhase->getPlatformList()[16][8] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(8.f * 64.f, 16.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow_p1.png", "SLOW_P1");
			this->currentPhase->getPlatformList()[13][13] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(13.f * 64.f, 13.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow_p1.png", "SLOW_P1");
			if (slowAmount > 3)
				this->currentPhase->getPlatformList()[13][14] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(14.f * 64.f, 13.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow_p1.png", "SLOW_P1");
			if (slowAmount > 4)
				this->currentPhase->getPlatformList()[9][22] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(22.f * 64.f, 9.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow_p1.png", "SLOW_P1");
			if (slowAmount > 5)
				this->currentPhase->getPlatformList()[7][7] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(7.f * 64.f, 7.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow_p1.png", "SLOW_P1");
			if (slowAmount > 6)
				this->currentPhase->getPlatformList()[7][8] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(8.f * 64.f, 7.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow_p1.png", "SLOW_P1");
		}
	}

	else if (phase == CASTLE_PHASE) {
		int obstacle1, obstacle2;
		obstacle1 = rand() % 3;
		obstacle2 = obstacle1;
		while (obstacle2 == obstacle1)
			obstacle2 = rand() % 3;

		int fireAmount = (rand() % 3) + 3;
		int teleportAmount = (rand() % 2) + 3;
		int slowAmount = (rand() % 6) + 3;

		//fire
		if (obstacle1 == 0 || obstacle2 == 0) {
			this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(11.f * 64.f, 14.f * 64.f), FIRE_SIZE, "images/fire.png", "FIRE");
			this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(15.f * 64.f, 13.f * 64.f), FIRE_SIZE, "images/fire.png", "FIRE");
			this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(17.f * 64.f, 16.f * 64.f), FIRE_SIZE, "images/fire.png", "FIRE");
			if (fireAmount > 3)
				this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(24.f * 64.f, 10.f * 64.f), FIRE_SIZE, "images/fire.png", "FIRE");
			if (fireAmount > 4)
				this->currentPhase->createEntity(FIRE, 1.f, sf::Vector2f(25.f * 64.f, 10.f * 64.f), FIRE_SIZE, "images/fire.png", "FIRE");
		}
		//teleport
		if (obstacle1 == 1 || obstacle2 == 1) {
			this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(9.f * 64.f, 16.f * 64.f), TELEPORT_SIZE, "images/teleport.png", "TELEPORT");
			this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(22.f * 64.f, 16.f * 64.f), TELEPORT_SIZE, "images/teleport.png", "TELEPORT");
			this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(18.f * 64.f, 8.f * 64.f), TELEPORT_SIZE, "images/teleport.png", "TELEPORT");
			if (teleportAmount > 3)
				this->currentPhase->createEntity(TELEPORT, TELEPORT_SPRITE_SCALE, sf::Vector2f(12.f * 64.f, 7.f * 64.f), TELEPORT_SIZE, "images/teleport.png", "TELEPORT");
		}
		//slow
		if (obstacle1 == 2 || obstacle2 == 2) {
			this->currentPhase->getPlatformList()[17][7] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(7.f * 64.f, 17.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow.png", "SLOW");
			this->currentPhase->getPlatformList()[17][8] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(8.f * 64.f, 17.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow.png", "SLOW");
			this->currentPhase->getPlatformList()[13][18] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(18.f * 64.f, 13.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow.png", "SLOW");
			if (slowAmount > 3)
				this->currentPhase->getPlatformList()[13][19] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(19.f * 64.f, 13.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow.png", "SLOW");
			if (slowAmount > 4)
				this->currentPhase->getPlatformList()[13][20] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(20.f * 64.f, 13.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow.png", "SLOW");
			if (slowAmount > 5)
				this->currentPhase->getPlatformList()[11][23] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(23.f * 64.f, 11.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow.png", "SLOW");
			if (slowAmount > 6)
				this->currentPhase->getPlatformList()[9][19] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(19.f * 64.f, 9.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow.png", "SLOW");
			if (slowAmount > 7)
				this->currentPhase->getPlatformList()[9][20] = this->currentPhase->createEntity(SLOW, 1.f, sf::Vector2f(20.f * 64.f, 9.f * 64.f), sf::Vector2f(64.f, 64.f), "images/slow.png", "SLOW");
		}
	}
}

void PlayingState::createEnemies(int phase)
{
	if (phase == FOREST_PHASE) {

		int skeletonAmount = (rand() % 3) + 3;
		int archerAmount = (rand() % 2) + 3;

		this->currentPhase->createEntity(SKELETON, SKELETON_SPRITE_SCALE, sf::Vector2f(7.f * 64.f, 15.f * 64.f), sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), "images/skeleton.png", "SKELETON");
		this->currentPhase->createEntity(SKELETON, SKELETON_SPRITE_SCALE, sf::Vector2f(13.f * 64.f, 12.f * 64.f), sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), "images/skeleton.png", "SKELETON");
		this->currentPhase->createEntity(SKELETON, SKELETON_SPRITE_SCALE, sf::Vector2f(19.f * 64.f, 12.f * 64.f), sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), "images/skeleton.png", "SKELETON");

		if (skeletonAmount > 3)
			this->currentPhase->createEntity(SKELETON, SKELETON_SPRITE_SCALE, sf::Vector2f(23.f * 64.f, 15.f * 64.f), sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), "images/skeleton.png", "SKELETON");
		if (skeletonAmount > 4)
			this->currentPhase->createEntity(SKELETON, SKELETON_SPRITE_SCALE, sf::Vector2f(11.f * 64.f, 5.f * 64.f), sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), "images/skeleton.png", "SKELETON");

		this->currentPhase->createEntity(ARCHER, ARCHER_SPRITE_SCALE, sf::Vector2f(15.f * 64.f, 12.f * 64.f), sf::Vector2f(ARCHER_WIDTH, ARCHER_HEIGHT), "images/archer_running.png", "ARCHER");
		this->currentPhase->createEntity(ARCHER, ARCHER_SPRITE_SCALE, sf::Vector2f(18.f * 64.f, 12.f * 64.f), sf::Vector2f(ARCHER_WIDTH, ARCHER_HEIGHT), "images/archer_running.png", "ARCHER");
		this->currentPhase->createEntity(ARCHER, ARCHER_SPRITE_SCALE, sf::Vector2f(24.f * 64.f, 12.f * 64.f), sf::Vector2f(ARCHER_WIDTH, ARCHER_HEIGHT), "images/archer_running.png", "ARCHER");
		if (archerAmount > 3)
			this->currentPhase->createEntity(ARCHER, ARCHER_SPRITE_SCALE, sf::Vector2f(18.f * 64.f, 6.f * 64.f), sf::Vector2f(ARCHER_WIDTH, ARCHER_HEIGHT), "images/archer_running.png", "ARCHER");
	}

	else if (phase == CASTLE_PHASE) {
		int skeletonAmount = (rand() % 2) + 3;
		int archerAmount = (rand() % 2) + 3;

		this->currentPhase->createEntity(SKELETON, SKELETON_SPRITE_SCALE, sf::Vector2f(6.f * 64.f, 16.f * 64.f), sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), "images/skeleton.png", "SKELETON");
		this->currentPhase->createEntity(SKELETON, SKELETON_SPRITE_SCALE, sf::Vector2f(18.f * 64.f, 16.f * 64.f), sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), "images/skeleton.png", "SKELETON");
		this->currentPhase->createEntity(SKELETON, SKELETON_SPRITE_SCALE, sf::Vector2f(20.f * 64.f, 16.f * 64.f), sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), "images/skeleton.png", "SKELETON");

		if (skeletonAmount > 3)
			this->currentPhase->createEntity(SKELETON, SKELETON_SPRITE_SCALE, sf::Vector2f(24.f * 64.f, 16.f * 64.f), sf::Vector2f(SKELETON_WIDTH, SKELETON_HEIGHT), "images/skeleton.png", "SKELETON");

		this->currentPhase->createEntity(ARCHER, ARCHER_SPRITE_SCALE, sf::Vector2f(12.f * 64.f, 14.f * 64.f), sf::Vector2f(ARCHER_WIDTH, ARCHER_HEIGHT), "images/archer_running.png", "ARCHER");
		this->currentPhase->createEntity(ARCHER, ARCHER_SPRITE_SCALE, sf::Vector2f(14.f * 64.f, 13.f * 64.f), sf::Vector2f(ARCHER_WIDTH, ARCHER_HEIGHT), "images/archer_running.png", "ARCHER");
		this->currentPhase->createEntity(ARCHER, ARCHER_SPRITE_SCALE, sf::Vector2f(26.f * 64.f, 10.f * 64.f), sf::Vector2f(ARCHER_WIDTH, ARCHER_HEIGHT), "images/archer_running.png", "ARCHER");

		if (archerAmount > 3)
			this->currentPhase->createEntity(ARCHER, ARCHER_SPRITE_SCALE, sf::Vector2f(16.f * 64.f, 8.f * 64.f), sf::Vector2f(ARCHER_WIDTH, ARCHER_HEIGHT), "images/archer_running.png", "ARCHER");

		// BOSS AQUI
	}
}

void PlayingState::createPlayers()
{
	this->player1 = new Player(this->graphicsManager, this->dt, PLAYER, PLAYER_SPRITE_SCALE, sf::Vector2f(4.f * 64.f, 15.f * 64.f), sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), "images/player.png", "PLAYER", PLAYER_SPEED, PLAYER_HP, 1);
	this->currentPhase->setPlayer1(this->player1);

	if (twoPlayers) {
		this->player2 = new Player(this->graphicsManager, this->dt, PLAYER, PLAYER_SPRITE_SCALE, sf::Vector2f(5.f * 64.f, 15.f * 64.f), sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), "images/player2.png", "PLAYER_2", PLAYER_SPEED, PLAYER_HP, 2);
		this->currentPhase->setPlayer2(this->player2);
	}
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

void PlayingState::update(float dt)
{
	this->updateInput();

	float aspectRatio = (float)this->graphicsManager->getWindow()->getSize().x / (float)this->graphicsManager->getWindow()->getSize().y;
	this->graphicsManager->setViewSize(sf::Vector2f(512.f * aspectRatio, 512.f));

	this->currentPhase->update();
	if (this->currentPhase->getPhaseEnd())
		this->changeLevel();
	this->graphicsManager->updateView(this->player1->getShape());
}

void PlayingState::render()
{
	this->graphicsManager->clearWindow(this->currentPhase->getId());
	this->graphicsManager->setView();
	this->currentPhase->render();
}

void PlayingState::changeLevel()
{
	this->currentPhase->clearPlatformList();
	this->currentPhase->clearEntityList();

	delete this->currentPhase;

	this->setPhase(new CastlePhase(this->graphicsManager, this->dt, CASTLE_PHASE));

	this->currentPhase->loadMap("images/castle_map.txt");
	this->currentPhase->setPlayer1(this->player1);

	if (twoPlayers)
		this->currentPhase->setPlayer2(this->player2);

	this->createObstacles(CASTLE_PHASE);
	this->createEnemies(CASTLE_PHASE);

	this->currentPhase->addEntity(this->player1);

	if (twoPlayers)
		this->currentPhase->addEntity(this->player2);

	this->player1->getShape()->setPosition(sf::Vector2f(4.f * 64.f, 15.f * 64.f));

	if (twoPlayers)
		this->player2->getShape()->setPosition(sf::Vector2f(5.f * 64.f, 15.f * 64.f));
}