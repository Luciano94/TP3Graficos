#ifndef DEFINITIONS_H
#define DEFINITIONS_H
//Game
#define SCREEN_W  640	//ancho de pantalla
#define SCREEN_H  480	//largo de pantalla
//personaje
#define PLAYER_SIZE  32	//tamanio del personaje
#define PLAYER_SPEED 6	//velocidad del jugador
#define PLAYER_SPRITE "player.png" //ruta de imagen del jugador
#define PLAYER_LIVES 3
//Enemigo
#define ENEMY_SIZE 32
#define ENEMY_SPEED 4
#define ENEMY_SPRITE "enemy.png"
//Bullet
#define BULLET_SIZE 32
#define BULLET_SPEED 8
#define BULLET_SPRITE "player.png"
//teclas
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
#endif
