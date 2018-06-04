#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "Definitions.h"
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
	void shot();
	void setPosition(int x, int y);
};
#endif // !PLAYER_H

