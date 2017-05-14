#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Bool.h"

struct Explosion
{
	float x;
	float y;

	float max_radius;
	float current_radius;

	long time_to_live;
	long spawn_time;

	int firing_id;

    BOOL alive;
};


#endif