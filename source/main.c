#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include <stdbool.h>
static void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}
 enum State {Undefined, StandPlass, StoppMellomEtasje, Bevegelse, DørÅpen};
int main(){
    
    enum State state;
    state = Undefined;


    int error = hardware_init();

    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    int definedState = 0;
    while(1){
        //if(hardware_read_stop_signal()){
        //  hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        //  break;
        //}
        lookForOrders();
        switch(state){
            case Undefined : 

               undefinedManouver(state);
               if (definedState!=0){
                   state = StandPlass;
               }
                break;
            case StandPlass :
                stop();
                if (orderFound()){
                    state = Bevegelse;
                }
                break;
            case StoppMellomEtasje :
                if (orderFound()){
                    state = StandPlass;
                }
                break;
            case Bevegelse :
                kjør();
                if (atDestination()){
                    state = DørÅpen;
                }
                if (stop(state)){
                    state = StoppMellomEtasje;
                }
                break;
            case DørÅpen:
                if (!stop()){
                    openTimedDoor;
                    if (doorIsClose){
                        state = StandPlass;
                    }
                }
                else{
                openDoor();
                }
                break;

            default :
                
                break;
        };
    }
    return 0;
}
