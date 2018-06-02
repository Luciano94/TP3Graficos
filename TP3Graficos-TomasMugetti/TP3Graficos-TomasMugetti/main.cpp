#ifndef _DEBUG
	#define ALLEGRO_STATICLINK
#endif // !_DEBUG
#include "allegro5/allegro.h"
#include "allegro5/allegro_native_dialog.h"
#include "Player.h"
/*constantes*/
const float FPS = 60;		//timer
const int SCREEN_W = 640;	//ancho de pantalla
const int SCREEN_H = 480;	//largo de pantalla
const int PLAYER_SIZE = 32;	//ancho del personaje

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display = NULL;					 // pantalla
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;			 //cola de eventos
	ALLEGRO_TIMER *timer = NULL;						//timer del juego
	bool redraw = true;									 // controla el refresco de pantalla
	bool doexit = false;								 //controla el loop de la ventana
	/*inicializo allegro*/
	if (!al_init()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
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
	al_clear_to_color(al_map_rgb(0, 0, 0)); //pongo pantalla en negro
	al_flip_display();						//dibuja pantalla
	al_start_timer(timer);					//inicializo el timer
	while (!doexit){			//windows loop
		ALLEGRO_EVENT ev;		//variable para eventos
		al_wait_for_event(event_queue, &ev);	//espero que haya eventos en la cola
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//evento de cerrar ventana
			return 0;
		}
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));	//se pone la pantalla en negro
			al_flip_display();						//dibuja pantalla
		}
	}
	al_destroy_display(display);					//destruye la pantalla
	al_destroy_event_queue(event_queue);			//destruye cola de eventos
	al_destroy_timer(timer);						//destruyo el timer
	return 0;
}