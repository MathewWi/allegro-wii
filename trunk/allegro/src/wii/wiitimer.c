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

static int wii_timer_init()
{
  return 0;
}

static void wii_timer_exit()
{
  return;
}

static void wii_timer_rest(unsigned int time, AL_METHOD(void, callback, (void)))
{
  return;
}


TIMER_DRIVER timer_wii =
{
	TIMER_WII,				/* int  id; */
	empty_string,			/* AL_CONST char *name; */
	empty_string,			/* AL_CONST char *desc; */
	"Nintendo Wii Timer",	/* AL_CONST char *ascii_name; */
	wii_timer_init,			/* AL_METHOD(int,  init, (void)); */
	wii_timer_exit,			/* AL_METHOD(void, exit, (void)); */
	NULL,					/* AL_METHOD(int,  install_int, (AL_METHOD(void, proc, (void)), long speed)); */
	NULL,					/* AL_METHOD(void, remove_int, (AL_METHOD(void, proc, (void)))); */
	NULL,					/* AL_METHOD(int,  install_param_int, (AL_METHOD(void, proc, (void *param)), void *param, long speed)); */
	NULL,					/* AL_METHOD(void, remove_param_int, (AL_METHOD(void, proc, (void *param)), void *param)); */
	NULL,					/* AL_METHOD(int,  can_simulate_retrace, (void)); */
	NULL,					/* AL_METHOD(void, simulate_retrace, (int enable)); */
 	wii_timer_rest,			/* AL_METHOD(void, rest, (unsigned int tyme, AL_METHOD(void, callback, (void)))); */
};

_DRIVER_INFO _timer_driver_list[] =
{
   { TIMER_WII, &timer_wii, TRUE  },
   { 0,         NULL,       FALSE }
};
