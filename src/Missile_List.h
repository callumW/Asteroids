#ifndef MISSILE_LIST_H
#define MISSILE_LIST_H

struct Missile_Node
{
	struct Missile* missile;
	struct Missile_Node* next;
};

struct Missile_Node* g_missile_head;
struct Missile_Node* g_missile_tail;

struct Missile_Node* create_missile_node()
{
	struct Missile_Node* node = (struct Missile_Node*) malloc(sizeof(struct Missile_Node));

	if (node == NULL)
	{
		printf("Error creating new missile, ran out of memory?\n");
	}

	return node;
}

int add_missile(float sx, float sy, long ltime, long dtime, long eradius, int id)
{
	struct Missile_Node* node = create_missile_node();

	if (node == NULL)
		return -1;

	node->missile->start_x = sx;
	node->missile->start_y = sy;
	node->missile->x = sx;
	node->missile->y = sy;
	node->missile->launch_time = ltime;
	node->missile->detination_time = dtime;
	node->missile->explosion_radius = eradius;
	node->missile->firing_id = id;
	node->next = NULL;

	if (g_missile_head == NULL)
	{
		g_missile_head = node;
		g_missile_tail = node;
	}
	else 
	{
		g_missile_tail->next = node;
	}
}

struct Missile_Node* get_head()
{
	return g_missile_head;
}

struct Missile_Node* get_tail()
{
	return g_missile_tail;
}


#endif