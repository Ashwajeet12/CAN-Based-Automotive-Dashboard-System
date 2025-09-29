

#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

unsigned int count = 1;
uint16_t get_speed()
{
    // Implement the speed function
    unsigned int speed = read_adc(CHANNEL4);
    speed = speed / 10.23;
    if(speed > 99)
    {
        speed = 99;
    }
    return speed;
}

unsigned char get_gear_pos()
{
    unsigned char gear[] = {'R','N','1','2','3','4','5','C'};
    unsigned char key = read_digital_keypad(STATE_CHANGE);

    // If collision happens, lock the gear to 'C'
   
    // Ignore gear changes if in collision state
    
        if(key == GEAR_UP)
        {
            if(count < 6)
            {
                count++;
            }
             if(count == 7)
            {
                count = 1;
            }
        }
        else if(key == GEAR_DOWN)
        {
            if(count == 7)
            {
                count = 1;
            }
            else if(count > 0)
            {
                count--;
            }
             
        }
  

    if(key == COLLISION)
    {
        count = 7;
    }
    return gear[count];
}
