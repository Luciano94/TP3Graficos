#ifndef _DEBUG
	#define ALLEGRO_STATICLINK
#endif // !_DEBUG
#include "allegro5/allegro.h"
#include "allegro5/allegro_native_dialog.h"
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
	bool redraw = true;									 // controla el refresco de pantalla
	bool doexit = false;								 //controla el loop de la ventana
	Player* player;
	Enemy* enemy[cantEnemies];
	Bullet* bullet=NULL;
	bool shot = false;
	bool key[4] = { false, false, false, false };
	srand(time(0));
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
	
	al_register_event_source(event_queue, al_get_display_event_source(display)); //inicializo eventos de ventana
	al_register_event_source(event_queue, al_get_timer_event_source(timer));	//inicializo eventos del timer
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0)); //pongo pantalla en negro
	al_flip_display();						//dibuja pantalla
	al_start_timer(timer);					//inicializo el timer
	
	/*creo elementos del juego*/
	player = new Player();
	player->setPosition(SCREEN_W / 2.0 - PLAYER_SIZE / 2.0, SCREEN_H - PLAYER_SIZE);
	/*Creacion de enemigos*/
	for (int i = 0; i < cantEnemies; i++)
		enemy[i] = new Enemy();
	for (int i = 0; i < cantEnemies; i++)
		enemy[i]->setPosition(rand() % (SCREEN_W - ENEMY_SIZE - 20 + 1),ENEMY_SIZE);
	/*game loop*/
	while (!doexit){
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
				if(!shot)
					bullet = player->shot(shot);
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
	}
	al_destroy_display(display);					//destruye la pantalla
	al_destroy_event_queue(event_queue);			//destruye cola de eventos
	al_destroy_timer(timer);						//destruyo el timer
	al_uninstall_keyboard();
	delete player;
	//delete[] enemy;
	return 0;
}