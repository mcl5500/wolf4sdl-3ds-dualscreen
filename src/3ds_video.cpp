#include "3ds_video.h"

byte *s_right_eye_buffer = NULL;
int s_weapon_stereo_shift = 0;
int s_stereo_pass = 0;
fixed s_min_wall_distance = 0x8000;
fixed s_cur_min_wall_distance = 0x7fffffff;

#ifdef __3DS__

void N3DS_InitVideo(void)
{
    gfxInitDefault();
    gfxSet3D(true);
    gfxSetDoubleBuffering(GFX_TOP, true);
    gfxSetDoubleBuffering(GFX_BOTTOM, true);
    gfxSetScreenFormat(GFX_TOP, GSP_BGR8_OES);
    gfxSetScreenFormat(GFX_BOTTOM, GSP_BGR8_OES);

    if (!s_right_eye_buffer) {
        s_right_eye_buffer = (byte *) malloc(400 * 240);
        if (s_right_eye_buffer)
            memset(s_right_eye_buffer, 0, 400 * 240);
    }
}

void N3DS_ShutdownVideo(void)
{
    if (s_right_eye_buffer) {
        free(s_right_eye_buffer);
        s_right_eye_buffer = NULL;
    }
    gfxExit();
}

float N3DS_GetSliderState(void)
{
    return osGet3DSliderState();
}

static inline void N3DS_BlitTop(u8 *dst, const byte *src, int shift_x)
{
    if (!dst || !src) return;

    // 3DS Top Screen: 400x240 landscape (physical 240x400 portrait, column stride = 240 * 3 = 720 bytes)
    for (int y = 0; y < 240; y++) {
        const byte *src_row = &src[y * 400];
        int dst_col_offset = (239 - y) * 3;
        int dst_idx = dst_col_offset;

        for (int x = 0; x < 400; x++, dst_idx += 720) {
            int src_x = x - shift_x;
            if (src_x < 0) src_x = 0;
            else if (src_x >= 400) src_x = 399;

            byte pal_idx = src_row[src_x];
            const SDL_Color *col = &curpal[pal_idx];

            dst[dst_idx + 0] = col->b;
            dst[dst_idx + 1] = col->g;
            dst[dst_idx + 2] = col->r;
        }
    }
}

static inline void N3DS_BlitBottom(u8 *dst, const byte *src)
{
    if (!dst || !src) return;

    // 3DS Bottom Screen: 320x240 landscape (physical 240x320 portrait, column stride = 240 * 3 = 720 bytes)
    // Source is from lines 240..479 of screenBuffer, centered horizontally at x=40
    for (int y = 0; y < 240; y++) {
        const byte *src_row = &src[(240 + y) * 400 + 40];
        int dst_col_offset = (239 - y) * 3;
        int dst_idx = dst_col_offset;

        for (int x = 0; x < 320; x++, dst_idx += 720) {
            byte pal_idx = src_row[x];
            const SDL_Color *col = &curpal[pal_idx];

            dst[dst_idx + 0] = col->b;
            dst[dst_idx + 1] = col->g;
            dst[dst_idx + 2] = col->r;
        }
    }
}

void N3DS_PresentStereo(const byte *src_left, const byte *src_right, const byte *src_bottom, int shift_x)
{
    u8 *dst_l = (u8 *)gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    u8 *dst_r = (u8 *)gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
    u8 *dst_b = (u8 *)gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);

    if (dst_l && src_left)
        N3DS_BlitTop(dst_l, src_left, -shift_x);
    if (dst_r && src_right)
        N3DS_BlitTop(dst_r, src_right, +shift_x);
    if (dst_b && src_bottom)
        N3DS_BlitBottom(dst_b, src_bottom);

    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
}

void N3DS_PresentMono(const byte *src_top, const byte *src_bottom)
{
    u8 *dst_l = (u8 *)gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    u8 *dst_r = (u8 *)gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
    u8 *dst_b = (u8 *)gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);

    if (dst_l && src_top)
        N3DS_BlitTop(dst_l, src_top, 0);
    if (dst_r && src_top)
        N3DS_BlitTop(dst_r, src_top, 0);
    if (dst_b && src_bottom)
        N3DS_BlitBottom(dst_b, src_bottom);

    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
}

void N3DS_PresentMono32(const uint32_t *src_pixels)
{
    if (!src_pixels) return;

    u8 *dst_l = (u8 *)gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    u8 *dst_r = (u8 *)gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL);
    u8 *dst_b = (u8 *)gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);

    if (dst_l || dst_r) {
        for (int y = 0; y < 240; y++) {
            const uint32_t *src_row = &src_pixels[y * 400];
            int dst_col_offset = (239 - y) * 3;
            int dst_idx = dst_col_offset;

            for (int x = 0; x < 400; x++, dst_idx += 720) {
                uint32_t c = src_row[x];
                u8 r = (c >> 0) & 0xFF;
                u8 g = (c >> 8) & 0xFF;
                u8 b = (c >> 16) & 0xFF;

                if (dst_l) {
                    dst_l[dst_idx + 0] = b;
                    dst_l[dst_idx + 1] = g;
                    dst_l[dst_idx + 2] = r;
                }
                if (dst_r) {
                    dst_r[dst_idx + 0] = b;
                    dst_r[dst_idx + 1] = g;
                    dst_r[dst_idx + 2] = r;
                }
            }
        }
    }

    if (dst_b) {
        for (int y = 0; y < 240; y++) {
            const uint32_t *src_row = &src_pixels[(240 + y) * 400 + 40];
            int dst_col_offset = (239 - y) * 3;
            int dst_idx = dst_col_offset;

            for (int x = 0; x < 320; x++, dst_idx += 720) {
                uint32_t c = src_row[x];
                dst_b[dst_idx + 0] = (c >> 16) & 0xFF;
                dst_b[dst_idx + 1] = (c >> 8) & 0xFF;
                dst_b[dst_idx + 2] = (c >> 0) & 0xFF;
            }
        }
    }

    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
}

#else

void N3DS_InitVideo(void) {}
void N3DS_ShutdownVideo(void) {}
float N3DS_GetSliderState(void) { return 0.0f; }
void N3DS_PresentStereo(const byte *src_left, const byte *src_right, const byte *src_bottom, int shift_x) {}
void N3DS_PresentMono(const byte *src_top, const byte *src_bottom) {}
void N3DS_PresentMono32(const uint32_t *src_pixels) {}

#endif
