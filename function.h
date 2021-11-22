//
// Created by cleme on 07/10/2021.
//

#ifndef UNTITLED7_FUNCTIONS_H
#define UNTITLED7_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>                 //We need to copy some char and find their len easily

typedef struct Element_str {
    char text[50];
    struct Element_str *next;
} Element_str;

typedef struct Taste_Stack {
    Element_str *stack;
} Taste_Stack;

typedef struct Cake {
    Element_str *order;
    Taste_Stack *s_tastes;
} Cake;

typedef struct Element_cake {
    Cake *cake;
    struct Element_cake *next;
} Element_cake;

typedef struct Order_Queue {
    Element_str *f_queue;
    Element_str *l_queue;
    int size;
} Order_Queue;

typedef struct Tasting_Queue {
    Element_cake *f_queue;
    Element_cake *l_queue;
} Tasting_Queue;

typedef struct Deliver_Queue {
    Element_cake *f_queue;
    Element_cake *l_queue;
} Deliver_Queue;

void tasting(Tasting_Queue* q_tasting, int nb_parts);

Element_str *init_tastes();
Deliver_Queue *init_d_queue();


Tasting_Queue *init_testing_queue();


void build_cake(Cake *cake, Element_str *l_tastes, Deliver_Queue *d_queue);
void pass_order(char order[50], Order_Queue *f_orders);

Element_str *process_order(Order_Queue *q_orders);

Cake *create_cake(Element_str *order);

void deliver(Deliver_Queue *d_queue, Tasting_Queue* q_tasting);

Order_Queue *init_order_queue();
Element_str *process_order(Order_Queue *q_orders);

void display(struct Order_Queue *f_orders);
// every function used above are explain in function.c
#endif //UNTITLED7_FUNCTIONS_H