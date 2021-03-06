#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_audio.h"
#include "Definitions.h"
#include "Bullet.h"
using namespace std;

class Player {
private:
	ALLEGRO_BITMAP* _player;
	int _playerX;
	int _playerY;
	int _lives;
public:
	Player();
	~Player();
	void draw();
	void move(bool key[]);
	void setPosition(int x, int y);
	bool collision(int otherX, int otherY, int otherSize);
	void life(bool &done);
	int getLives();
	int getX();
	int getY();
};
#endif // !PLAYER_H

