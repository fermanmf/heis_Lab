
#pragma once

enum bestillingsType{opp, inn, ned};

struct bestilling
{
    int etasje;                 // Etasje heisen skal til
    enum bestillingsType type;  // Knapptypen, enten er knappen fra heispanelet, eller så er det utenfra med et ønske om enten opp eller ned

};



void o_lookForOrders();

void o_leggTilBestilling(struct bestilling nyBestilling);

bool o_bestillingFraHeispanel(struct bestilling panelBestilling);

int o_returnSizeOfOrders();

bool o_orderFound();

void o_orderCheck();

int o_returnNextOrder(bool* mother_orderDone);      // Funksjon skal bare brukes hvis det finnes en bestilling

void o_checkIfOrderisInLine();

void o_checkDir();

void pushArrayBack();

void pushArray();

void orderSent();