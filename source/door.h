/**
 * @file 
 * @brief This module contains functions that 
 * handle the door and the timer that keeps it open for 5 seconds.
 *
 */

#pragma once

#include <sys/time.h>

/**
 * @brief This function lets the elevator module know when to abandon the DoorOpen state
 * @return @c true when the door has been open for 3 seconds. @c false otherwise. 
 * **/
bool d_timeIsUp();
/**
 * @brief This func sets the variable timeIsUp that belongs to door.c to false. Used by the elevator module.
 * **/
void d_resetTimIsUpVar();
/**
 * @brief This function opens the door of the elevator. 
 * It also deals with problems such as the Stop button and the obstruction button being
 * pushed.
 * 
 * **/
void d_openTimedDoor();
