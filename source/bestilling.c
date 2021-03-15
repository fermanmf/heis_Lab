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
        o_arrangeOrder();
        return;
    }
};

bool o_checkExistence() {
    for(int i = 0; i < numOrders; i++) {
        if (bestillingsKo[i] == order.etasje) {
            return true;
        }
    }
    return false;
}

// Om det ligger en eller flere bestillinger inne
// Sjekk først om bestillingen som er trykket inn allerede skal dit

void o_arrangeOrder() {
    int firstOrder = bestillingsKo[0];

        // Bestilling større enn 1. i kø, og mindre enn der heisen står
        if ((firstOrder < order.etasje)&&(firstOrder < currentFloor)) {

            if (order.type==opp) {
                if (!o_checkExistence()) {
                    o_checkPriority();
                }
            }
            else {
                // Bestillingen skal legges først
                o_putOrderFirst();
            }
        }
        // Bestilling større enn der heisen står, men mindre enn 1. i køa
        else if ((firstOrder > order.etasje)&&(firstOrder > currentFloor)) {
            if (order.type==ned) {
                if (!o_checkExistence()) {
                o_checkPriority();
               }
            }
            else {
                // Bestillingen skal legges først
                o_putOrderFirst();
            }
        }
        // Bestilling større enn 1. i køa og større enn der heisen står
        else if ((firstOrder > currentFloor)&&(order.etasje > firstOrder)){
            o_orderOverFirst();
        }
        // Bestilling er mindre enn 1. i køa og mindre enn der heisen står
        else if ((firstOrder < currentFloor)&&(order.etasje < firstOrder)) {
            o_orderBelowFirst();
        }
        // Bestillingen er den samme som ligger først
        else {
            if (!o_checkExistence) {
            bestillingsKo[numOrders] = order.etasje;
            o_orderProcessed();
            }
        }
};

// Bestilling må legges bak i køen
void o_orderOverFirst() {
    if (numOrders > 1) {
    bool squeezedIn = false;
    for (int i = 1; i < numOrders; i++) {
        if (order.etasje < bestillingsKo[i]) {
            squeezedIn = true;
            for (int j = numOrders; j > i; j--) {
                bestillingsKo[j] = bestillingsKo[j-1];
            }
            bestillingsKo[i] = order.etasje;
            o_orderProcessed();
            break;
           }
        }
    if (!squeezedIn) {
        bestillingsKo[numOrders] = order.etasje;
        o_orderProcessed();
      }
    }
    else {
        bestillingsKo[1] = order.etasje;
        o_orderProcessed();
    }
};

void o_orderBelowFirst() {
    if (numOrders > 1) {
    bool squeezedIn = false;
    for (int i = 1; i < numOrders; i++) {
        if (order.etasje > bestillingsKo[i]) {
            squeezedIn = true;
            for (int j = numOrders; j > i; j--) {
                bestillingsKo[j] = bestillingsKo[j-1];
            }
            bestillingsKo[i] = order.etasje;
            o_orderProcessed();
            break;
        }
      }
    if (!squeezedIn) {
        bestillingsKo[numOrders] = order.etasje;
        o_orderProcessed();
    }
    }
    else {
        bestillingsKo[1] = order.etasje;
        o_orderProcessed();
    }
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
        numOrders--; // Det blir fjernet et element fra lista
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

void o_checkPriority() {
    // Finner rekkefølge etter heisen snur
    int priority = numOrders;
    for (int i = 1; i < numOrders; i++) {
        if (bestillingsKo[i] < order.etasje) {
            priority--;
        }
    }
    if (priority==numOrders) {
        // Sett den bakerst i køen
        bestillingsKo[numOrders] = order.etasje;
        o_orderProcessed();
    }
    else {
        for (int i = numOrders; i > priority; i--) {
            bestillingsKo[i] = bestillingsKo[i-1];
        }
        bestillingsKo[priority] = order.etasje;
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

void o_checkOrderDone() {
    if(m_orderDone) {
        orderSent();
        m_orderDone = false;
    }
};

bool queueIsEmpty() {
    return numOrders;
};

void o_clearOrders() {
    numOrders = 0;
    for (int i = 0; i < 10; i++) {
        bestillingsKo[i] = 0;
    };
};