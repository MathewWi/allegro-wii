#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

  if (allegro_init() != 0)
    return 1;

  /* set up the wiimote */
  install_mouse(); 

  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	allegro_message("\x1b[10;0H");
	allegro_message("Hello World!");


	// Wait for user to press A button on Wiimote (the left mouse button)
  while(!(mouse_b&1))
  {
    poll_mouse();
		//poll_joystick();
	  allegro_message("\x1b[15;0H");
  	allegro_message("Position:  %d, %d, %d, %d  (%d)   ", mouse_x, mouse_y, mouse_z, mouse_w, mouse_b);
	}
  exit(0);
  allegro_exit();
	return 0;
}

END_OF_MAIN()