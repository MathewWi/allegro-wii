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

#ifndef ALLEGRO_WII
#error Something is wrong with the makefile
#endif

static int wii_kbd_init()
{
  return 0;
}

static void wii_kbd_exit()
{
  return;
}


KEYBOARD_DRIVER keyboard_wii =
{
	KEYBOARD_WII,			/* int  id */
	empty_string,			/* AL_CONST char *name; */
	empty_string,			/* AL_CONST char *desc; */
	"Wii Keyboard",			/* AL_CONST char *ascii_name; */
	0,						/* int autorepeat; */
	wii_kbd_init,			/* AL_METHOD(int,  init, (void)); */
	wii_kbd_exit,			/* AL_METHOD(void, exit, (void)); */
	NULL,					/* AL_METHOD(void, poll, (void)); */
	NULL,					/* AL_METHOD(void, set_leds, (int leds)); */
	NULL,					/* AL_METHOD(void, set_rate, (int delay, int rate)); */
	NULL,					/* AL_METHOD(void, wait_for_input, (void)); */
	NULL,					/* AL_METHOD(void, stop_waiting_for_input, (void)); */
	NULL,					/* AL_METHOD(int,  scancode_to_ascii, (int scancode)); */
	NULL,					/* AL_METHOD(AL_CONST char *, scancode_to_name, (int scancode)); */
};

/* KEYBOARD DRIVER LIST */

_DRIVER_INFO _keyboard_driver_list[] =
{
   { KEYBOARD_WII,      &keyboard_wii,      TRUE  },
   { SYSTEM_NONE,                 NULL,               FALSE     }
};
