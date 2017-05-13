#include "Missile.h"


#ifndef MISSILE_LIST_H
#define MISSILE_LIST_H

struct Missile_Node
{
	struct Missile* missile;
	struct Missile_Node* next;
};

extern struct Missile_Node* g_missile_head;
extern struct Missile_Node* g_missile_tail;

struct Missile_Node* create_missile_node();
int add_missile(float sx, float sy, float a, long ltime, long dtime, long eradius, int id);
struct Missile_Node* get_head();
struct Missile_Node* get_tail();


#endif