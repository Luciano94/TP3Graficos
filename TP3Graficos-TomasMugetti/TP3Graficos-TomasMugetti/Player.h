#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
using namespace std;
class Player {
private:
	ALLEGRO_BITMAP* _player;
	int _playerSize;
	int _playerX;
	int _playerY;
public:
	Player(char* spriteFile, int playerSize);
	~Player();
	void draw();
	void move();
	void shot();
	void imprimite();
	void setPosition(int x, int y);
};
#endif // !PLAYER_H

