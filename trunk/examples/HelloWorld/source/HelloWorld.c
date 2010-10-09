#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

  if (allegro_init() != 0)
    return 1;

  /* set up the wiimote */
  install_joystick(JOYSTICK_WII); 

  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	allegro_message("\x1b[10;0H");
	allegro_message("Hello World!");

  poll_joystick();
	// Wait for user to press A button on Wiimote
  while(!joy[0].button[ 0].b)
  {
		poll_joystick();
	}
  
  allegro_exit();
	return 0;
}

END_OF_MAIN()