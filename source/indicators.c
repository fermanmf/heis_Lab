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

void h_setLightOnOrders() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (hardware_read_order(i, j)) {
            
                hardware_command_order_light(i, j, 1);

            }
  
        }
    }
};

void h_resetOrderLights() {
    for (int i = 0; i < 3; i++) {
        hardware_command_order_light(currentFloor, i, 0);
    }
};