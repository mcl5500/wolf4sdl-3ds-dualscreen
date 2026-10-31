#ifndef _3DS_VIDEO_H_
#define _3DS_VIDEO_H_

#include "wl_def.h"

#ifdef __3DS__
#include <3ds.h>
#endif

extern SDL_Color curpal[256];
extern byte *s_right_eye_buffer;
extern int s_weapon_stereo_shift;
extern int s_stereo_pass;
extern fixed s_min_wall_distance;
extern fixed s_cur_min_wall_distance;

void N3DS_InitVideo(void);
void N3DS_ShutdownVideo(void);
void N3DS_PresentStereo(const byte *src_left, const byte *src_right, const byte *src_bottom, int shift_x);
void N3DS_PresentMono(const byte *src_top, const byte *src_bottom);
void N3DS_PresentMono32(const uint32_t *src_pixels);
float N3DS_GetSliderState(void);

#endif
