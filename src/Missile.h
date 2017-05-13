
#ifndef MISSILE_H
#define MISSILE_H

struct Missile
{
    float start_x;
    float start_y;
    float angle;

    float x;
    float y;

    long launch_time;
    long detination_time;
    float explosion_radius;
    int firing_id;	//who fired the missile? 0, for player, 1 for computer
};

#endif