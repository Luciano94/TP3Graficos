#ifndef BULLET_H
#define BULLET_H
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "Definitions.h"

using namespace std;
class Bullet {
private:
	ALLEGRO_BITMAP* _bullet;
	int _bulletX;
	int _bulletY;
public:
	Bullet(int bulletX, int bulletY);
	~Bullet();
	void draw();
	void update(bool &shot);
	void setPosition(int bulletX,int bulletY);
	bool collision(int otherX, int otherY, int otherSize);
	void reset(bool &shot, int X, int Y);
};
#endif // !BULLET_H

