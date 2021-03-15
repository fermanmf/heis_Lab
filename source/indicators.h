#pragma once
 
 void h_updateCurrentFloor();
 
 
 /*Lights are set and cleared like this: 
            for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
                //Internal orders 
                if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                    hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
                }

                //Orders going up 
                if(hardware_read_order(f, HARDWARE_ORDER_UP)){
                    hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
                }

                //Orders going down 
                if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
                    hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
                }
            } 


// All buttons must be polled, like this: 
            for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
                if(hardware_read_floor_sensor(f)){
                    hardware_command_floor_indicator_on(f);
                }
            }
*/