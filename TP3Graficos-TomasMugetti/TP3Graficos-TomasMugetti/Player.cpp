#include "Player.h"

Player::Player(char* spriteFile, int playerSize){
	_player = al_load_bitmap(spriteFile);
	if (!_player) {
		cout << "Player error";
	}
	_playerSize = playerSize;
	_playerX = 0;
	_playerY = 0;
}

Player::~Player(){
	al_destroy_bitmap(_player);
}

void Player::move(){
	//movimiento del player
}

void Player::shot(){
	// disparo del player
}

void Player::draw(){
	al_draw_bitmap(_player, _playerX, _playerY, 0);
}

void Player::setPosition(int x, int y) {
	_playerX = x;
	_playerY = y;
}