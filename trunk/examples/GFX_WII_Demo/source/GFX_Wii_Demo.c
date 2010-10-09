#include <allegro.h>
#include <wiiuse/wpad.h>

int main(int argc, char **argv){

    allegro_init();
    set_color_depth(32);
    set_gfx_mode(GFX_WII, 640, 480, 0, 0);
    WPAD_Init();
    textout_ex(screen, font, "Hello World!", 1, 1, 10, -1);
    textout_ex(screen, font, "Press ESCape to quit!", 1, 12, 11, -1);
    while(true){
	WPAD_ScanPads();
	if(WPAD_ButtonsDown(0)&WPAD_BUTTON_HOME)
	break;
	}
    allegro_exit();
    return 0;
}
END_OF_MAIN()
