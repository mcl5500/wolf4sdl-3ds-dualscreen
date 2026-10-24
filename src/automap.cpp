#include "automap.h"

byte mapseen[MAPSIZE][MAPSIZE];

static int map_scale = 8; // Pixels per tile (64 / map_scale = 8px)

void AutoMap_Reset(void)
{
    memset(mapseen, 0, sizeof(mapseen));
}

void AutoMap_Update(void)
{
    // Reveal visited tiles in line of sight
    for (int y = 0; y < MAPSIZE; y++)
    {
        for (int x = 0; x < MAPSIZE; x++)
        {
            if (spotvis[x][y])
            {
                mapseen[x][y] = 1;
                // Also reveal adjacent wall tiles so corridors have outlines
                for (int dy = -1; dy <= 1; dy++)
                {
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && nx < MAPSIZE && ny >= 0 && ny < MAPSIZE)
                        {
                            if (tilemap[nx][ny] || (MAPSPOT(nx, ny, 1) == PUSHABLETILE))
                                mapseen[nx][ny] = 1;
                        }
                    }
                }
            }
        }
    }
}

static inline void DrawMiniPlot(int x, int y, int color)
{
    if (x >= 0 && (unsigned)x < screenWidth && y >= 0 && (unsigned)y < screenHeight)
    {
        VL_Plot(x, y, color);
    }
}

static void DrawPlayerArrow(int cx, int cy, int dir, int color)
{
    // Draw 3x3 core
    for (int dy = -1; dy <= 1; dy++)
        for (int dx = -1; dx <= 1; dx++)
            DrawMiniPlot(cx + dx, cy + dy, color);

    // Draw pointer tip based on direction (0=East, 1=NE, 2=North, 3=NW, 4=West, 5=SW, 6=South, 7=SE)
    switch (dir)
    {
        case 0: // East (+X)
            DrawMiniPlot(cx + 2, cy, color);
            DrawMiniPlot(cx + 3, cy, color);
            break;
        case 1: // North-East
            DrawMiniPlot(cx + 2, cy - 2, color);
            break;
        case 2: // North (-Y)
            DrawMiniPlot(cx, cy - 2, color);
            DrawMiniPlot(cx, cy - 3, color);
            break;
        case 3: // North-West
            DrawMiniPlot(cx - 2, cy - 2, color);
            break;
        case 4: // West (-X)
            DrawMiniPlot(cx - 2, cy, color);
            DrawMiniPlot(cx - 3, cy, color);
            break;
        case 5: // South-West
            DrawMiniPlot(cx - 2, cy + 2, color);
            break;
        case 6: // South (+Y)
            DrawMiniPlot(cx, cy + 2, color);
            DrawMiniPlot(cx, cy + 3, color);
            break;
        case 7: // South-East
            DrawMiniPlot(cx + 2, cy + 2, color);
            break;
    }
}

void AutoMap_Draw(void)
{
    const int box_x = (screenWidth - 320) / 2;
    const int box_y = 240;
    const int box_w = 320;
    const int box_h = 200; // Leaves 40 pixels (440..480) for the status bar!

    const int center_x = box_x + box_w / 2;
    const int center_y = box_y + box_h / 2;

    // 1. Clear minimap background (black)
    VL_BarScaledCoord(box_x, box_y, box_w, box_h, 0);

    // 2. Outer border (Dark Gray)
    VL_BarScaledCoord(box_x, box_y, box_w, 2, 8);
    VL_BarScaledCoord(box_x, box_y + box_h - 2, box_w, 2, 8);
    VL_BarScaledCoord(box_x, box_y, 2, box_h, 8);
    VL_BarScaledCoord(box_x + box_w - 2, box_y, 2, box_h, 8);

    const int px = player->x >> 10;
    const int py = player->y >> 10;
    const int tw = 64 / map_scale;
    const int th = 64 / map_scale;

    // 3. Draw visible tiles
    for (int ty = 0; ty < MAPSIZE; ty++)
    {
        for (int tx = 0; tx < MAPSIZE; tx++)
        {
            if (!mapseen[tx][ty])
                continue;

            int rx = (tx << 6) / map_scale - px / map_scale + center_x;
            int ry = (ty << 6) / map_scale - py / map_scale + center_y;

            // Clip against minimap box interior
            if (rx + tw < box_x + 2 || rx >= box_x + box_w - 2 ||
                ry + th < box_y + 2 || ry >= box_y + box_h - 2)
                continue;

            int draw_x = rx < box_x + 2 ? box_x + 2 : rx;
            int draw_y = ry < box_y + 2 ? box_y + 2 : ry;
            int draw_w = (rx + tw > box_x + box_w - 2) ? (box_x + box_w - 2 - draw_x) : (rx + tw - draw_x);
            int draw_h = (ry + th > box_y + box_h - 2) ? (box_y + box_h - 2 - draw_y) : (ry + th - draw_y);

            if (draw_w <= 0 || draw_h <= 0)
                continue;

            int color = 0;

            if (MAPSPOT(tx, ty, 1) == PUSHABLETILE)
            {
                color = 14; // Yellow for secret pushwalls!
            }
            else if (tilemap[tx][ty] & BIT_DOOR)
            {
                // Door
                color = 9; // Light Blue
            }
            else if (tilemap[tx][ty] < 0x80 && tilemap[tx][ty] > 0)
            {
                // Solid wall
                color = 7; // Gray
            }
            else if (MAPSPOT(tx, ty, 1) == EXITTILE)
            {
                color = 10; // Light Green for elevator/exit
            }
            else
            {
                // Floor / visited space
                color = 8; // Dark Gray floor dot
                // Just draw a subtle 2x2 floor indicator in center
                VL_BarScaledCoord(draw_x + draw_w / 2, draw_y + draw_h / 2, 1, 1, 8);
                continue;
            }

            VL_BarScaledCoord(draw_x, draw_y, draw_w, draw_h, color);
        }
    }

    // 4. Draw static items (treasure, ammo, keys, health)
    statobj_t *sob = &statobjlist[0];
    while (sob != laststatobj)
    {
        if (sob->shapenum != -1 && (sob->flags & FL_BONUS))
        {
            if (mapseen[sob->tilex][sob->tiley])
            {
                int ix = (((int)sob->tilex << 6) + (TILEGLOBAL >> 11)) / map_scale - px / map_scale + center_x;
                int iy = (((int)sob->tiley << 6) + (TILEGLOBAL >> 11)) / map_scale - py / map_scale + center_y;
                if (ix >= box_x + 3 && ix < box_x + box_w - 3 &&
                    iy >= box_y + 3 && iy < box_y + box_h - 3)
                {
                    VL_BarScaledCoord(ix - 1, iy - 1, 2, 2, 14); // Yellow dot
                }
            }
        }
        sob++;
    }

    // 5. Draw active enemies (only if currently visible / nearby)
    for (objtype *ob = player->next; ob; ob = ob->next)
    {
        if (ob->flags & FL_SHOOTABLE)
        {
            if (spotvis[ob->tilex][ob->tiley])
            {
                int ex = (ob->x >> 10) / map_scale - px / map_scale + center_x;
                int ey = (ob->y >> 10) / map_scale - py / map_scale + center_y;
                if (ex >= box_x + 3 && ex < box_x + box_w - 3 &&
                    ey >= box_y + 3 && ey < box_y + box_h - 3)
                {
                    VL_BarScaledCoord(ex - 1, ey - 1, 3, 3, 12); // Bright Red 3x3 dot
                }
            }
        }
    }

    // 6. Draw Player (White arrow pointing in direction)
    int dir = ((player->angle + 22) / 45) & 7;
    // Map wolf3d angle (0=East, 90=North, 180=West, 270=South) to our 8 directions:
    // In wolf3d: player->angle: 0=E, 45=NE, 90=N, 135=NW, 180=W, 225=SW, 270=S, 315=SE
    DrawPlayerArrow(center_x, center_y, dir, 15); // 15 = White
}
