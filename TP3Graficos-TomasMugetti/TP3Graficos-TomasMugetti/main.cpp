#ifndef _DEBUG
	#define ALLEGRO_STATICLINK
#endif // !_DEBUG
#include "allegro5/allegro.h"
#include "allegro5/allegro_native_dialog.h"

/*constantes*/
const int SCREEN_W = 640;	//ancho de pantalla
const int SCREEN_H = 480;	//largo de pantalla

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display = NULL;					// pantalla
	bool redraw = true;									// controla el refresco de pantalla
	bool doexit = false;								//controla el loop de la ventana
	/*inicializo allegro*/
	if (!al_init()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
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
	while (!doexit){								//mientras doexit no cambie la ventana no se cierra
		if (redraw) {								//mientras redraw sea true la ventana se refresca
			al_clear_to_color(al_map_rgb(0, 0, 0));	//se pone la pantalla en negro
			al_flip_display();						//dibuja pantalla
		}
	}
	al_destroy_display(display);					//destruye la pantalla
	return 0;
}