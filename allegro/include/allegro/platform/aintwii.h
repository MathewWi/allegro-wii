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
 *      Internal header for the Wii Allegro library.
 *
 *      By juvinious.
 *
 *      See readme.txt for copyright information.
 */


#ifndef AINTWII_H
#define AINTWII_H

#include "wiialleg.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _WII_INFO            	/* info about Nintendo Wii specific settings */
{
   int id;                          	/* integer ID */
   int setting;                  	/* set to allow autodetection */
   const char *info;                    /* the driver structure */
} _WII_INFO;

AL_ARRAY(_WII_INFO, _wii_info_list);

#ifdef __cplusplus
}
#endif

#endif
