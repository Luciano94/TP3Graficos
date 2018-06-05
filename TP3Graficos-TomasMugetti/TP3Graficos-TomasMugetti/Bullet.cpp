#include "Bullet.h"

Bullet::Bullet(int bulletX, int bulletY)
{
	_bullet = al_load_bitmap(BULLET_SPRITE);
	if (!_bullet) {
		cout << "Bullet error";
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

void Bullet::update(bool &shot)
{
	if (_bulletY > -BULLET_SIZE && shot) {
		_bulletY -= BULLET_SPEED;
	}
	else {
		shot = false;
	}
}

void Bullet::setPosition(int bulletX,int bulletY)
{
	_bulletX = bulletX;
	_bulletY = bulletY;
}

bool Bullet::collision(int otherX, int otherY, int otherSize)
{
	return ((_bulletX < otherX + otherSize) && (otherX < _bulletX + BULLET_SIZE)
		&& (_bulletY < otherY + otherSize) && (otherY < _bulletY + BULLET_SIZE));
}

void Bullet::reset(bool &shot,int X, int Y)
{
	if (!shot) {
		shot = true;
		_bulletX = X + (PLAYER_SIZE / 2) - BULLET_SIZE;
		_bulletY = Y;
	}
}
