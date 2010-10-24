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

keyboard_event ke;
s32 res;

/*
typedef struct kbd_cond
{
  u8 modifiers;
  u8 leds;
  u8 keys[6];
} kbd_cond_t;
*/
typedef struct kbd_state
{
  u8 modifiers;
  u8 leds;
  u8 matrix[256];
  int shift_keys;
} kbd_state_t;

static int  wii_keyboard_init(void);
static void wii_keyboard_exit(void);
static void wii_keyboard_poll(void);
//static void wii_keyboard_wait_for_input(void);
//static void wii_keyboard_stop_waiting_for_input(void);


KEYBOARD_DRIVER keyboard_wii =
{
  KEYBOARD_WII,
  empty_string,
  empty_string,
  "Wii USB Keyboard",
  TRUE,
  wii_keyboard_init,
  wii_keyboard_exit,
  wii_keyboard_poll,
  NULL,   // AL_METHOD(void, set_leds, (int leds));
  NULL,   // AL_METHOD(void, set_rate, (int delay, int rate));
  NULL, //wii_keyboard_wait_for_input,
  NULL, //wii_keyboard_stop_waiting_for_input,
  _pckey_scancode_to_ascii,
  _pckey_scancode_to_name
};

static kbd_state_t wii_keyboard_current_state, wii_keyboard_old_state;

const static unsigned char wii_keyboard_key[]=
{
  0, 0, 0, 0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
  'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y', 'z',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  '\n', 0x1b, 0x8, '\t', ' ', '-', '=', '{', 
  '}', '\\' , 0, ';', '\'',
  '~', ',', '`', '/', 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, '/', '*', '-', '+', '\n', 
  '1', '2', '3', '4', '5', '6',
  '7', '8', '9', '0', 0, 0 
};

const static unsigned char wii_keyboard_code[]=
{
  0, 0, 0, 0, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I ,
  KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
  KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
  KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
  KEY_ENTER, KEY_ESC, KEY_BACKSPACE, KEY_TAB, KEY_SPACE, KEY_MINUS, KEY_EQUALS, KEY_OPENBRACE, 
  KEY_CLOSEBRACE, KEY_BACKSLASH , 0, KEY_SEMICOLON, KEY_QUOTE,
  '~', KEY_COMMA, KEY_TILDE, KEY_SLASH, KEY_CAPSLOCK, 
  KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12,
  KEY_PRTSCR, KEY_SCRLOCK, KEY_PAUSE, KEY_INSERT, KEY_HOME, KEY_PGUP, KEY_DEL, KEY_END, KEY_PGDN, KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP,
  KEY_NUMLOCK, KEY_SLASH_PAD, KEY_ASTERISK, KEY_MINUS_PAD, KEY_PLUS_PAD, KEY_ENTER_PAD, 
  KEY_1_PAD, KEY_2_PAD, KEY_3_PAD, KEY_4_PAD, KEY_5_PAD, KEY_6_PAD,
  KEY_7_PAD, KEY_8_PAD, KEY_9_PAD, KEY_0_PAD, KEY_DEL_PAD, 0 
};


const static unsigned char wii_keyboard_shift_code[] =
{
  KEY_LCONTROL,KEY_LSHIFT,KEY_ALT,0 /* S1 */,
  KEY_RCONTROL,KEY_RSHIFT,KEY_ALTGR,0 /* S2 */,
};

const static unsigned char wii_keyboard_shift[] =
{
  KB_CTRL_FLAG,KB_SHIFT_FLAG,KB_ALT_FLAG,0,
  KB_CTRL_FLAG,KB_SHIFT_FLAG,KB_ALT_FLAG,0,
};


static void wii_keyboard_handler_key(int pressed, int code)
{
  int scancode=wii_keyboard_code[code];
  if (pressed)
  {
    _handle_key_press(wii_keyboard_key[code], scancode);
    key[scancode]=1;
  }
  else
  {
    _handle_key_release(scancode);
    key[scancode]=0;
  }
}

static void wii_keyboard_handler_shift(int pressed, int code)
{
  int scancode=wii_keyboard_shift[code];
  if (pressed)
  {
    key[scancode]=1;
    _key_shifts|=wii_keyboard_shift[code];
  }
  else
  {
    key[scancode]=0;
    _key_shifts&=~wii_keyboard_shift[code];
  }
}


static void wii_keyboard_poll(void)
{
  //kbd_state_t	*state;
  int	i, shiftkeys;

/*
typedef struct kbd_state
{
  u8 modifiers;
  u8 leds;
  u8 matrix[256];
  int shift_keys;
} kbd_state_t;
*/

  res = KEYBOARD_GetEvent(&ke);
  if (!res)
  {
    return;
  }
  else
  {
    if ((ke.type == KEYBOARD_PRESSED)||(ke.type == KEYBOARD_RELEASED))
    {
      wii_keyboard_current_state.matrix[ke.keycode]=(ke.type == KEYBOARD_PRESSED)?1:0;
      // fill in shift keys
      shiftkeys = wii_keyboard_current_state.shift_keys ^ wii_keyboard_old_state.shift_keys;
      for(i=0;i<sizeof(wii_keyboard_shift);i++)
      {
        if ((shiftkeys>>i)&1)
        {
          wii_keyboard_handler_shift(((wii_keyboard_current_state.shift_keys>>i)&1),i);
        }
      }

      for(i=0;i<sizeof(wii_keyboard_key);i++)
      {
        if (wii_keyboard_current_state.matrix[i]!=wii_keyboard_old_state.matrix[i])
        {
          wii_keyboard_handler_key(wii_keyboard_current_state.matrix[i],i);
        }
      }
    }
  }

  wii_keyboard_old_state = wii_keyboard_current_state;
}

/*
static void wii_keyboard_wait_for_input(void)
{
  return;
}

static void wii_keyboard_stop_waiting_for_input(void)
{
  return;
}
*/

static int wii_keyboard_init(void)
{
  KEYBOARD_Init(NULL);
  _pckeys_init();
  memset(&wii_keyboard_current_state,0,sizeof(wii_keyboard_current_state));
  memset(&wii_keyboard_old_state,0,sizeof(wii_keyboard_old_state));
  //install_int(wii_keyboard_poll, 1000/120); //twice a second just to be sure
  return 0;
}


static void wii_keyboard_exit(void)
{
  return;
}


/* KEYBOARD DRIVER LIST */
_DRIVER_INFO _keyboard_driver_list[] =
{
  { KEYBOARD_WII,      &keyboard_wii,      TRUE  },
  { SYSTEM_NONE,                 NULL,               FALSE     }
};
