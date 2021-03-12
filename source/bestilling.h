
#pragma once

enum bestillingsType{opp, inn, ned};

struct bestilling
{
    int etasje;                 // Etasje heisen skal til
    enum bestillingsType type;  // Knapptypen, enten er knappen fra heispanelet, eller så er det utenfra med et ønske om enten opp eller ned

};

int numOrders;

void o_lookForOrders();

void o_orderProcessed();

void o_orderCheck();

void o_checkDir();

int o_findOrderToSameFloor();

void o_putOrderFirst();

void pushArrayBack();

void pushArray();

void orderSent();

int o_returnNextOrder();      // Funksjon skal bare brukes hvis det finnes en bestilling

void o_checkOrderDone();

bool queueIsEmpty();