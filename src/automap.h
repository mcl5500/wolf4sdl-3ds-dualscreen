#ifndef _AUTOMAP_H_
#define _AUTOMAP_H_

#include "wl_def.h"

extern byte mapseen[MAPSIZE][MAPSIZE];

void AutoMap_Reset(void);
void AutoMap_Update(void);
void AutoMap_Draw(void);

#endif
