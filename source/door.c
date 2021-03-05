#include "door.h"
#include "hardware.h"
#include <sys/time.h>
void openDoor(){
    hardware_command_door_open(1);
};
float timedifference(struct timeval t0, struct timeval t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1.0+ (t1.tv_usec - t0.tv_usec) / 1.0;
}
void openTimedDoor(){
    struct timeval t0;
    struct timeval t1;
    if()
    gettimeofday(&t0, NULL);
    gettimeofday(&t1,NULL);
    float elapsed = timedifference(t0,t1);
    if (elapsed > 5){
        hardware_command_door_open(0);
    }

}