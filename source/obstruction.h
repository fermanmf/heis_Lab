/* Code to clear all lights given the obstruction signal 
            if(hardware_read_obstruction_signal()){
                hardware_command_stop_light(1);
                clear_all_order_lights();
            }
            else{
                hardware_command_stop_light(0);
            }*/ 
int obs = 0;