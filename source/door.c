#include "door.h"
#include "hardware.h"

void openDoor(){
    hardware_command_door_open(1);
};

void openTimedDoor(){
    hardware_command_door_open(1);
    
}