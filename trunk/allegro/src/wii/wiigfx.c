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

#ifndef ALLEGRO_WII
#error Something is wrong with the makefile
#endif



static char *screen_surf;
#define RENDER_DELAY (1000/60)  /* 60 Hz */

BITMAP* afb; //Allegro framebuffer

//8-bit 332 RGB: rrrgggbb
//16-bit: rrrrrggggggbbbbb
//15-bit: 0rrrrrgggggbbbbb
//24-bit: rrrrrrrrggggggggbbbbbbbb
//32-bit: aaaaaaaarrrrrrrrggggggggbbbbbbbb

/****************************************************************************
* CvtRGB
*
* This function simply returns two RGB pixels as one Y1CbY2Cr.
*****************************************************************************/
u32 CvtRGB (u8 r1, u8 g1, u8 b1, u8 r2, u8 g2, u8 b2)
{
  int y1, cb1, cr1, y2, cb2, cr2, cb, cr;
 
  y1 = (299 * r1 + 587 * g1 + 114 * b1) / 1000;
  cb1 = (-16874 * r1 - 33126 * g1 + 50000 * b1 + 12800000) / 100000;
  cr1 = (50000 * r1 - 41869 * g1 - 8131 * b1 + 12800000) / 100000;
 
  y2 = (299 * r2 + 587 * g2 + 114 * b2) / 1000;
  cb2 = (-16874 * r2 - 33126 * g2 + 50000 * b2 + 12800000) / 100000;
  cr2 = (50000 * r2 - 41869 * g2 - 8131 * b2 + 12800000) / 100000;
 
  cb = (cb1 + cb2) >> 1;
  cr = (cr1 + cr2) >> 1;
 
  return (y1 << 24) | (cb << 16) | (y2 << 8) | cr;
}
//copies the Allegro framebuffer (in 8-bit color) to the GX framebuffer
void copy_8bit_afb_to_xfb()
{
  int i=0, x, y, c1, c2;
  //u16 *afb2 = (u16 *)screen_surf;

  //short *wfb = (short *)xfb;

  for(y=0;y<480;++y)
  {
    for(x=0;x<320;++x)
    {
      c1=getpixel(screen, 2*x, y);
      c2=getpixel(screen, 2*x+1, y);
      xfb[i++]=CvtRGB (getr8(c1), getg8(c1), getb8(c1), getr8(c2), getg8(c2), getb8(c2));
//      xfb[i++]=CvtRGB (getr8(screen->line[y][x*2]), getg8(screen->line[y][x*2]), getb8(screen->line[y][x*2]), getr8(screen->line[y][x*2+1]), getg8(screen->line[y][x*2+1]), getb8(screen->line[y][x*2+1]));
    }
  }
}

//copies the Allegro framebuffer (in 15-bit color) to the GX framebuffer
void copy_15bit_afb_to_xfb()
{
  int i=0, x, y, c1, c2;
  //u16 *afb2 = (u16 *)screen_surf;

  //short *wfb = (short *)xfb;

  for(y=0;y<480;++y)
  {
    for(x=0;x<320;++x)
    {
      c1=getpixel(screen, 2*x, y);
      c2=getpixel(screen, 2*x+1, y);
      xfb[i++]=CvtRGB (getr15(c1), getg15(c1), getb15(c1), getr15(c2), getg15(c2), getb15(c2));
//      xfb[i++]=CvtRGB (getr15(screen->line[y][x*2]), getg15(screen->line[y][x*2]), getb15(screen->line[y][x*2]), getr15(screen->line[y][x*2+1]), getg15(screen->line[y][x*2+1]), getb15(screen->line[y][x*2+1]));
    }
  }
}

//copies the Allegro framebuffer (in 16-bit color) to the GX framebuffer
void copy_16bit_afb_to_xfb()
{
  int i=0, x, y, c1, c2;
  //u16 *afb2 = (u16 *)screen_surf;

  //short *wfb = (short *)xfb;

  for(y=0;y<480;++y)
  {
    for(x=0;x<320;++x)
    {
      c1=getpixel(screen, 2*x, y);
      c2=getpixel(screen, 2*x+1, y);
      xfb[i++]=CvtRGB (getr16(c1), getg16(c1), getb16(c1), getr16(c2), getg16(c2), getb16(c2));
//      xfb[i++]=CvtRGB (getr16(screen->line[y][x*2]), getg16(screen->line[y][x*2]), getb16(screen->line[y][x*2]), getr16(screen->line[y][x*2+1]), getg16(screen->line[y][x*2+1]), getb16(screen->line[y][x*2+1]));
    }
  }
}

//copies the Allegro framebuffer (in 24-bit color) to the GX framebuffer
void copy_24bit_afb_to_xfb()
{
  int i=0, x, y, c1, c2;
  //u16 *afb2 = (u16 *)screen_surf;

  //short *wfb = (short *)xfb;

  for(y=0;y<480;++y)
  {
    for(x=0;x<320;++x)
    {
      c1=getpixel(screen, 2*x, y);
      c2=getpixel(screen, 2*x+1, y);
      xfb[i++]=CvtRGB (getr24(c1), getg24(c1), getb24(c1), getr24(c2), getg24(c2), getb24(c2));
//      xfb[i++]=CvtRGB (getr24(screen->line[y][x*2]), getg24(screen->line[y][x*2]), getb24(screen->line[y][x*2]), getr24(screen->line[y][x*2+1]), getg24(screen->line[y][x*2+1]), getb24(screen->line[y][x*2+1]));
    }
  }
}

//copies the Allegro framebuffer (in 32-bit color) to the GX framebuffer
void copy_32bit_afb_to_xfb()
{
  int i=0, x, y, c1, c2;
  //u16 *afb2 = (u16 *)screen_surf;

  //short *wfb = (short *)xfb;

  for(y=0;y<480;++y)
  {
    for(x=0;x<320;++x)
    {
      c1=getpixel(screen, 2*x, y);
      c2=getpixel(screen, 2*x+1, y);
      xfb[i++]=CvtRGB (getr32(c1), getg32(c1), getb32(c1), getr32(c2), getg32(c2), getb32(c2));
//      xfb[i++]=CvtRGB (getr32(screen->line[y][x*2]), getg32(screen->line[y][x*2]), getb32(screen->line[y][x*2]), getr32(screen->line[y][x*2+1]), getg32(screen->line[y][x*2+1]), getb32(screen->line[y][x*2+1]));
    }
  }
}


static struct BITMAP *wii_gfx_init(int w, int h, int v_w, int v_h, int color_depth);
static void wii_gfx_exit(struct BITMAP *b);
static int wii_gfx_scroll(int x, int y);
static void wii_gfx_vsync();
static void wii_gfx_set_palette(AL_CONST struct RGB *p, int from, int to, int retracesync);
static struct BITMAP *wii_gfx_create_video_bitmap(int width, int height);
static void wii_gfx_destroy_video_bitmap(struct BITMAP *bitmap);
static int wii_gfx_show_video_bitmap(struct BITMAP *bitmap);
static int wii_gfx_request_video_bitmap(struct BITMAP *bitmap);
GFX_MODE_LIST *wii_gfx_fetch_mode_list();

GXRModeObj *rmode = NULL;

#if(0)  //might need this later, not sure
static GFX_VTABLE _wii_gfx_vtable = 
{
	0,		/*int color_depth;*/
	0,		/*int mask_color;*/
	NULL,	/*void *unwrite_bank;  C function on some machines, asm on i386 */
	NULL,	/*AL_METHOD(void, set_clip, (struct BITMAP *bmp));*/
	NULL,	/*AL_METHOD(void, acquire, (struct BITMAP *bmp));*/
	NULL,	/*AL_METHOD(void, release, (struct BITMAP *bmp));*/
	NULL,	/*AL_METHOD(struct BITMAP *, create_sub_bitmap, (struct BITMAP *parent, int x, int y, int width, int height));*/
	NULL,	/*AL_METHOD(void, created_sub_bitmap, (struct BITMAP *bmp, struct BITMAP *parent));*/
	NULL,	/*AL_METHOD(int,  getpixel, (struct BITMAP *bmp, int x, int y));*/
	NULL,	/*AL_METHOD(void, putpixel, (struct BITMAP *bmp, int x, int y, int color));*/
	NULL,	/*AL_METHOD(void, vline, (struct BITMAP *bmp, int x, int y_1, int y2, int color));*/
	NULL,	/*AL_METHOD(void, hline, (struct BITMAP *bmp, int x1, int y, int x2, int color));*/
	NULL,	/*AL_METHOD(void, hfill, (struct BITMAP *bmp, int x1, int y, int x2, int color));*/
	NULL,	/*AL_METHOD(void, line, (struct BITMAP *bmp, int x1, int y_1, int x2, int y2, int color));*/
	NULL,	/*AL_METHOD(void, fastline, (struct BITMAP *bmp, int x1, int y_1, int x2, int y2, int color));*/
	NULL,	/*AL_METHOD(void, rectfill, (struct BITMAP *bmp, int x1, int y_1, int x2, int y2, int color));*/
	NULL,	/*AL_METHOD(void, triangle, (struct BITMAP *bmp, int x1, int y_1, int x2, int y2, int x3, int y3, int color));*/
	NULL,	/*AL_METHOD(void, draw_sprite, (struct BITMAP *bmp, struct BITMAP *sprite, int x, int y));*/
	NULL,	/*AL_METHOD(void, draw_256_sprite, (struct BITMAP *bmp, struct BITMAP *sprite, int x, int y));*/
	NULL,	/*AL_METHOD(void, draw_sprite_v_flip, (struct BITMAP *bmp, struct BITMAP *sprite, int x, int y));*/
	NULL,	/*AL_METHOD(void, draw_sprite_h_flip, (struct BITMAP *bmp, struct BITMAP *sprite, int x, int y));*/
	NULL,	/*AL_METHOD(void, draw_sprite_vh_flip, (struct BITMAP *bmp, struct BITMAP *sprite, int x, int y));*/
	NULL,	/*AL_METHOD(void, draw_trans_sprite, (struct BITMAP *bmp, struct BITMAP *sprite, int x, int y));*/
	NULL,	/*AL_METHOD(void, draw_trans_rgba_sprite, (struct BITMAP *bmp, struct BITMAP *sprite, int x, int y));*/
	NULL,	/*AL_METHOD(void, draw_lit_sprite, (struct BITMAP *bmp, struct BITMAP *sprite, int x, int y, int color));*/
	NULL,	/*AL_METHOD(void, draw_rle_sprite, (struct BITMAP *bmp, AL_CONST struct RLE_SPRITE *sprite, int x, int y));*/
	NULL,	/*AL_METHOD(void, draw_trans_rle_sprite, (struct BITMAP *bmp, AL_CONST struct RLE_SPRITE *sprite, int x, int y));*/
	NULL,	/*AL_METHOD(void, draw_trans_rgba_rle_sprite, (struct BITMAP *bmp, AL_CONST struct RLE_SPRITE *sprite, int x, int y));*/
	NULL,	/*AL_METHOD(void, draw_lit_rle_sprite, (struct BITMAP *bmp, AL_CONST struct RLE_SPRITE *sprite, int x, int y, int color));*/
	NULL,	/*AL_METHOD(void, draw_character, (struct BITMAP *bmp, struct BITMAP *sprite, int x, int y, int color, int bg));*/
	NULL,	/*AL_METHOD(void, draw_glyph, (struct BITMAP *bmp, AL_CONST struct FONT_GLYPH *glyph, int x, int y, int color, int bg));*/
	NULL,	/*AL_METHOD(void, blit_from_memory, (struct BITMAP *source, struct BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height));*/
	NULL,	/*AL_METHOD(void, blit_to_memory, (struct BITMAP *source, struct BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height));*/
	NULL,	/*AL_METHOD(void, blit_from_system, (struct BITMAP *source, struct BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height));*/
	NULL,	/*AL_METHOD(void, blit_to_system, (struct BITMAP *source, struct BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height));*/
	NULL,	/*AL_METHOD(void, blit_to_self, (struct BITMAP *source, struct BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height));*/
	NULL,	/*AL_METHOD(void, blit_to_self_forward, (struct BITMAP *source, struct BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height));*/
	NULL,	/*AL_METHOD(void, blit_to_self_backward, (struct BITMAP *source, struct BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height));*/
	NULL,	/*AL_METHOD(void, blit_between_formats, (struct BITMAP *source, struct BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height));*/
	NULL,	/*AL_METHOD(void, masked_blit, (struct BITMAP *source, struct BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height));*/
	NULL,	/*AL_METHOD(void, clear_to_color, (struct BITMAP *bitmap, int color));*/
	NULL,	/*AL_METHOD(void, pivot_scaled_sprite_flip, (struct BITMAP *bmp, struct BITMAP *sprite, fixed x, fixed y, fixed cx, fixed cy, fixed angle, fixed scale, int v_flip));*/
	NULL,	/*AL_METHOD(void, do_stretch_blit, (struct BITMAP *source, struct BITMAP *dest, int source_x, int source_y, int source_width, int source_height, int dest_x, int dest_y, int dest_width, int dest_height, int masked));*/
	NULL,	/*AL_METHOD(void, draw_gouraud_sprite, (struct BITMAP *bmp, struct BITMAP *sprite, int x, int y, int c1, int c2, int c3, int c4));*/
	NULL,	/*AL_METHOD(void, draw_sprite_end, (void));*/
	NULL,	/*AL_METHOD(void, blit_end, (void));*/
	NULL,	/*AL_METHOD(void, polygon, (struct BITMAP *bmp, int vertices, AL_CONST int *points, int color));*/
	NULL,	/*AL_METHOD(void, rect, (struct BITMAP *bmp, int x1, int y_1, int x2, int y2, int color));*/
	NULL,	/*AL_METHOD(void, circle, (struct BITMAP *bmp, int x, int y, int radius, int color));*/
	NULL,	/*AL_METHOD(void, circlefill, (struct BITMAP *bmp, int x, int y, int radius, int color));*/
	NULL,	/*AL_METHOD(void, ellipse, (struct BITMAP *bmp, int x, int y, int rx, int ry, int color));*/
	NULL,	/*AL_METHOD(void, ellipsefill, (struct BITMAP *bmp, int x, int y, int rx, int ry, int color));*/
	NULL,	/*AL_METHOD(void, arc, (struct BITMAP *bmp, int x, int y, fixed ang1, fixed ang2, int r, int color));*/
	NULL,	/*AL_METHOD(void, spline, (struct BITMAP *bmp, AL_CONST int points[8], int color));*/
	NULL,	/*AL_METHOD(void, floodfill, (struct BITMAP *bmp, int x, int y, int color));*/
	NULL,	/*AL_METHOD(void, polygon3d, (struct BITMAP *bmp, int type, struct BITMAP *texture, int vc, V3D *vtx[]));*/
	NULL,	/*AL_METHOD(void, polygon3d_f, (struct BITMAP *bmp, int type, struct BITMAP *texture, int vc, V3D_f *vtx[]));*/
	NULL,	/*AL_METHOD(void, triangle3d, (struct BITMAP *bmp, int type, struct BITMAP *texture, V3D *v1, V3D *v2, V3D *v3));*/
	NULL,	/*AL_METHOD(void, triangle3d_f, (struct BITMAP *bmp, int type, struct BITMAP *texture, V3D_f *v1, V3D_f *v2, V3D_f *v3));*/
	NULL,	/*AL_METHOD(void, quad3d, (struct BITMAP *bmp, int type, struct BITMAP *texture, V3D *v1, V3D *v2, V3D *v3, V3D *v4));*/
	NULL,	/*AL_METHOD(void, quad3d_f, (struct BITMAP *bmp, int type, struct BITMAP *texture, V3D_f *v1, V3D_f *v2, V3D_f *v3, V3D_f *v4));*/
};
#endif
GFX_DRIVER gfx_wii =
{
	GFX_WII,					/* int  id; */
	"Wii GFX", 					/* AL_CONST char *name; */
	"Wii gfx driver",		/* AL_CONST char *desc; */
	"Wii GFX",					/* AL_CONST char *ascii_name; */
	wii_gfx_init,				/* AL_METHOD(struct BITMAP *, init, (int w, int h, int v_w, int v_h, int color_depth)); */
	wii_gfx_exit,				/* AL_METHOD(void, exit, (struct BITMAP *b)); */
	wii_gfx_scroll,				/* AL_METHOD(int, scroll, (int x, int y)); */
	wii_gfx_vsync,				/* AL_METHOD(void, vsync, (void)); */
	wii_gfx_set_palette,	/* AL_METHOD(void, set_palette, (AL_CONST struct RGB *p, int from, int to, int retracesync)); */
	NULL,						/* AL_METHOD(int, request_scroll, (int x, int y)); */
	NULL,						/* AL_METHOD(int, poll_scroll, (void)); */
	NULL,						/* AL_METHOD(void, enable_triple_buffer, (void)); */
	wii_gfx_create_video_bitmap,	/* AL_METHOD(struct BITMAP *, create_video_bitmap, (int width, int height)); */
	wii_gfx_destroy_video_bitmap,/* AL_METHOD(void, destroy_video_bitmap, (struct BITMAP *bitmap)); */
	wii_gfx_show_video_bitmap,	/* AL_METHOD(int, show_video_bitmap, (struct BITMAP *bitmap)); */
	wii_gfx_request_video_bitmap,/* AL_METHOD(int, request_video_bitmap, (struct BITMAP *bitmap)); */
	NULL,						/* AL_METHOD(struct BITMAP *, create_system_bitmap, (int width, int height)); */
	NULL,						/* AL_METHOD(void, destroy_system_bitmap, (struct BITMAP *bitmap)); */
	NULL,						/* AL_METHOD(int, set_mouse_sprite, (struct BITMAP *sprite, int xfocus, int yfocus)); */
	NULL,						/* AL_METHOD(int, show_mouse, (struct BITMAP *bmp, int x, int y)); */
	NULL,						/* AL_METHOD(void, hide_mouse, (void)); */
	NULL,						/* AL_METHOD(void, move_mouse, (int x, int y)); */
	NULL,						/* AL_METHOD(void, drawing_mode, (void)); */
	NULL,						/* AL_METHOD(void, save_video_state, (void)); */
	NULL,						/* AL_METHOD(void, restore_video_state, (void)); */
	NULL,						/* AL_METHOD(void, set_blender_mode, (int mode, int r, int g, int b, int a)); */
	wii_gfx_fetch_mode_list,	/* AL_METHOD(GFX_MODE_LIST *, fetch_mode_list, (void)); */
	640,						/* int w; */				/* physical (not virtual!) screen size */
	480,						/* int h; */				/* physical (not virtual!) screen size */
	1,							/* int linear; */			/* true if video memory is linear */
	0,							/* long bank_size; */		/* bank size, in bytes */
	0,							/* long bank_gran; */		/* bank granularity, in bytes */
	0,							/* long vid_mem; */			/* video memory size, in bytes */
	0,							/* long vid_phys_base; */	/* physical address of video memory */
	0,							/* int windowed; */			/* true if driver runs windowed */
};

/* wii_gfx_set_palette:
 */
static void wii_gfx_set_palette(AL_CONST struct RGB *p, int from, int to, int retracesync)
{
  return;
}

/* gfx_wii_lock:
 */
static void gfx_wii_lock(struct BITMAP *bmp)
{
  return;
}

/* gfx_wii_unlock:
 */
static void gfx_wii_unlock(struct BITMAP *bmp)
{
  return;
}


void gfx_wii_unwrite_bank(BITMAP *bmp)
{
  return;
}


/* render_proc:
 *  Timer proc that updates the window.
 */
static void render_proc(void)
{
  if (!afb)
  {
    return;
  }
  switch (_color_depth)
  {
    case 8:
      copy_8bit_afb_to_xfb();
      break;
    case 15:
      copy_15bit_afb_to_xfb();
      break;
    case 16:
      copy_16bit_afb_to_xfb();
      break;
    case 24:
      copy_24bit_afb_to_xfb();
      break;
    case 32:
      copy_32bit_afb_to_xfb();
      break;
  }
}

static struct BITMAP *wii_gfx_init(int w, int h, int v_w, int v_h, int color_depth)
{
  switch(color_depth)
  {
    case 8:
      _screen_vtable = __linear_vtable8;
      break;
    case 15:
      _screen_vtable = __linear_vtable15;
      break;
    case 16:
      _screen_vtable = __linear_vtable16;
      break;
    case 24:
      _screen_vtable = __linear_vtable24;
      break;
    case 32:
      _screen_vtable = __linear_vtable32;
      break;
  }

  screen_surf = _AL_MALLOC_ATOMIC(w * h * BYTES_PER_PIXEL(color_depth));
  afb = _make_bitmap(w, h, (unsigned long)screen_surf, &gfx_wii, color_depth, w * BYTES_PER_PIXEL(color_depth));

//  wii_screen = _make_bitmap(w, h, 0x6000000,     &gfx_hw_wii,         color_depth,     v_w * BYTES_PER_PIXEL(color_depth));
//  wii_screen = _make_bitmap(w, h, uintptr_t addr, GFX_DRIVER *driver, int color_depth, int bpl)
		
  clear_to_color(afb, 0);

  /* virtual screen are not supported */
  if ((v_w!=0 && v_w!=w) || (v_h!=0 && v_h!=h))
  return NULL;

  gfx_wii.w = w;
  gfx_wii.h = h;

  /* the last flag serves as an end of loop delimiter */
  //wii_dirty_lines = _AL_MALLOC_ATOMIC((h+1) * sizeof(char));
  //ASSERT(wii_dirty_lines);
  //memset(wii_dirty_lines, 0, (h+1) * sizeof(char));
  //wii_dirty_lines[h] = 1;

  /* create the screen surface */
  _screen_vtable.acquire = gfx_wii_lock;
  _screen_vtable.release = gfx_wii_unlock;
  _screen_vtable.unwrite_bank = gfx_wii_unwrite_bank; 

  /* create render timer */
  install_int(render_proc, RENDER_DELAY);

/*
  while(1)
  {
    unsigned char* afbc = (unsigned char*)screen_surf;
    int i=0, x1=0;
    for(i=0;i<480*640;++i)
    {
      afbc[x1+1]=rand()%256;
      afbc[x1+2]=rand()%256;
      afbc[x1+3]=rand()%256;
      x1+=4;
    }
//    copy_32bit_afb_to_xfb();
//    VIDEO_WaitVSync();
  }
*/
  return afb;

//  Error:
  wii_gfx_exit(NULL);

  return NULL;

}

static void wii_gfx_exit(struct BITMAP *b)
{
  _AL_FREE(screen_surf);
  return;
}

static int wii_gfx_scroll(int x, int y)
{
  return 0;
}

static void wii_gfx_vsync()
{
//  if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
  VIDEO_WaitVSync();
  return;
}

static struct BITMAP *wii_gfx_create_video_bitmap(int width, int height)
{
  return NULL;
}

static void wii_gfx_destroy_video_bitmap(struct BITMAP *bitmap)
{
  return;
}

static int wii_gfx_show_video_bitmap(struct BITMAP *bitmap)
{
  return 0;
}

static int wii_gfx_request_video_bitmap(struct BITMAP *bitmap)
{
  return 0;
}

GFX_MODE_LIST *wii_gfx_fetch_mode_list()
{
	GFX_MODE_LIST *list = malloc(sizeof(GFX_MODE_LIST));
	if(!list)
		return NULL;

	list->num_modes = 5;

	list->mode = malloc(sizeof(GFX_MODE_LIST*) * list->num_modes);
	if(!list->mode)
  {
		_AL_FREE(list);
		return NULL;
	}

	list->mode[0].width = gfx_wii.w;
	list->mode[0].height = gfx_wii.h;
	list->mode[0].bpp = 8;

	list->mode[1].width = gfx_wii.w;
	list->mode[1].height = gfx_wii.h;
	list->mode[1].bpp = 15;

	list->mode[2].width = gfx_wii.w;
	list->mode[2].height = gfx_wii.h;
	list->mode[2].bpp = 16;

	list->mode[3].width = gfx_wii.w;
	list->mode[3].height = gfx_wii.h;
	list->mode[3].bpp = 24;

	list->mode[4].width = gfx_wii.w;
	list->mode[4].height = gfx_wii.h;
	list->mode[4].bpp = 32;

	return list;
}

_DRIVER_INFO _gfx_driver_list[] =
{
   {GFX_WII, &gfx_wii, TRUE},
   {0, NULL, 0}
};

