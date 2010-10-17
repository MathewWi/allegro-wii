#include <allegro.h>
#include <wiiuse/wpad.h>

extern u32 *xfb;

int main(int argc, char **argv)
{
  allegro_init();
  set_color_depth(32);
  int c=makecol32(0, 255, 255);
  set_gfx_mode(GFX_WII, 640, 480, 0, 0);

  install_mouse(); 
  
  int x, y;
  for(y=100; y<200; ++y)
  {
    for(x=100; x<200; ++x)
    {
      putpixel(screen, x, y, c);
    }
  }
    textout_ex(screen, font, "Hello world!", 200, 200, c, -1);
  
  while(!(mouse_b&1))
  {
    poll_mouse();
  }

  allegro_exit();
  return 0;
}
END_OF_MAIN()
