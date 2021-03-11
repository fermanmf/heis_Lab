#include "stdbool.h"
#include "stdio.h"
#include "bestilling.h"
#include "heis.h"
#include "hardware.h"

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

int currentFloor;

int bestillingsKo[10] = { 0 };
int numOrders = 0;      // Hjelpevariabel for å testekoden, etterhvert skal kun arrayen sjekkes

struct bestilling order;

void o_lookForOrders() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (hardware_read_order(i, j)) {
                order.etasje = i;
                order.type = j;
                o_orderCheck();
            }
        }
    }
};

void o_orderProcessed() {
    order.etasje = NULL;
    order.type = NULL;  
};

void o_orderCheck() {
    // Sjekker først om det ligger bestillinger inne
    if (numOrders==0) {
        // Det ligger ikke inne noen bestillinger
        bestillingsKo[0]=order.etasje;
        numOrders += 1;
        o_orderProcessed();
        return;
    }
    else {
        // Det ligger inne bestillinger
        o_checkDir();
    }
};

// Om det ligger en eller flere bestillinger inne
// Sjekk først om bestillingen som er trykket inn allerede skal dit

void o_checkDir() {
    int firstOrder = bestillingsKo[0];
    if((firstOrder < currentFloor)&&(order.etasje > currentFloor)||((firstOrder > currentFloor)&&(order.etasje < currentFloor))) {
        // Bestillingen kan ikke vurderes til å komme først i køen

    }
    else {
        // Bestillingen er i samme retning som første bestilling
        // Hvis den er nærmere enn heisen og den skal samme vei kan den settes først
        if ((firstOrder < order.etasje)&&(firstOrder < currentFloor)) {
            // Da skal heisen til en etasje, men den nye bestillingen er på veien dit
            // Det må da sjekkes om knappen indikerer at den skal motsatt vei
            // Her skal heisa ned, altså legges bestillingen bakerst om den vil opp
            if (order.type==opp) {
                bestillingsKo[o_returnSizeOfOrders()] = order.etasje;
            }
            else {
                // Bestillingen skal legges først
                pushArray();
                bestillingsKo[0] = order.etasje;
            }

        }
        else if ((firstOrder > order.etasje)&&(firstOrder > currentFloor)) {
            if (order.type==ned) {
                bestillingsKo[o_returnSizeOfOrders()+1] = order.etasje;
            }
            else {
                // Bestillingen skal legges først
                pushArrayBack();
                bestillingsKo[0] = order.etasje;
            }
        }
    }
};

void o_checkIfOrderisInLine() {
    int orderFloor = order.etasje;
    int sizeOfOrders = numOrders;
    for (int i = 0; i < sizeOfOrders; i++) {
        if (orderFloor == bestillingsKo[i]) {
            // Det finnes allerede en bestilling dit
            return;
        }
        // Det er en ny etasje og bestillingen må legges til
        o_findPriority(order);
    }
};

void pushArrayBack() {
    for (int i = o_returnSizeOfOrders() - 1; i >= 0; i--)
    {
        bestillingsKo[i] = bestillingsKo[i+1];
    }
    
};

void pushArray() {
    for (int i = 1; i < o_returnSizeOfOrders(); i++)
    {
        bestillingsKo[i] = bestillingsKo[i-1];
    }  
};

int o_returnSizeOfOrders() {
    int antallBestillinger = NELEMS(bestillingsKo);
    return antallBestillinger;
};

bool o_bestillingFraHeispanel(struct bestilling panelBestilling) {
    if (panelBestilling.type == 2) {
        // Bestillingen kommer innenfra
        return true;
    }
    return false;
};

bool o_orderFound() {
    if (bestillingsKo[0] == 0) {
        return false;
    }
    return true;
};

void orderSent() {

};

int o_returnNextOrder(bool* mother_orderDone) {
    if(o_orderFound()) {
        int sending = bestillingsKo[0];
        orderSent();
        *mother_orderDone = true;
        numOrders -= 1;
        return sending;
    }
    
};