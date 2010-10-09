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
 *      Configuration defines for use with the Nintendo Wii.
 *
 *      By Arikado.
 *
 *      See readme.txt for copyright information.
 */

#ifndef SCAN_DEPEND
   #include <stdio.h>
   #include <stdlib.h>
   #include <fcntl.h>
   #include <unistd.h>
   #include <string.h>                     /* strcpy/memset        */
#endif


/* a static auto config */
#define ALLEGRO_HAVE_INTTYPES_H		/* TODO: check this */
#define ALLEGRO_HAVE_STDINT_H		/* TODO: check this */
#define ALLEGRO_HAVE_STRICMP
#define ALLEGRO_HAVE_STRLWR
#define ALLEGRO_HAVE_STRUPR
#define ALLEGRO_HAVE_MEMCMP
#define ALLEGRO_HAVE_MKSTEMP
#define ALLEGRO_HAVE_UNISTD_H
#define ALLEGRO_HAVE_FCNTL_H
#define ALLEGRO_HAVE_LIMITS_H
#define ALLEGRO_HAVE_DIRENT_H
#define ALLEGRO_HAVE_SYS_DIR_H
#define ALLEGRO_HAVE_SYS_UTSNAME_H
#define ALLEGRO_HAVE_SYS_TIME_H
#define ALLEGRO_TIME_WITH_SYS_TIME

/* describe this platform */
#define ALLEGRO_PLATFORM_STR  "Wii"
#define ALLEGRO_BIG_ENDIAN
/*#define ALLEGRO_CONSOLE_OK*/
#define ALLEGRO_USE_SCHED_YIELD
#define ALLEGRO_USE_CONSTRUCTOR
#undef ALLEGRO_MULTITHREADED  /* FIXME */

/* Exclude ASM */

#ifndef ALLEGRO_NO_ASM
	#define ALLEGRO_NO_ASM
#endif

/* arrange for other headers to be included later on */
#define ALLEGRO_EXTRA_HEADER     "allegro/platform/alwii.h"
#define ALLEGRO_INTERNAL_HEADER  "allegro/platform/aintwii.h"

/* Provide implementations of missing definitions */
#define O_BINARY     0
#define dup(X)	fcntl (X, F_DUPFD, 0)
