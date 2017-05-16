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
    node->missile->alive = TRUE;

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
    printf("removing missile\n");
    if (mis == NULL)
        return -1;

    struct Missile_Node* node = get_missile_head();
    struct Missile_Node* previous_node = NULL;

    while (node != NULL)
    {
        if (node->next != NULL)
        {
            if (node->missile == mis)
            {
                //not at tail, so we need point previous node to next node.
                if (previous_node == NULL)
                {
                    //we're at the head
                    g_missile_head = node->next;
                    free(node->missile);
                    free(node);
                    return 0;
                }
                else
                {
                    //not at tail nor at head
                    previous_node->next = node->next;
                    free(node->missile);
                    free(node);
                    return 0;
                }
            }
            //else if (node->next->missile == mis)
            //{
            //    struct Missile_Node* temp = node->next;

            //    /* The node to be removed is the tail*/
            //    if (temp->next == NULL)
            //    {
            //        //we need to update the tail too
            //        g_missile_tail = node;
            //    }

            //    node->next = temp->next;

            //    free(temp);
            //    return 0;
            //}
        }
        else
        {
            if (node->missile == mis)
            {
                if (g_missile_head == g_missile_tail)
                {
                    printf("Deleting only missile\n");
                    free(node->missile);
                    free(node);
                    g_missile_head = NULL;
                    g_missile_tail = NULL;
                }
                else 
                {
                    printf("Removing tail\n");
                    free(node->missile);
                    free(node);
                    node = NULL;
                    g_missile_tail = previous_node;
                    previous_node->next = NULL;
                }
                
                return 0;
            }
        }

        previous_node = node;
        node = node->next;
    }

    return -1;
}

struct Missile_Node* get_missile_head()
{
	return g_missile_head;
}

struct Missile_Node* get_missile_tail()
{
	return g_missile_tail;
}