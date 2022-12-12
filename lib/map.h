#ifndef MAP_H
#define MAP_H

#include "robot.h"
#include "sensor.h"

// Which map's path logic to follow.
// 1 = straight line
// 2 = zig zag
#define	MAP_DEF	1

void map_setup ();
void map_logic ();

#endif