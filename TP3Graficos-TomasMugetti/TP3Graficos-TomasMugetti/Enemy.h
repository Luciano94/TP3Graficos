#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "Definitions.h"
#include <ctime>
using namespace std;

class Enemy {
private:
	ALLEGRO_BITMAP* _enemy;
	int _enemyX;
	int _enemyY;

public:

	Enemy();
	~Enemy();
	void draw();
	void setPosition(int x, int y);
	int getEnemyX();
	int getEnemyY();
	void reset();
};
#endif // !PLAYER_H#pragma once
