
/**
 * @file 
 * @brief This module contains functions that give instructions 
 * to the elevator and control at which state the elevator is at all times.
 */

#pragma once

    enum State {UndefinedState, StandPlass, StoppMellomEtasje, Bevegelse, DoorOpen};

    int currentFloor;
    bool m_orderDone;
    bool m_currentMomentumDir; 
    bool obstruction;

    void h_initiateHardware();
    void h_goToDestination(int currentDestination); 
    void h_goToDefinedState();
    bool h_stopPushed();
    void h_goToStopState();
    bool h_checkIfInbetween();
    void h_stopElevatorMovement();
    void h_setDestination();
    void h_updateCurrentFloor();
    void h_goToStandPlass(bool timeIsUp);
    void h_goToBevegelse(bool queueIsEmpty);
    enum State h_getState();