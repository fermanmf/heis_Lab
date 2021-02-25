#include "stdbool.h"
#include "bestilling.h"
#include "hardware.h"

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

void checkForOrders() {

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {

            if (hardware_read_order(i, j)) {
            
                // Knappen er trykket inn i etasje i og knapp av typen j
                // Det opprettes en ny bestilling
                struct bestilling newOrder;
                newOrder.etasje = i;
                newOrder.type = j;
                leggTilBestilling(newOrder);
                delete(newOrder);
            }
        }
    }
};

void leggTilBestilling(struct bestilling nyBestilling) {

    // Først må det sjekkes om bestillingen kommer fra heispanelet eller etasjepanelet
    bool heispanel = bestillingFraHeispanel(nyBestilling);

    // Hvis bestillingen kommer fra heispanelet skal det opprettes en bestilling til etasjen med en gang
    if (heispanel) {
        bestillingsKø[0] = nyBestilling;
    }
    else {
        /* Hvis bestillingen kommer fra etasjepanelet kan ikke bestillingen legges direkte inn.
           Det betyr at etasjen bestillingen kom fra må sammenlignes med retningen på heisen */
        if (/*nyBestilling.etasje > nåverendeEtasje)&&(retningOpp == 0) || (nyBestilling.etasje < nåverendeEtasje)&&(retningOpp == true*/true) {
            // Ikke legg til bestilling
            return 0;
        }
        else {
            // Heisen skal legge til bestillingen
            bestillingsKø[0] = nyBestilling;
        }
    }

    return 0;
};

int antallBestillinger = NELEMS(bestillingsKø);

int returnerAntallBestillinger() {
    return antallBestillinger;
};

bool bestillingFraHeispanel(struct bestilling panelBestilling) {
    if (panelBestilling.type == 2) {
        // Bestillingen kommer innenfra
        return true;
    }
    return false;
};

bool orderFound() {
    if (returnerAntallBeestillinger() == 0) {
        return false;
    }
    return true;
};

