#include "stdbool.h"
#include "indicators.h"
#include "hardware.h"
#include "heis.h"

void h_updateCurrentFloor(){
   for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_floor_sensor(f)){
            hardware_command_floor_indicator_on(f);
            currentFloor = f;
        }
    }
}
