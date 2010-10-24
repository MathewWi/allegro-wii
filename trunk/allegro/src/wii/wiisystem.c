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

#include <malloc.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

u32 *xfb;
static GXRModeObj *rmode;
bool installed_mouse=false;
bool installed_joystick=false;

static int wii_sys_init()
{
  VIDEO_Init();
  WPAD_Init();
  WPAD_SetVRes(0, 640, 480);
  WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);

  rmode = VIDEO_GetPreferredMode(NULL);

  xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
  console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);

  VIDEO_Configure(rmode);
  VIDEO_SetNextFramebuffer(xfb);
  VIDEO_SetBlack(FALSE);
  VIDEO_Flush();
  VIDEO_WaitVSync();
  if(rmode->viTVMode&VI_NON_INTERLACE)
  {
    VIDEO_WaitVSync();
  }
  return 0;
}

static void wii_sys_exit()
{
  return;
}

static void wii_sys_message(AL_CONST char *msg)
{
  printf(msg);
  return;
}

static void wii_sys_assert(AL_CONST char *msg)
{
  return;
}

static void wii_sys_read_hardware_palette()
{
  return;
}

static void wii_sys_set_palette_range(AL_CONST struct RGB *p, int from, int to, int retracesync)
{
  return;
}

static int get_wii_resolution(int *width, int *height)
{
  return 0;
}

static void wii_get_safe_mode(int *driver, struct GFX_MODE *mode)
{
  return;
}

static void wii_sys_restore_console_state()
{
  return;
}

SYSTEM_DRIVER system_wii =
{
	SYSTEM_WII,						/* int  id; */
	empty_string,					/* AL_CONST char *name; */
	empty_string,					/* AL_CONST char *desc; */
	"Wii System", 					/* AL_CONST char *ascii_name; */
	wii_sys_init,					/* AL_METHOD(int, init, (void)); */
	wii_sys_exit,					/* AL_METHOD(void, exit, (void)); */
	NULL,							/*AL_METHOD(void, get_executable_name, (char *output, int size));*/

// do find_resource later, if needed.
	NULL,							/*AL_METHOD(int, find_resource, (char *dest, AL_CONST char *resource, int size));*/

	NULL,							/*AL_METHOD(void, set_window_title, (AL_CONST char *name));*/
	NULL,							/*AL_METHOD(int, set_close_button_callback, (AL_METHOD(void, proc, (void))));*/
	wii_sys_message,				/*AL_METHOD(void, message, (AL_CONST char *msg));*/
	wii_sys_assert,					/*AL_METHOD(void, assert, (AL_CONST char *msg));*/
	NULL,							/*AL_METHOD(void, save_console_state, (void));*/
	wii_sys_restore_console_state,	/*AL_METHOD(void, restore_console_state, (void));*/
	NULL,							/*AL_METHOD(struct BITMAP *, create_bitmap, (int color_depth, int width, int height));*/
	NULL,							/*AL_METHOD(void, created_bitmap, (struct BITMAP *bmp));*/
	NULL,							/*AL_METHOD(struct BITMAP *, create_sub_bitmap, (struct BITMAP *parent, int x, int y, int width, int height));*/
	NULL,							/*AL_METHOD(void, created_sub_bitmap, (struct BITMAP *bmp, struct BITMAP *parent));*/
	NULL,							/*AL_METHOD(int, destroy_bitmap, (struct BITMAP *bitmap));*/
	wii_sys_read_hardware_palette,	/*AL_METHOD(void, read_hardware_palette, (void));*/
	wii_sys_set_palette_range,		/*AL_METHOD(void, set_palette_range, (AL_CONST struct RGB *p, int from, int to, int retracesync));*/
	NULL,							/*AL_METHOD(struct GFX_VTABLE *, get_vtable, (int color_depth));*/
	NULL,							/*AL_METHOD(int, set_display_switch_mode, (int mode));*/
	NULL,							/*AL_METHOD(void, display_switch_lock, (int lock, int foreground));*/
	NULL,							/*AL_METHOD(int, desktop_color_depth, (void));*/

// not sure get_desktop_resolution should be used here...
	get_wii_resolution,				/*AL_METHOD(int, get_desktop_resolution, (int *width, int *height));*/

	wii_get_safe_mode,				/*AL_METHOD(void, get_gfx_safe_mode, (int *driver, struct GFX_MODE *mode));*/
	NULL,							/*AL_METHOD(void, yield_timeslice, (void));*/
	NULL,							/*AL_METHOD(void *, create_mutex, (void));*/
	NULL,							/*AL_METHOD(void, destroy_mutex, (void *handle));*/
	NULL,							/*AL_METHOD(void, lock_mutex, (void *handle));*/
	NULL,							/*AL_METHOD(void, unlock_mutex, (void *handle));*/
	NULL,							/*AL_METHOD(_DRIVER_INFO *, gfx_drivers, (void));*/
	NULL,							/*AL_METHOD(_DRIVER_INFO *, digi_drivers, (void));*/
	NULL,							/*AL_METHOD(_DRIVER_INFO *, midi_drivers, (void));*/
	NULL,							/*AL_METHOD(_DRIVER_INFO *, keyboard_drivers, (void));*/
	NULL,							/*AL_METHOD(_DRIVER_INFO *, mouse_drivers, (void));*/
	NULL,							/*AL_METHOD(_DRIVER_INFO *, joystick_drivers, (void));*/
	NULL,							/*AL_METHOD(_DRIVER_INFO *, timer_drivers, (void));*/
};

/* SYSTEM DRIVER LIST */

_DRIVER_INFO _system_driver_list[] =
{
   {SYSTEM_WII, &system_wii, TRUE},
   {SYSTEM_NONE, &system_none, FALSE},
   {0, NULL, 0}
};

