#include "Player.h"

Player::Player(){
	_player = al_load_bitmap(PLAYER_SPRITE);
	if (!_player) {
		cout << "Player error";
	}
	else {
		_playerX = 0;
		_playerY = 0;
		_lives = PLAYER_LIVES;
	}
}

Player::~Player(){
	al_destroy_bitmap(_player);
}

void Player::move( bool key[]){

	if (key[KEY_LEFT] && _playerX >= PLAYER_SPEED) {
		_playerX -= PLAYER_SPEED;
	}

	if (key[KEY_RIGHT] && _playerX <= SCREEN_W - PLAYER_SIZE - PLAYER_SPEED) {
		_playerX += PLAYER_SPEED;
	}
}

Bullet* Player::shot(bool &shot){
	if (!shot) {
		shot = true;
		return new Bullet(_playerX, _playerY);
	}
	else {
		shot = false;
	}
}

void Player::draw(){
	al_draw_bitmap(_player, _playerX, _playerY, 0);
}

void Player::setPosition(int x, int y) {
	_playerX = x;
	_playerY = y;
}