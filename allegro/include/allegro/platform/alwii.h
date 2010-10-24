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
 *      Wii specific driver definitions.
 *
 *      By Arikado.
 *
 *      See readme.txt for copyright information.
 */


/* magic to capture name of executable file */

#undef END_OF_MAIN
#define END_OF_MAIN()

/* System driver */
#define SYSTEM_WII            AL_ID('N','W','S','Y')
AL_VAR(SYSTEM_DRIVER, system_wii);


/* Timer driver */
#define TIMER_WII	      AL_ID('N','W','T','M')
AL_VAR(TIMER_DRIVER, timer_wii);

/* Keyboard driver */
#define KEYBOARD_WII          AL_ID('N','W','K','Y')
AL_VAR(KEYBOARD_DRIVER, keyboard_wii);


/* Mouse driver */
#define MOUSE_WII             AL_ID('N','W','M','S')
AL_VAR(MOUSE_DRIVER, mouse_wii);

/* Joystick driver */
#define JOYSTICK_WII          AL_ID('N','W','J','Y')
AL_VAR(JOYSTICK_DRIVER, joystick_wii);

/* Graphics drivers */
#define GFX_WII                AL_ID('N','W','G','X')
AL_VAR(GFX_DRIVER, gfx_wii);

/* Sound driver */
#define DIGI_WII             AL_ID('N','W','D','G')
AL_VAR(DIGI_DRIVER, digi_wii);


/* MIDI driver */
#define MIDI_WII             AL_ID('N','W','M','D')
AL_VAR(MIDI_DRIVER, midi_wii);

#ifdef __cplusplus
extern "C" {
#endif

/* Setters getters for specific items for Nintendo Wii settings */

AL_FUNC(void, al_wii_set, (int option, int value));
AL_FUNC(int,  al_wii_get, (int option));
AL_FUNC(AL_CONST char *,  al_wii_get_info, (int option));

#ifdef __cplusplus
}
#endif
