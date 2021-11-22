#include "function.h"

Element_str *init_tastes() {
    Element_str *l_taste, *temp;
    char taste_list[7][50] = {"Chocolate", "Vanilla", "Strawberry", "Orange", "Apple", "Banana", "Fudge"};
    l_taste = malloc(sizeof(Element_str));
    l_taste->next = NULL;                               // This function allow us to initialise the list of taste
    strcpy(l_taste->text, taste_list[0]);               //                                   here named "l_taste"
    temp = l_taste;
    for (int i=1; i<7; i++) {
        temp->next = malloc(sizeof(Element_str));
        temp = temp->next;
        strcpy(temp->text, taste_list[i]);
        temp->next = NULL;
    }
    return l_taste;
}
Order_Queue *init_order_queue() {                       // This function setup an empty order queue
    Order_Queue *q_order;                               // We will empty it with all our order 1 by 1 and linked
    q_order = malloc(sizeof(Element_str));
    q_order->f_queue = NULL;
    q_order->l_queue = NULL;
    q_order->size = 0;
    return q_order;
}
Tasting_Queue *init_testing_queue() {          // Same as above we initialise an empty queue
    Tasting_Queue *q_taste;
    q_taste = malloc(sizeof(Element_str));
    q_taste->f_queue = NULL;
    q_taste->l_queue = NULL;
    return q_taste;
}
Deliver_Queue *init_d_queue(){                      // Again, an empty initialisation
    Deliver_Queue *d_queue;
    d_queue=malloc(sizeof(Element_str));
    d_queue->f_queue = NULL;
    d_queue->l_queue = NULL;
    return d_queue;

};

void pass_order(char order[50], Order_Queue *f_orders) {
    if (f_orders->size < 10) {
        Element_str *new_queue = malloc(sizeof(Element_str));
        strcpy(new_queue->text, order);                             // If the queue is empty then the order become the 1st
        new_queue->next = NULL;                                     // else it follow these who are already there
        if (f_orders->f_queue == NULL) {
            f_orders->f_queue = new_queue;
            f_orders->l_queue = new_queue;
        }
        else {
            f_orders->l_queue->next = new_queue;
            f_orders->l_queue = new_queue;
        }
        printf("%s was successfully added to the queue!\n", order);     // confirmation that it worked
        f_orders->size++;
    } else
        printf("Sorry mate, I can't handle more than 10 commands\n");   // case where there is more than 10 orders
}                                                                       // (counted by the size++)
Element_str *process_order(Order_Queue *q_orders) {     // Here the function erase the first order replacing it by the
    Element_str *temp = q_orders->f_queue;              // next one and return a copy of the first erased
    if (q_orders->f_queue != NULL) {
        q_orders->f_queue = temp->next;
        q_orders->size--;
    }
    return temp;
}
Cake *create_cake(Element_str *order) {     // We used this function as a couple with the one above, we create the cake
    Cake *cake = malloc(sizeof(Cake));      // with the given copy of the order
    cake->order = order;
    cake->s_tastes = malloc(sizeof(Taste_Stack));           // We allocate memory for the cake and put in the order
    cake->s_tastes->stack = NULL;
    printf("The cake %s has been create ", order->text);
    return cake;
}
void build_cake(Cake *cake, Element_str *l_tastes, Deliver_Queue *d_queue) {
    int check;                                                      // With the created cake we obtained before
    Element_str *temp, *temp2;                                      // we build the cake with the good taste
    printf("and successfully built as ");
    for (int i = 0; i < strlen(cake->order->text); i++) {
        temp = malloc(sizeof(Element_str));
        temp->next = cake->s_tastes->stack;
        cake->s_tastes->stack = temp;
        check = 1;
        temp2 = l_tastes;
        while (temp2 != NULL && check) {
            if ((temp2->text)[0] == (cake->order->text)[i]) {       //Here every taste displayed
                strcpy(temp->text, temp2->text);
                printf("%s ", temp2->text);
                check = 0;
            }
            temp2 = temp2->next;

        }
    }
    printf("\n");
    Element_cake *temp3 = malloc(sizeof(Cake));         //Adding the built cake to the delivery queue
    temp3->cake = cake;
    temp3->next = NULL;
    if(d_queue->f_queue == NULL){
        d_queue->f_queue = temp3;
        d_queue->l_queue = temp3;
    }
    else {
        d_queue->l_queue->next = temp3;
        d_queue->l_queue = temp3;
    }
}
void deliver(Deliver_Queue *d_queue, Tasting_Queue* q_tasting){
    Element_cake *temp = malloc(sizeof(Cake));
    temp->cake = d_queue->f_queue->cake;
    temp->next = NULL;
    if(q_tasting->f_queue == NULL){                     //Adding it in the tasting queue
        q_tasting->f_queue = temp;
        q_tasting->l_queue = temp;
    }
    else {
        q_tasting->l_queue->next = temp;
        q_tasting->l_queue = temp;
    }
    printf("Winner winner chicken dinner! %s has been delivered!\n", d_queue->f_queue->cake->order->text);
    d_queue->f_queue=d_queue->f_queue->next;        //Delivery queue go to the next one
}

void tasting(Tasting_Queue *q_tasting, int nb_parts) {
    if (q_tasting->f_queue != NULL) { //Case: the queue isn't empty
        int i = 0;
        Element_str *cake_temp = q_tasting->f_queue->cake->s_tastes->stack;
        Element_str *temp;
        Element_cake *temp1;
        while (i < nb_parts && q_tasting->f_queue != NULL) { //Every loop the cake lost a floor
            printf("You are eating the %s floor\n", q_tasting->f_queue->cake->s_tastes->stack->text);
            temp = cake_temp;
            cake_temp = cake_temp->next;
            q_tasting->f_queue->cake->s_tastes->stack = cake_temp;
            free(temp);
            if (cake_temp == NULL) { //Case where the cake lost all its floor
                temp1 = q_tasting->f_queue; //We go to the next cake available for the tasting
                q_tasting->f_queue = q_tasting->f_queue->next;
                printf("Greedy Boy ! You ate all the %s cake! \n", temp1->cake->order->text);
                free(temp1);

            }
            if (q_tasting->f_queue != NULL) { //If the cake is not fully eaten, then we update it
                cake_temp = q_tasting->f_queue->cake->s_tastes->stack;
            }
            i++;
        }
    }
    if(q_tasting->f_queue == NULL) {
        printf("There is no more cake ready, I advice you to order an other :)\n"); // Case the queue was empty
    }
}
void display(Order_Queue *q_orders) {           //Just a little checkpoint to display all of our order avilable
    int n=1;
    Element_str *temp=q_orders->f_queue;
    while (temp != NULL)
    {
        printf("Your Cake %s is the %d th of the list\n", temp->text, n);
        temp=temp->next;
        n++;
    }
    printf("\n");
}