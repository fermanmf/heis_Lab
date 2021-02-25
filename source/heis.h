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
    
    void enterWaitingMode(void);
    void kjorTilNesteDestinasjon(int* currentDestination) ; 
    bool destinasjonNaadd(int bestillingsListe[], int i);
    void settNyDestinasjon(int bestillingsListe []  );
    bool tomBestillingsliste(int b []);
    void settRetning(int i, bool b, int currentFloor);
    void undefinedManouver(enum State* state);
    void stop();

            /* Code block that makes the elevator go up when it reach the botton
            if(hardware_read_floor_sensor(0)){
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
            }

            /* Code block that makes the elevator go down when it reach the top floor
            if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            }
*/