/**
 * @file 
 * @brief This module contains functions that 
 * handle the door and the timer that keeps it open for 5 seconds.
 *
 */

#pragma once
#include <sys/time.h>
/* Code to clear all lights given the obstruction signal 
            if(hardware_read_obstruction_signal()){
                hardware_command_stop_light(1);
                clear_all_order_lights();
            }
            else{
                hardware_command_stop_light(0);
            }
*/ 

/**
 * @brief This @c boolean is set to true when the timer has counted 5 seconds.
 * it is set to false otherwise. It lets the elevator module know when to abandon the DoorOpen state
 * **/
bool timeIsUp;

/**
 * @brief This function opens the door of the elevator. 
 * It also deals with problems such as the Stop button and the obstruction button being
 * pushed.
 * 
 * **/
void openTimedDoor();
