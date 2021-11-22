#include <stdio.h>
#include "function.h"

int main() {
    // The Menu is made as the customer will follow the convention given and will not try to skirt the system

    Element_str* l_tastes = init_tastes();
    Order_Queue* q_orders = init_order_queue();
    Tasting_Queue* q_tasting = init_testing_queue();
    Deliver_Queue *d_queue=init_d_queue();
    int choice = 0;
    do{                                 //Basic Menu with choice
        int nb_parts=1;
        choice=0;
        for(int i=0; i <106;i++){
            putchar('-');
        }
        putchar('\n');
        printf("1: Order     2: Show Order Queue     3: Cake Creation and Build    4: Delivery    5: Tasting    else: Exit\n");
        for(int i=0; i <106;i++){
            putchar('-');
        }
        putchar('\n');
        scanf("%d", &choice);
        putchar('\n');
        if (choice == 1){
            char yourorder[50];
            printf("What's your order Sir ?\n");
            putchar('\n');
            scanf("%s", yourorder);
            putchar('\n');
            pass_order(yourorder, q_orders);
        }
        if (choice == 2) {
            display(q_orders);
        }
        if (choice == 3) {
            Cake *cake=create_cake(process_order(q_orders));
            build_cake(cake, l_tastes, d_queue);
        }
        if (choice==4){
            deliver(d_queue, q_tasting);
        }
        if (choice==5){
            printf("How many parts do you want to eat from your cake?\n");
            putchar('\n');
            scanf("%d", &nb_parts);
            putchar('\n');
            printf("%s %d\n", q_tasting->f_queue->cake->order->text, nb_parts);
            tasting(q_tasting, nb_parts);
        }
    }while(choice>0 && choice<6);
    return 0;}