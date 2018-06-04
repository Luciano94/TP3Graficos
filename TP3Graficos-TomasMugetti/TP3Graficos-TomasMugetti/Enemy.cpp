#include "Enemy.h"

Enemy::Enemy()
{
	_enemy = al_load_bitmap(ENEMY_SPRITE);
	if (!_enemy)
		cout << "Enemy fail";
	else {
		srand(time(0));
		_enemyX = 0;
		_enemyY = 0;
	}
}

Enemy::~Enemy()
{
	al_destroy_bitmap(_enemy);
}

int Enemy::getEnemyX() {
	return _enemyX;
}

int Enemy::getEnemyY(){
	return _enemyY;
}

void Enemy::reset(){
	_enemyY = ENEMY_SIZE;
	_enemyX = rand() % (SCREEN_W - ENEMY_SIZE - 20 + 1);

}

void Enemy::draw()
{
	al_draw_bitmap(_enemy, _enemyX, _enemyY, 0);
	if (_enemyY < SCREEN_H)
		_enemyY += ENEMY_SPEED;
	else {
		_enemyY = ENEMY_SIZE;
		_enemyX = rand() % (SCREEN_W - ENEMY_SIZE - 20 + 1);
	}
}

void Enemy::setPosition(int x, int y)
{
	_enemyX = x;
	_enemyY = y;
}
