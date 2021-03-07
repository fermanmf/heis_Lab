
/**
 * @file 
 * @brief This module contains functions that changes the state of the elevator. 
 */

#pragma once

enum State {UndefinedState, StandPlass, StoppMellomEtasje, Bevegelse, DoorOpen};
enum State state;


    void h_initiateHardware();
    void h_goToDestination(int currentDestination, int currentFloor, bool*m_currentMomentumDir, enum State* state,bool* m_orderDone); 
    void h_settRetning(int currentDestination, bool* currentMomentumDir, int currentFloor);
    void h_goToDefinedState();
    bool h_stop();
    bool h_checkIfInbetween();
    void h_stopElevatorMovement();
    void h_atDestination(int currentFloor,int currentDestination, enum State* state,bool* m_orderDone);
    void returnDestination(int* i);
            /* Code block that makes the elevator go up when it reach the botton
            if(hardware_read_floor_sensor(0)){
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
            }

            Code block that makes the elevator go down when it reach the top floor
            if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            }
*/