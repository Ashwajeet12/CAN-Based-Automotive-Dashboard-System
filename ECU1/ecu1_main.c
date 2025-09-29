

#define _XTAL_FREQ 20000000

#include <xc.h>
#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"

void main(void) {
    // Initialize all required modules
    init_digital_keypad();
    init_adc();
    init_uart();
    init_can();
    
    puts("Welcome to dashboard, press any key to continue\n\r");


    uint8_t data;
    char gear;

    while (1) {
        // Get speed value and transmit over CAN
        uint16_t speed = get_speed(); // e.g., 85
        data = (uint8_t) speed; // CAN frame data is byte-sized
        can_transmit(SPEED_MSG_ID, &data, 1);
        __delay_us(1000);

        // Get gear and transmit over CAN
        gear = get_gear_pos();
        
        can_transmit(GEAR_MSG_ID, &gear, 1);
        __delay_us(1000);

        // Display over UART
//        puts("speed: ");
//        putch((speed / 10) + '0');
//        putch((speed % 10) + '0');
//        puts(" gear: ");
//        putch(gear);
//        puts("\r");
    }
}
