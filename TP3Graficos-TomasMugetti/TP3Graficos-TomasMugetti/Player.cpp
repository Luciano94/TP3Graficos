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

void Player::draw(){
	al_draw_bitmap(_player, _playerX, _playerY, 0);
}

void Player::setPosition(int x, int y) {
	_playerX = x;
	_playerY = y;
}

bool Player::collision(int otherX, int otherY, int otherSize)
{
	return ((_playerX < otherX + otherSize) && (otherX < _playerX + BULLET_SIZE)
		&& (_playerY < otherY + otherSize) && (otherY < _playerY + BULLET_SIZE));
}

void Player::life(bool &done)
{
	_lives--;
	if (_lives > 0) {
		_playerX = SCREEN_W / 2.0 - PLAYER_SIZE / 2.0;
		_playerY = SCREEN_H - PLAYER_SIZE;
	}
	else {
		done = true;
	}
}

int Player::getLives()
{
	return _lives;
}

int Player::getX()
{
	return _playerX;
}

int Player::getY()
{
	return _playerY;
}
