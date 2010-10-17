/*         ______   ___    ___
 *        /\  _  \ /\_ \  /\_ \
 *        \ \ \L\ \\//\ \ \//\ \      __     __   _ __   ___
 *         \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\
 *          \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \L\ \ \ \//\ \L\ \
 *           \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/
 *            \/_/\/_/\/____/\/____/\/____/\/___L\ \/_/ \/___/
 *                                           /\____/
 *                                           \_/__/
 *
 *      List of Wii drivers.
 *
 *      By Arikado.
 *
 *      See readme.txt for copyright information.
 */


#include "allegro.h"
#include "allegro/internal/aintern.h"
#include "allegro/platform/aintwii.h"
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

extern bool installed_mouse;
extern bool installed_joystick;

#ifndef ALLEGRO_WII
#error Something is wrong with the makefile
#endif

ir_t wii_mouse_data;

static int wii_wiimouse_init()
{
	WPAD_Init();
	WPAD_SetDataFormat(0, WPAD_FMT_BTNS_ACC_IR);
	WPAD_SetVRes(0, 640, 480);
	WPAD_SetIdleTimeout(200);
  installed_mouse=true;
  return 2;
}

static void wii_wiimouse_exit()
{
  installed_mouse=false;
  if (!installed_joystick)
  {
    WPAD_Shutdown();
  }
  return;
}

static void wii_wiimouse_poll()
{
  WPAD_ScanPads();
  WPAD_IR(0, &wii_mouse_data);
  _mouse_x=wii_mouse_data.x;
  _mouse_y=wii_mouse_data.y;
  _mouse_z+=(WPAD_ButtonsHeld(0) & WPAD_BUTTON_UP)?1:0;
  _mouse_z-=(WPAD_ButtonsHeld(0) & WPAD_BUTTON_DOWN)?1:0;
  _mouse_w+=(WPAD_ButtonsHeld(0) & WPAD_BUTTON_RIGHT)?1:0;
  _mouse_w-=(WPAD_ButtonsHeld(0) & WPAD_BUTTON_LEFT)?1:0;

  _mouse_b=(WPAD_ButtonsHeld(0) & WPAD_BUTTON_A)?1:0;
  _mouse_b+=(WPAD_ButtonsHeld(0) & WPAD_BUTTON_B)?2:0;
  _mouse_b+=((WPAD_ButtonsHeld(0) & WPAD_BUTTON_MINUS)||(WPAD_ButtonsHeld(0) & WPAD_BUTTON_PLUS))?4:0;

  return;
}

static void wii_wiimouse_set_coord(int x, int y)
{
  _mouse_x = x;
  _mouse_x = y;
  return;
}

static void wii_wiimouse_get_coord(int *mickeyx, int *mickeyy)
{
  *mickeyx = _mouse_x;
  *mickeyy = _mouse_y;
  return;
}


MOUSE_DRIVER mouse_wii =
{
	MOUSE_WII,				/* int  id; */
	empty_string,			/* AL_CONST char *name; */
	empty_string,			/* AL_CONST char *desc; */
	"Nintendo Wiimote",			/* AL_CONST char *ascii_name; */
	wii_wiimouse_init,			/* AL_METHOD(int,  init, (void)); */
	wii_wiimouse_exit,			/* AL_METHOD(void, exit, (void)); */
	wii_wiimouse_poll,			/* AL_METHOD(void, poll, (void)); */
	NULL,					/* AL_METHOD(void, timer_poll, (void)); */
	wii_wiimouse_set_coord,		/* AL_METHOD(void, position, (int x, int y)); */
	NULL,					/* AL_METHOD(void, set_range, (int x1, int y_1, int x2, int y2)); */
	NULL,					/* AL_METHOD(void, set_speed, (int xspeed, int yspeed)); */
	wii_wiimouse_get_coord,		/* AL_METHOD(void, get_mickeys, (int *mickeyx, int *mickeyy)); */
	NULL,					/* AL_METHOD(int,  analyse_data, (AL_CONST char *buffer, int size)); */
	NULL,					/* AL_METHOD(void, enable_hardware_cursor, (int mode)); */
	NULL,					/* AL_METHOD(int,  select_system_cursor, (int cursor)); */
};

_DRIVER_INFO _mouse_driver_list[] =
{
   { MOUSE_WII,         &mouse_wii,         TRUE  },
   { MOUSEDRV_NONE,     &mousedrv_none,     FALSE }
};