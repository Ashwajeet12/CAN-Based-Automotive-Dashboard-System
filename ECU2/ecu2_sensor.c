#include "ecu_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id2.h"
#include "uart.h"

volatile IndicatorStatus prev_ind_status = e_ind_off;
volatile IndicatorStatus cur_ind_status = e_ind_off;
volatile unsigned char led_state = 0;

uint16_t get_rpm()
{
    unsigned int rpm = read_adc(CHANNEL4);     // Read ADC value from channel 4 (RPM sensor)
    rpm = rpm * 5.86510264;                    // Scale raw ADC value to RPM
    if (rpm > 6000)
    {
        rpm = 6000;                            // Clamp RPM to max value of 6000
    }
    return rpm;                                // Return the calculated RPM
    //Implement the rpm function
}

uint16_t get_engine_temp()
{
    //Implement the engine temperature function
    // Placeholder for engine temperature logic
}

IndicatorStatus process_indicator()
{
    unsigned char key = read_digital_keypad(STATE_CHANGE); // Read current key press event

    if (key == SWITCH1)
        return e_ind_left;                    // Return left indicator if SWITCH1 pressed
    else if (key == SWITCH3)
        return e_ind_right;                   // Return right indicator if SWITCH3 pressed
    else if (key == SWITCH2)
        return e_ind_off;                     // Return off state if SWITCH2 pressed
}
