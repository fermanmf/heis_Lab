#include "stdbool.h"
#include "stdio.h"
#include "bestilling.h"
#include "heis.h"
#include "hardware.h"
#include "door.h"
#include "indicators.h"

static int bestillingsKo[4] = {0,0,0,0};
static int numOrders = 0;

static struct bestilling order;

static void pushArrayBack() {
    for (int i = numOrders; i > 0; i--)
    {
        bestillingsKo[i] = bestillingsKo[i-1];
    }
};

static void pushArray() {
    for (int i = 1; i < (numOrders+1); i++)
    {
        bestillingsKo[i-1] = bestillingsKo[i];
    }  
};

static void o_orderProcessed() {
    numOrders++;
};

static void orderSent() {
    numOrders--;
    pushArray();
};

static bool o_checkExistence() {
    for(int i = 0; i < numOrders; i++) {
        if (bestillingsKo[i] == order.etasje) {
            return true;
        }
    }
    return false;
}

static void o_between() {
    int firstOrder = bestillingsKo[0];
        if (numOrders==1) {
                bestillingsKo[numOrders] = order.etasje;
                o_orderProcessed();
        }
        else {
            if (firstOrder>g_currentFloor) {
                int swap = 0;
                for (int i = 1; i < numOrders; i++) {
                    if (order.etasje>bestillingsKo[i]) {
                         swap++;
                     }
                }
                if (swap==0) {
                    bestillingsKo[numOrders] = order.etasje;
                    o_orderProcessed();
                }
                else {
                    for (int i = numOrders; i > swap; i--) {
                        bestillingsKo[i] = bestillingsKo[i-1];
                    }
                    bestillingsKo[1] = order.etasje;
                    o_orderProcessed();
                }
            }
            else {
                int swap = 0;
                for (int i = 1; i < numOrders; i++) {
                    if (order.etasje<bestillingsKo[i]) {
                         swap++;
                     }
                }
                if (swap==0) {
                     bestillingsKo[numOrders] = order.etasje;
                    o_orderProcessed();
                }
                else {
                    for (int i = numOrders; i > swap; i--) {
                        bestillingsKo[i] = bestillingsKo[i-1];
                    }
                    bestillingsKo[1] = order.etasje;
                    o_orderProcessed();
                }

            }
                
        }

}

// Bestilling må legges bak i køen
static void o_orderOverFirst() {
    if (numOrders==1) {
        bestillingsKo[numOrders] = order.etasje;
        o_orderProcessed();
    }
    else {
        bool check = false;
        int place;
        for (int i = 1; i < numOrders; i++) {
            if (order.etasje < bestillingsKo[i]) {
                check = true;
                place = i;
                break;
            }
        }
        if (check) {
            for (int i = numOrders; i > place; i--) {
                bestillingsKo[i] = bestillingsKo[i-1];
            }
            bestillingsKo[place] = order.etasje;
            o_orderProcessed();
        }
        else {
            bestillingsKo[numOrders] = order.etasje;
            o_orderProcessed();
        }   
    }
};

static void o_orderBelowFirst() {
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

// Returner hvor i rekken duplikatbestillingen ligger, evt -1 om ingen finnes
static int o_findOrderToSameFloor() {
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
static void o_putOrderFirst() {
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

static void o_checkPriority() {
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

static void o_checkPriority2() {
    // Finner rekkefølge etter heisen snur
    int priority = numOrders;
    for (int i = 1; i < numOrders; i++) {
        if (bestillingsKo[i] > order.etasje) {
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


// Om det ligger en eller flere bestillinger inne
// Sjekk først om bestillingen som er trykket inn allerede skal dit

static void o_arrangeOrder() {
    int firstOrder = bestillingsKo[0];

        if ((g_currentFloor==order.etasje)&&(h_checkIfInbetween())) {

            if ( !o_checkExistence() ){
            o_between();

            }
            return;
        }
        // Bestilling større enn 1. i kø, og mindre enn der heisen står
        if ((firstOrder < order.etasje)&&(firstOrder < g_currentFloor)) {

            if (order.type==opp) {
                if (!o_checkExistence()) {
                    o_checkPriority();
                }
            }
            else if (order.etasje > g_currentFloor) {
                if (!o_checkExistence()) {
                    o_checkPriority2();
                }
            }
            else {
                // Bestillingen skal legges først
                o_putOrderFirst();
            }
        }
        // Bestilling større enn der heisen står, men mindre enn 1. i køa
        else if ((firstOrder > order.etasje)&&(firstOrder > g_currentFloor)) {
            if (order.type==ned) {
                if (!o_checkExistence()) {
                o_checkPriority();
               }
            }
            else if (order.etasje < g_currentFloor) {
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
        else if ((firstOrder > g_currentFloor)&&(order.etasje > firstOrder)){
            if (!o_checkExistence()) {
                if (order.type==ned) {
                    bestillingsKo[numOrders] = order.etasje;
                    o_orderProcessed();
                }
                else {
                    o_orderOverFirst();
                }
            }
        }
        // Bestilling er mindre enn 1. i køa og mindre enn der heisen står
        else if ((firstOrder < g_currentFloor)&&(order.etasje < firstOrder)) {
            if (!o_checkExistence()) {
                if (order.type==opp) {
                    bestillingsKo[numOrders] = order.etasje;
                    o_orderProcessed();
                }
                else {
                    o_orderBelowFirst();
                }
            }
        }
        // Bestillingen er den samme som ligger først
        else {
            if (!o_checkExistence()) {
            bestillingsKo[numOrders] = order.etasje;
            o_orderProcessed();
            }
        }
};

static void o_orderCheck() {
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

void o_lookForOrders() {
    if (!h_stopPushed()){
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

int o_returnNextOrder() {
    int sending = bestillingsKo[0];
    return sending;
};

void o_checkIfOrderDone() {
    if((g_elevatorHasHandeledCurrentOrder) && (numOrders>0)) {
        orderSent();
        g_elevatorHasHandeledCurrentOrder = false;
    }
};

void o_clearOrders() {
    numOrders = 0;
    for (int i = 0; i < 4; i++) {
        bestillingsKo[i] = 0;
    };
};

bool o_newOrderExists() {
    return numOrders;
};