/**
 * @file 
 * @brief This module contains functions that changes the state of the elevator. 
 */

#define val MOTORSPEED

    bool retningOpp;
    bool motorPaa;
    bool doraapen;
    int naavaerendeEtasje;
    bool standPlass;
    int currentDestination;
    int bestillingsliste[10];
    
    void enterWaitingMode()
    void kjorTilNesteDestinasjon(int i); 
    bool destinasjonNaadd(int i);
    void settNyDestinasjon(int[] bestillingsliste );
    bool tomBestillingsliste(bestillingsliste b);
    void settRetning(int i, bool b);
    


/*Kjører til etasjen destinasjon*/
