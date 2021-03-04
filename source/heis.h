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

    void h_initiateHardware();
    void enterWaitingMode(void);
    void h_goToDestination(int currentDestination, int currentFloor, bool*m_currentMomentumDir, enum State* state,bool* m_orderDone); 
    bool destinasjonNaadd(int bestillingsListe[], int i);
    void settNyDestinasjon(int bestillingsListe []  );
    bool tomBestillingsliste(int b []);
    void h_settRetning(int currentDestination, bool* currentMomentumDir, int currentFloor);
    void h_goToDefinedState();
    bool h_stop();

            /* Code block that makes the elevator go up when it reach the botton
            if(hardware_read_floor_sensor(0)){
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
            }

            /* Code block that makes the elevator go down when it reach the top floor
            if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            }
*/