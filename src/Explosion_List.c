#include "Explosion_List.h"
#include "Game.h"
#include <stdlib.h>

struct Explosion_Node* g_explosion_head = NULL;
struct Explosion_Node* g_explosion_tail = NULL;

struct Explosion_Node* create_explosion_node()
{
    struct Explosion_Node* node = (struct Explosion_Node*) malloc(sizeof(struct Explosion_Node));

    if (node == NULL)
    {
        printf("Error creating new explosion, ran out of memory?\n");
    }

    return node;
}

int add_explosion(float x, float y, float max_r, long life_span, int id)
{
    struct Explosion_Node* node = create_explosion_node();

    struct Explosion* mis = (struct Explosion*) malloc(sizeof(struct Explosion));

    if (mis == NULL)
        return -1;

    if (node == NULL)
        return -1;

    node->explosion = mis;

    node->explosion->x = x;
    node->explosion->y = y;

    node->explosion->max_radius = max_r;
    node->explosion->current_radius = 0.0f;
    node->explosion->time_to_live = life_span;
    node->explosion->spawn_time = g_current_time;
    node->explosion->firing_id = id;
    node->explosion->alive = TRUE;

    node->next = NULL;
    

    if (g_explosion_head == NULL)
    {
        g_explosion_head = node;
        g_explosion_tail = node;
    }
    else
    {
        g_explosion_tail->next = node;
        g_explosion_tail = node;
    }
}

struct Explosion_Node* get_explosion_head()
{
    return g_explosion_head;
}

struct Explosion_Node* get_explosion_tail()
{
    return g_explosion_tail;
}

int remove_explosion(struct Explosion* exp)
{

    if (exp == NULL)
        return -1;

    struct Explosion_Node* node = get_explosion_head();
    struct Explosion_Node* previous_node = NULL;

    while (node != NULL)
    {
        if (node->next != NULL)
        {
            if (node->explosion == exp)
            {
                //not at tail, so we need point previous node to next node.
                if (previous_node == NULL)
                {
                    //we're at the head
                    g_explosion_head = node->next;
                    free(node->explosion);
                    free(node);
                    
                    node = NULL;
                    return 0;
                }
                else
                {
                    //not at tail nor at head
                    previous_node->next = node->next;
                    free(node->explosion);
                    free(node);
                    
                    node = NULL;
                    return 0;
                }
            }
            //if (node->next->explosion == exp)
            //{
            //    struct Explosion_Node* temp = node->next;

            //    /* The node to be removed is the tail*/
            //    if (temp->next == NULL)
            //    {
            //        //we need to update the tail too
            //        g_explosion_tail = node;
            //    }

            //    node->next = temp->next;

            //    free(temp);
            //    //printf("Removed explosion\n");
            //    return 0;
            //}
        }
        else
                //we are at the tail
        {
            if (node->explosion == exp)
            {
                if (g_explosion_head == g_explosion_tail)
                {
                    free(node->explosion);
                    free(node);
                    
                    node = NULL;
                    g_explosion_head = NULL;
                    g_explosion_tail = NULL;
                }
                else
                {
                    free(node->explosion);
                    free(node);

                    node = NULL;
                    g_explosion_tail = previous_node;
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