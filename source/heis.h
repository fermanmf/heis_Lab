
/**
 * @file 
 * @brief This module contains functions that give instructions 
 * to the elevator and control at which state the elevator is at all times.
 */ 

#pragma once
/**
 * @brief This @c enum type keeps track of the possible states of the system.
 * **/
enum State {UndefinedState, AtRest, StoppBetweenFloors, Moving, DoorOpen};

/**
 * @brief This @c int  keeps track of the elevators current floor.
 * **/
int g_currentFloor;
/**
 * @brief This @c bool tells whether or not the @c goToDestinaiton() function has finished an order.
 * It is used to communicate to the order module that it can remove the order.  
 * **/
bool g_elevatorHasHandeledCurrentOrder;
/**
 * @brief This @c bool is true when the elevator moves up and false when it moves down. 
 * In the case of no movement the variable holds the latest direction.
 * **/
bool g_directionOfElevatorIsUp; 
/**
 * @brief This @c bool holds true when the obstruction button is active.
 * **/
bool g_obstructed;
/**
 * @brief This function deletes the orderqueu when the stopbutton is pushed . 
 * **/
void h_handleStopButton();
 /**
 * @brief This function initiates the hardware . 
 * **/
void h_initiateHardware();
 /**
 * @brief This function makes the elevator go to 
 * the current destination. When the elevator arrives a destination, 
 * the function changes the state of the system.
 * @param[in] currentDestination It is the destination passed by by the order module.
 * **/
void h_goToDestination(int currentDestination); 
 /**
 * @brief This function brings the elevator to a floor (a defined state).
 * If the elevator is initiated between two floors it always moves up.
 * **/

void h_goToDefinedState();
 /**
 * @brief This function checks if the stop-button is pushed.
 * @return 0 if the stopbutton is not pushed. 1 if it is.
 * **/

bool h_stopPushed();
 /**
 * @brief This function makes the elevator go to 
 * to either the StopBetweenFloors state or the DoorOpen state, but only
 * if the stopButton is pushed.
 * **/

void h_goToStopStateIfPushed();
/**
 * @brief Checks if the elevator is triggering any floorSensor
 * @return @c true if no floor sensor is triggered by the elevator. @c false otherwise.
 * **/

bool h_checkIfInbetween();
/**
 * @brief This function simply stops the movement of the elevator.
 * **/

void h_stopElevatorMovement();

//void h_setDestination();
/**
 * @brief This function makes the elevator go to 
 * to the StandPlass state if the timer of the door is finished.
 * **/
void h_goToAtRestStateIf(bool timeIsUp);
/**
 * @brief This function makes the elevator go to 
 * to the Bevegelse state, but only if @p queueIsEmpty is @c true.
 * @param[in] queueIsEmpty This variable is holding true if there are no orders. false otherwise.
 * **/
void h_goToMovingStateIf(bool queueIsEmpty);
/**
 * @brief This function simply returns the state of the system.
 * @return state of the system.
 * **/
enum State h_getState();
/**
 * @brief This function watches the global variable @c obstruction and makes 
 * sure it holds the correct value at all times.
 * **/
void h_updateObstructionVar();