#include "Bullet.h"

Bullet::Bullet(int bulletX, int bulletY)
{
	_bullet = al_load_bitmap(PLAYER_SPRITE);
	if (!_bullet) {
		cout << "Player error";
	}
	else {
		_bulletX = bulletX;
		_bulletY = bulletY;
	}
}

Bullet::~Bullet()
{
	al_destroy_bitmap(_bullet);
}

void Bullet::draw()
{
	al_draw_bitmap(_bullet, _bulletX, _bulletY, 0);
}

void Bullet::update()
{
	if (_bulletY < BULLET_SIZE) {
		_bulletY -= BULLET_SPEED;
	}
	else {
		delete this;
	}
}

void Bullet::setPosition(int bulletX,int bulletY)
{
	_bulletX = bulletX;
	_bulletY = bulletY;
}
