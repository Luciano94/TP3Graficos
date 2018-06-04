#ifndef _DEBUG
	#define ALLEGRO_STATICLINK
#endif // !_DEBUG
#include "allegro5/allegro.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_audio.h"
#include "Player.h"
#include "Enemy.h"
#include "Definitions.h"
#include "Bullet.h"
#include <ctime>

/*constantes*/
const float FPS = 60;		//timer
const int cantEnemies = 5;	//cantidad de enemigos en pantalla

int main(int argc, char **argv) {

	ALLEGRO_DISPLAY *display = NULL;					 // pantalla
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;			 //cola de eventos
	ALLEGRO_TIMER *timer = NULL;						//timer del juego
	ALLEGRO_BITMAP* menu = NULL;
	ALLEGRO_SAMPLE* playerShot = NULL;					//sonido de disparo del player
	ALLEGRO_SAMPLE* enemyDeath = NULL;					//sonido muerte del enemigo
	bool gameStart = false;
	/*inicializo allegro*/
	if (!al_init()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	/*inicializo extencion para cargar imagenes*/
	if (!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	/*inicializo el timer*/
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize timer!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	/*inicializo el teclado*/
	if (!al_install_keyboard()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize keyboard!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	/*inicializo la ventana*/
	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_set_target_bitmap(al_get_backbuffer(display));
	/*inicializo cola de eventos*/
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize event queue!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return -1;
	}
	/*creo la imagen del menu*/
	menu = al_load_bitmap(MENU_FILE);
	if (!menu) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load menu!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	/*inicializo audio*/
	if (!al_install_audio()) {
		fprintf(stderr, "failed to initialize audio!\n");
		return -1;
	}
	if (!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return -1;
	}
	if (!al_reserve_samples(3)) {
		fprintf(stderr, "failed to reserve samples!\n");
		return -1;
	}

	playerShot = al_load_sample(SHOT_SOUND);

	if (!playerShot)
		printf("Audio clip sample not loaded!\n");
	
	enemyDeath = al_load_sample(ENEMY_DEATH);

	if (!enemyDeath)
		printf("Audio clip sample not loaded!\n");

	al_register_event_source(event_queue, al_get_display_event_source(display)); //agrego los eventos de ventana a la cola de eventos
	al_register_event_source(event_queue, al_get_timer_event_source(timer));	//agrego los eventos del timer a la cola de eventos
	al_register_event_source(event_queue, al_get_keyboard_event_source());		//agrego los eventos del teclado a la cola de eventos
	al_clear_to_color(al_map_rgb(0, 0, 0)); //pongo pantalla en negro
	al_flip_display();						//dibuja pantalla
	al_start_timer(timer);					//inicializo el timer
	
	/*Pantalla de titulo*/
	while (!gameStart) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//evento de cerrar ventana
			return 0;
		}
		if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_ENTER:
				gameStart = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				return 0;
				break;
			}
		}
		al_draw_bitmap(menu,0,0,0);
		al_flip_display();
	}
	/*Juego*/
	if (gameStart) {
		bool redraw = true;									 // controla el refresco de pantalla
		bool doexit = false;								 //controla el loop de la ventana
		Player* player;
		Enemy* enemy[cantEnemies];
		Bullet* bullet = NULL;
		bool shot = false;
		bool key[4] = { false, false, false, false };
		ALLEGRO_SAMPLE* music=NULL;
		music = al_load_sample(MUSIC_SOUND);

		if (!music)
			printf("Audio clip sample not loaded!\n");
		srand(time(0));
		/*creo elementos del juego*/
		player = new Player();
		player->setPosition(SCREEN_W / 2.0 - PLAYER_SIZE / 2.0, SCREEN_H - PLAYER_SIZE);
		/*Creacion de enemigos*/
		for (int i = 0; i < cantEnemies; i++)
			enemy[i] = new Enemy();
		for (int i = 0; i < cantEnemies; i++)
			enemy[i]->setPosition(rand() % (SCREEN_W - ENEMY_SIZE - 20 + 1), ENEMY_SIZE);
		/*game loop*/
		al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
		while (!doexit) {
			ALLEGRO_EVENT ev;								//variable para eventos
			al_wait_for_event(event_queue, &ev);			//espero que haya eventos en la cola
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//evento de cerrar ventana
				doexit = true;
			}
			if (ev.type == ALLEGRO_EVENT_TIMER) {
				player->move(key);
				redraw = true;
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = true;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					break;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = false;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = false;
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = false;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = false;
					break;

				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;

				case ALLEGRO_KEY_C:
					if (!shot) {
						bullet = player->shot(shot);
						al_play_sample(playerShot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
						break;
				}
			}
			if (redraw && al_is_event_queue_empty(event_queue)) {
				redraw = false;
				al_clear_to_color(al_map_rgb(0, 0, 0));	//se pone la pantalla en negro
				player->draw();							//dibuja player
				for (int i = 0; i < cantEnemies; i++)
					enemy[i]->draw();
				if (shot) {
					bullet->draw();
					bullet->update(shot);
				}
				al_flip_display();						//dibuja pantalla
			}
			/*Colisiones*/
			for (int i = 0; i < cantEnemies; i++) {
				if (shot && (bullet->collision(enemy[i]->getEnemyX(), enemy[i]->getEnemyY(), ENEMY_SIZE))) {
					enemy[i]->reset();
					al_play_sample(enemyDeath, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					delete bullet;
					shot = false;
				}
				if (player->collision(enemy[i]->getEnemyX(), enemy[i]->getEnemyY(), ENEMY_SIZE)) {
					player->life(doexit);
					enemy[i]->reset();
				}
			}
		}
		al_destroy_display(display);					//destruye la pantalla
		al_destroy_event_queue(event_queue);			//destruye cola de eventos
		al_destroy_timer(timer);						//destruyo el timer
		al_uninstall_keyboard();
		delete player;
		for (int i = 0; i < cantEnemies; i++)
			delete enemy[i];
		if(bullet) delete bullet;
	}
		return 0;
}