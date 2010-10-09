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
 *      By Arikado
 *
 *      See readme.txt for copyright information.
 */

#ifndef WII_DIGI_C
#define WII_DIGI_C

#include "allegro.h"
#include "allegro/internal/aintern.h"
#include "allegro/platform/aintwii.h"

#ifndef ALLEGRO_WII
#error Something is wrong with the makefile
#endif

static int wii_digi_detect(int input)
{
  return 0;
}

static int wii_digi_init(int input, int voices)
{
  return 0;
}

static void wii_digi_exit(int input)
{
  return;
}

static int wii_digi_set_mixer_volume(int volume)
{
  return 0;
}

static int wii_digi_get_mixer_volume()
{
  return 0;
}

static void wii_digi_init_voice(int voice, AL_CONST SAMPLE *sample)
{
  return;
}

static void wii_digi_release_voice(int voice)
{
  return;
}

static void wii_digi_start_voice(int voice)
{
  return;
}

static void wii_digi_stop_voice(int voice)
{
  return;
}

static void wii_digi_loop_voice(int voice, int playmode)
{
  return;
}

static int wii_digi_get_volume(int voice)
{
  return 0;
}

static void wii_digi_set_volume(int voice, int volume)
{
  return;
}

static void wii_digi_ramp_volume(int voice, int time, int endvol)
{
  return;
}

static void wii_digi_stop_volume_ramp(int voice)
{
  return;
}

static int wii_digi_get_frequency(int voice)
{
  return 0;
}

static void wii_digi_set_frequency(int voice, int frequency)
{
  return;
}

static void wii_digi_sweep_frequency(int voice, int time, int endfreq)
{
  return;
}

static void wii_digi_stop_frequency_sweep(int voice)
{
  return;
}

static int wii_digi_get_pan(int voice)
{
  return 0;
}

static void wii_digi_set_pan(int voice, int pan)
{
  return;
}

static void wii_digi_sweep_pan(int voice, int time, int endpan)
{
  return;
}

static void wii_digi_stop_pan_sweep(int voice)
{
  return;
}

static int wii_digi_rec_cap_rate(int bits, int stereo)
{
  return 0;
}

static int wii_digi_rec_cap_parm(int rate, int bits, int stereo)
{
  return 0;
}

static int wii_digi_rec_source(int source)
{
  return 0;
}

static int wii_digi_rec_start(int rate, int bits, int stereo)
{
  return 0;
}

static void wii_digi_rec_stop()
{
  return;
}

static int wii_digi_rec_read(void *buf)
{
  return 0;
}



DIGI_DRIVER digi_wii =
{
   DIGI_WII,            /* int  id; */                      /* driver ID code */
   empty_string,         /* AL_CONST char *name; */          /* driver name */
   empty_string,         /* AL_CONST char *desc; */          /* description string */
   "WII DIGI",            /* AL_CONST char *ascii_name; */    /* ASCII format name string */
   8,                  /* int  voices; */                  /* available voices */
   0,                  /* int  basevoice; */               /* voice number offset */
   8,                  /* int  max_voices; */              /* maximum voices we can support */ /* Half because of stereo */
   0,                  /* int  def_voices; */              /* default number of voices to use */
   wii_digi_detect,      /* AL_METHOD(int,  detect, (int input)); */
   wii_digi_init,         /* AL_METHOD(int,  init, (int input, int voices)); */
   wii_digi_exit,         /* AL_METHOD(void, exit, (int input)); */
   wii_digi_set_mixer_volume,   /* AL_METHOD(int,  set_mixer_volume, (int volume)); */
   wii_digi_get_mixer_volume,   /* AL_METHOD(int,  get_mixer_volume, (void)); */
   NULL,               /* AL_METHOD(void *, lock_voice, (int voice, int start, int end)); */
   NULL,               /* AL_METHOD(void, unlock_voice, (int voice)); */
   NULL,               /* AL_METHOD(int,  buffer_size, (void)); */
   wii_digi_init_voice,   /* AL_METHOD(void, init_voice, (int voice, AL_CONST SAMPLE *sample)); */
   wii_digi_release_voice,   /* AL_METHOD(void, release_voice, (int voice)); */
   wii_digi_start_voice,   /* AL_METHOD(void, start_voice, (int voice)); */
   wii_digi_stop_voice,   /* AL_METHOD(void, stop_voice, (int voice)); */
   wii_digi_loop_voice,   /* AL_METHOD(void, loop_voice, (int voice, int playmode)); */
   NULL,               /* AL_METHOD(int,  get_position, (int voice)); */
   NULL,               /* AL_METHOD(void, set_position, (int voice, int position)); */
   wii_digi_get_volume,   /* AL_METHOD(int,  get_volume, (int voice)); */
   wii_digi_set_volume,   /* AL_METHOD(void, set_volume, (int voice, int volume)); */
   wii_digi_ramp_volume,   /* AL_METHOD(void, ramp_volume, (int voice, int time, int endvol)); */
   wii_digi_stop_volume_ramp,   /* AL_METHOD(void, stop_volume_ramp, (int voice)); */
   wii_digi_get_frequency,   /* AL_METHOD(int,  get_frequency, (int voice)); */
   wii_digi_set_frequency,   /* AL_METHOD(void, set_frequency, (int voice, int frequency)); */
   wii_digi_sweep_frequency,/* AL_METHOD(void, sweep_frequency, (int voice, int time, int endfreq)); */
   wii_digi_stop_frequency_sweep,   /* AL_METHOD(void, stop_frequency_sweep, (int voice)); */
   wii_digi_get_pan,      /* AL_METHOD(int,  get_pan, (int voice)); */
   wii_digi_set_pan,      /* AL_METHOD(void, set_pan, (int voice, int pan)); */
   wii_digi_sweep_pan,      /* AL_METHOD(void, sweep_pan, (int voice, int time, int endpan)); */
   wii_digi_stop_pan_sweep,/* AL_METHOD(void, stop_pan_sweep, (int voice)); */
   NULL,               /* AL_METHOD(void, set_echo, (int voice, int strength, int delay)); */
   NULL,               /* AL_METHOD(void, set_tremolo, (int voice, int rate, int depth)); */
   NULL,               /* AL_METHOD(void, set_vibrato, (int voice, int rate, int depth)); */
   0,                  /* int rec_cap_bits; */
   0,                  /* int rec_cap_stereo; */
   wii_digi_rec_cap_rate,   /* AL_METHOD(int,  rec_cap_rate, (int bits, int stereo)); */
   wii_digi_rec_cap_parm,   /* AL_METHOD(int,  rec_cap_parm, (int rate, int bits, int stereo)); */
   wii_digi_rec_source,   /* AL_METHOD(int,  rec_source, (int source)); */
   wii_digi_rec_start,      /* AL_METHOD(int,  rec_start, (int rate, int bits, int stereo)); */
   wii_digi_rec_stop,      /* AL_METHOD(void, rec_stop, (void)); */
   wii_digi_rec_read,      /* AL_METHOD(int,  rec_read, (void *buf)); */
};

BEGIN_DIGI_DRIVER_LIST
   { DIGI_WII,         &digi_wii,         TRUE  },
END_DIGI_DRIVER_LIST

#endif
