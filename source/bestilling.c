#include "stdbool.h"
#include "stdio.h"
#include "bestilling.h"
#include "heis.h"
#include "hardware.h"

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

int bestillingsKo[10] = {0,0,0,0,0,0,0,0,0,0};
int numOrders = 0;      // Hjelpevariabel for å testekoden, etterhvert skal kun arrayen sjekkes

struct bestilling order;

void o_lookForOrders() {
    if (!h_stopPushed){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (hardware_read_order(i, j)) {
                order.etasje = i;
                order.type = j;
                o_orderCheck();
             }
          }
        }
    }
};

void o_orderProcessed() {
    numOrders++;
};

void o_orderCheck() {
    // Sjekker først om det ligger bestillinger inne
    if (numOrders==0) {
        // Det ligger ikke inne noen bestillinger
        bestillingsKo[0]=order.etasje;
        o_orderProcessed();
        return;
    }
    else {
        // Det ligger inne bestillinger
        o_checkDir();
        return;
    }
};

// Om det ligger en eller flere bestillinger inne
// Sjekk først om bestillingen som er trykket inn allerede skal dit

void o_checkDir() {
    int firstOrder = bestillingsKo[0];
        // Bestillingen er i samme retning som første bestilling
        // Hvis den er nærmere enn heisen og den skal samme vei kan den settes først
        if ((firstOrder < order.etasje)&&(firstOrder < currentFloor)) {
            // Da skal heisen til en etasje, men den nye bestillingen er på veien dit
            // Det må da sjekkes om knappen indikerer at den skal motsatt vei
            // Her skal heisa ned, altså legges bestillingen bakerst om den vil opp
            if (order.type==opp) {
                bestillingsKo[numOrders] = order.etasje;
                o_orderProcessed();
            }
            else {
                // Bestillingen skal legges først
                o_putOrderFirst();
            }
        }
        else if ((firstOrder > order.etasje)&&(firstOrder > currentFloor)) {
            if (order.type==ned) {
                bestillingsKo[numOrders] = order.etasje;
                o_orderProcessed();
            }
            else {
                // Bestillingen skal legges først
                o_putOrderFirst();
            }
        }
        else {
            
        }
};

// Returner hvor i rekken duplikatbestillingen ligger, evt -1 om ingen finnes
int o_findOrderToSameFloor() {
    // Funksjonen skal returnere true om det finnes et tilfelle av samme etasje i bestillingslisten
    for (int i = 0; i < numOrders; i++) {
        int floor = order.etasje;
        if (bestillingsKo[i] == floor) {
            // Det ligger allerede en bestilling til etasjen inne
            return i;
        }
    }
    return -1;
};

// Bestilling skal legges først
void o_putOrderFirst() {
    int num = o_findOrderToSameFloor();
    if (num==-1) {
        // Det finnes ingen andre tilfeller av etasjen i listen
        pushArrayBack();
        bestillingsKo[0]=order.etasje;
        o_orderProcessed();
    }
    else {      // Det som allerede ligger der inne må fjernes
        for (int i = num; i < (numOrders-1); i++) {
            bestillingsKo[i] = bestillingsKo[i+1];
        }
        pushArrayBack();
        bestillingsKo[0]=order.etasje;
        o_orderProcessed();
    }
};

void pushArrayBack() {
    for (int i = numOrders; i > 0; i--)
    {
        bestillingsKo[i] = bestillingsKo[i-1];
    }
};

void pushArray() {
    for (int i = 1; i < (numOrders+1); i++)
    {
        bestillingsKo[i-1] = bestillingsKo[i];
    }  
};

void orderSent() {
    pushArray();
    numOrders--;
};



int o_returnNextOrder() {
    int sending = bestillingsKo[0];
    return sending;
};

void o_checkIfOrderDone() {
    if(m_orderDone) {
        orderSent();
        m_orderDone = false;
    }
};

bool queueIsEmpty() {
    return numOrders;
};