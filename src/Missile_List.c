#include "Missile_List.h"
#include <stdlib.h>

struct Missile_Node* g_missile_head = NULL;
struct Missile_Node* g_missile_tail = NULL;

struct Missile_Node* create_missile_node()
{
	struct Missile_Node* node = (struct Missile_Node*) malloc(sizeof(struct Missile_Node));

	if (node == NULL)
	{
		printf("Error creating new missile, ran out of memory?\n");
	}

	return node;
}

int add_missile(float sx, float sy, float a, long ltime, long dtime, long eradius, int id)
{
	struct Missile_Node* node = create_missile_node();

    struct Missile* mis = (struct Missile*) malloc(sizeof(struct Missile));

    if (mis == NULL)
        return -1;

	if (node == NULL)
		return -1;

    node->missile = mis;

	node->missile->start_x = sx;
	node->missile->start_y = sy;
    node->missile->angle = a;
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
        g_missile_tail = node;
	}
}

int remove_missile(struct Missile* mis)
{

    if (mis == NULL)
        return -1;

    struct Missile_Node* node = get_head();

    while (node != NULL)
    {
        if (node->next != NULL)
        {
            if (node->next->missile == mis)
            {            
                struct Missile_Node* temp = node->next;

                if (temp->next == NULL)
                {
                    //we need to update the tail too
                    g_missile_tail = temp->next;
                }

                node->next = temp->next;

                free(temp);
            }
        }
        else
        {
            //we're at the tail
        }

        node = node->next;
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