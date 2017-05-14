#include "Explosion.h"

#ifndef EXPLOSION_LIST_H
#define EXPLOSION_LIST_H

struct Explosion_Node
{
    struct Explosion* explosion;
    struct Explosion_Node* next;
};

extern struct Explosion_Node* g_explosion_head;
extern struct Explosion_Node* g_explosion_tail;

struct Explosion_Node* create_explosion_node();
int add_explosion(float x, float y, float max_r, long life_span, int id);
struct Explosion_Node* get_explosion_head();
struct Explosion_Node* get_explosion_tail();

int remove_explosion(struct Explosion* exp);


#endif