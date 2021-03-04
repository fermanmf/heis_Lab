#include "stdbool.h"
#include "stdio.h"
#include "bestilling.h"
#include "heis.h"
#include "hardware.h"

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

int currentFloor;

void o_lookForOrders() {

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {

            if (hardware_read_order(i, j)) {
            
                // Knappen er trykket inn i etasje i og knapp av typen j
                // Det opprettes en ny bestilling
                struct bestilling newOrder;
                newOrder.etasje = i;
                newOrder.type = j;
                o_leggTilBestilling(newOrder);
                delete(newOrder);
            }
        }
    }
};

void o_leggTilBestilling(struct bestilling nyBestilling) {

    // Først sjekkes det om det ligger bestillinger inne fra før
    if (o_orderFound()) {
        // Det ligger allerede bestillinger inne

    }
    else {
        bestillingsKo[0] = nyBestilling;
    }

};

// Om det ligger en eller flere bestillinger inne
// Sjekk først om bestillingen som e trykket inn allerede skal dit

void o_checkIfOrderisInLine(struct bestilling order) {
    int orderFloor = order.etasje;
    int sizeOfOrders = o_returnSizeOfOrders();
    for (int i = 0; i < sizeOfOrders; i++) {
        if (orderFloor == bestillingsKo[i].etasje) {
            // Det finnes allerede en bestilling dit
            return;
        }
        // Det er en ny etasje og bestillingen må legges til
        o_findPriority(order);
    }
};

void o_findPriority(struct bestilling order) {
    // Sjekker først om første bestilling i køa er i samme retning som bestillingen relativt til heisa

};

void o_checkDir(struct bestilling order) {
    struct bestilling firstOrder = bestillingsKo[0];
    if((firstOrder.etasje < currentFloor)&&(order.etasje > currentFloor)||((firstOrder.etasje > currentFloor)&&(order.etasje < currentFloor))) {
        // Bestillingen kan ikke vurderes til å komme først i køen

    }
    else {
        // Bestillingen er i samme retning som første bestilling
        // Hvis den er nærmere enn heisen og den skal samme vei kan den settes først
        if ((firstOrder.etasje < order.etasje)&&(firstOrder.etasje < currentFloor)) {
            // Da skal heisen til en etasje, men den nye bestillingen er på veien dit
            // Det må da sjekkes om knappen indikerer at den skla motsatt vei
            // Her skal heisa ned, altså legges bestillingen bakerst om den vil opp
            if (order.type==opp) {
                bestillingsKo[o_returnSizeOfOrders()] = order;
            }
            else {
                // Bestillingen skal legges først
                pushArray();
                bestillingsKo[0] = order;
            }

        }
        else if ((firstOrder.etasje > order.etasje)&&(firstOrder.etasje > currentFloor)) {
            if (order.type==ned) {
                bestillingsKo[o_returnSizeOfOrders()+1] = order;
            }
            else {
                // Bestillingen skal legges først
                pushArrayBack();
                bestillingsKo[0] = order;
            }
        }
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
    if (o_returnSizeOfOrders() == 0) {
        return false;
    }
    return true;
};

int o_returnNextOrder(bool* mother_orderDone) {
    if (o_orderFound){
    int next = bestillingsKo[0].etasje;
        if (*mother_orderDone == false) {
            return next;
        }
        else {
             delete(bestillingsKo[0]);
            pushArray();
            return bestillingsKo[0].etasje;
            *mother_orderDone = false;
        }
     }
    else {
        return 1;
    }

};