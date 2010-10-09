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
#include <gccore.h>
#include <wiiuse/wpad.h>

extern bool installed_mouse;
extern bool installed_joystick;

#ifndef ALLEGRO_WII
#error Something is wrong with the makefile
#endif

int numberOfAttachedControllers()
{
  // used to check how many controllers are attached
  int i, numAttached = 0;
  u32 type;  //find the type of the expansion

  for(i=0; i<WPAD_MAX_WIIMOTES; i++)
  {
    if (WPAD_Probe(i, &type) == WPAD_ERR_NONE)
    {
      numAttached++;
    }
  }
  return numAttached;
}

void waitForWiimote()
{
  while(numberOfAttachedControllers()<1)
  {
    allegro_message("\x1b[15;30HWaiting for wiimote");
  }
  return;
}

static int wii_joy_poll()
{
	WPAD_ScanPads();

  if (!num_joysticks)
    return -1;

  // just buttons for now, no analog sticks
  int i=0;
  for (i=0; i<num_joysticks; i++)
  {
    u32 held = WPAD_ButtonsHeld(i);
    
    // Wiimote
    joy[i].button[ 0].b = (held & WPAD_BUTTON_A);
    joy[i].button[ 1].b = (held & WPAD_BUTTON_B);
    joy[i].button[ 2].b = (held & WPAD_BUTTON_1);
    joy[i].button[ 3].b = (held & WPAD_BUTTON_2);
    joy[i].button[ 4].b = (held & WPAD_BUTTON_MINUS);
    joy[i].button[ 5].b = (held & WPAD_BUTTON_PLUS);
    joy[i].button[ 6].b = (held & WPAD_BUTTON_HOME);
    joy[i].button[ 7].b = (held & WPAD_BUTTON_UP);
    joy[i].button[ 8].b = (held & WPAD_BUTTON_DOWN);
    joy[i].button[ 9].b = (held & WPAD_BUTTON_LEFT);
    joy[i].button[10].b = (held & WPAD_BUTTON_RIGHT);
											
    // Nunchuck
    joy[i].button[11].b = (held & WPAD_NUNCHUK_BUTTON_C);
    joy[i].button[12].b = (held & WPAD_NUNCHUK_BUTTON_Z);

    // Classic Controller
    joy[i].button[13].b = (held & WPAD_CLASSIC_BUTTON_A);
    joy[i].button[14].b = (held & WPAD_CLASSIC_BUTTON_B);
    joy[i].button[15].b = (held & WPAD_CLASSIC_BUTTON_X);
    joy[i].button[16].b = (held & WPAD_CLASSIC_BUTTON_Y);
    joy[i].button[17].b = (held & WPAD_CLASSIC_BUTTON_FULL_L);
    joy[i].button[18].b = (held & WPAD_CLASSIC_BUTTON_FULL_R);
    joy[i].button[19].b = (held & WPAD_CLASSIC_BUTTON_ZL);
    joy[i].button[20].b = (held & WPAD_CLASSIC_BUTTON_ZR);
    joy[i].button[21].b = (held & WPAD_CLASSIC_BUTTON_MINUS);
    joy[i].button[22].b = (held & WPAD_CLASSIC_BUTTON_PLUS);
    joy[i].button[23].b = (held & WPAD_CLASSIC_BUTTON_HOME);
    joy[i].button[24].b = (held & WPAD_CLASSIC_BUTTON_UP);
    joy[i].button[25].b = (held & WPAD_CLASSIC_BUTTON_DOWN);
    joy[i].button[26].b = (held & WPAD_CLASSIC_BUTTON_LEFT);
    joy[i].button[27].b = (held & WPAD_CLASSIC_BUTTON_RIGHT);
  }

  return 0;
}

static int wii_joy_init()
{
  WPAD_Init();

  while (num_joysticks < 1)
  {
    num_joysticks = numberOfAttachedControllers();
  }

  int i=0;
  for (i=0; i<num_joysticks; i++)
  {
    joy[i].flags = JOYFLAG_ANALOGUE | JOYFLAG_SIGNED;

    joy[i].num_sticks = 5;

    // Wiimote Directional Pad
    joy[i].stick[0].flags = JOYFLAG_ANALOGUE | JOYFLAG_SIGNED;
    joy[i].stick[0].num_axis = 2;
    joy[i].stick[0].axis[0].name = get_config_text("Wiimote Directional Pad X");
    joy[i].stick[0].axis[1].name = get_config_text("Wiimote Directional Pad Y");
    joy[i].stick[0].name = get_config_text("Wiimote Directional Pad");

    // Nunchuck Stick
    joy[i].stick[1].flags = JOYFLAG_ANALOGUE | JOYFLAG_SIGNED;
    joy[i].stick[1].num_axis = 2;
    joy[i].stick[1].axis[0].name = get_config_text("Nunchuck Stick X");
    joy[i].stick[1].axis[1].name = get_config_text("Nunchuck Stick Y");
    joy[i].stick[1].name = get_config_text("Nunchuck Stick");

    // Classic Directional Pad
    joy[i].stick[2].flags = JOYFLAG_ANALOGUE | JOYFLAG_SIGNED;
    joy[i].stick[2].num_axis = 2;
    joy[i].stick[2].axis[0].name = get_config_text("Classic Directional Pad X");
    joy[i].stick[2].axis[1].name = get_config_text("Classic Directional Pad Y");
    joy[i].stick[2].name = get_config_text("Classic Directional Pad");

    // Classic Left Stick
    joy[i].stick[3].flags = JOYFLAG_ANALOGUE | JOYFLAG_SIGNED;
    joy[i].stick[3].num_axis = 2;
    joy[i].stick[3].axis[0].name = get_config_text("Classic Left Stick X");
    joy[i].stick[3].axis[1].name = get_config_text("Classic Left Stick Y");
    joy[i].stick[3].name = get_config_text("Classic Left Stick");

    // Classic Right Stick
    joy[i].stick[4].flags = JOYFLAG_ANALOGUE | JOYFLAG_SIGNED;
    joy[i].stick[4].num_axis = 2;
    joy[i].stick[4].axis[0].name = get_config_text("Classic Right Stick X");
    joy[i].stick[4].axis[1].name = get_config_text("Classic Right Stick Y");
    joy[i].stick[4].name = get_config_text("Classic Right Stick");


    joy[i].num_buttons = 28;

    // Wiimote
    joy[i].button[ 0].name = get_config_text("A");
    joy[i].button[ 1].name = get_config_text("B");
    joy[i].button[ 2].name = get_config_text("1");
    joy[i].button[ 3].name = get_config_text("2");
    joy[i].button[ 4].name = get_config_text("-");
    joy[i].button[ 5].name = get_config_text("+");
    joy[i].button[ 6].name = get_config_text("Home");
    joy[i].button[ 7].name = get_config_text("Up");
    joy[i].button[ 8].name = get_config_text("Down");
    joy[i].button[ 9].name = get_config_text("Left");
    joy[i].button[10].name = get_config_text("Right");
    // Nunchuck
    joy[i].button[11].name = get_config_text("C");
    joy[i].button[12].name = get_config_text("Z");
    // Classic Controller
    joy[i].button[13].name = get_config_text("a");
    joy[i].button[14].name = get_config_text("b");
    joy[i].button[15].name = get_config_text("x");
    joy[i].button[16].name = get_config_text("y");
    joy[i].button[17].name = get_config_text("L");
    joy[i].button[18].name = get_config_text("R");
    joy[i].button[19].name = get_config_text("ZL");
    joy[i].button[20].name = get_config_text("ZR");
    joy[i].button[21].name = get_config_text("Select");
    joy[i].button[22].name = get_config_text("Start");
    joy[i].button[23].name = get_config_text("Home");
    joy[i].button[24].name = get_config_text("Up");
    joy[i].button[25].name = get_config_text("Down");
    joy[i].button[26].name = get_config_text("Left");
    joy[i].button[27].name = get_config_text("Right");
  }

  installed_joystick=true;
  // Go ahead and poll once
  return wii_joy_poll();
}

static void wii_joy_exit()
{
  installed_joystick=false;
  if (!installed_mouse)
  {
    WPAD_Shutdown();
  }
  return;
}

static int wii_joy_save_data()
{
  return 0;
}

static int wii_joy_load_data()
{
  return 0;
}

static AL_CONST char *wii_joy_calibrate_name(int n)
{
  return NULL;
}

static int wii_joy_calibrate(int n)
{
  return 0;
}

JOYSTICK_DRIVER joystick_wii =
{
   JOYSTICK_WII,         /* int  id; */
   "Nintendo Wii Controller",         /* AL_CONST char *name; */
   "Nintendo Wii Controller",         /* AL_CONST char *desc; */
   "Nintendo Wii Controller",   /* AL_CONST char *ascii_name; */
   wii_joy_init,         /* AL_METHOD(int, init, (void)); */
   wii_joy_exit,         /* AL_METHOD(void, exit, (void)); */
   wii_joy_poll,         /* AL_METHOD(int, poll, (void)); */
   wii_joy_save_data,      /* AL_METHOD(int, save_data, (void)); */
   wii_joy_load_data,      /* AL_METHOD(int, load_data, (void)); */
   wii_joy_calibrate_name,   /* AL_METHOD(AL_CONST char *, calibrate_name, (int n)); */
   wii_joy_calibrate,      /* AL_METHOD(int, calibrate, (int n)); */
};

BEGIN_JOYSTICK_DRIVER_LIST
   { JOYSTICK_WII,         &joystick_wii,         TRUE  },
END_JOYSTICK_DRIVER_LIST

