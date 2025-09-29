#include "adc.h"
#include "can.h"
#include "ecu_sensor.h"
#include "msg_id2.h"
#include "uart.h"
#include "digital_keypad.h"

#define _XTAL_FREQ 20000000

unsigned int flag = 0;
unsigned int delay = 0;

uint16_t g_rpm;

int main() {

    // Initialize hardware modules
    init_digital_keypad();         // Initialize digital keypad for input
    init_adc();                    // Initialize ADC for analog data
    init_uart();                   // Initialize UART for serial communication
    //init_display();              // Display init is commented out
    init_can();                    // Initialize CAN communication

    char rpm[4];
    TRISB = TRISB & 0x3C;          // Configure PORTB direction (preserve certain bits)

    while (1) {

        int key = process_indicator(); // Get current indicator button pressed

        if (key == e_ind_left) {
            flag = 1;                  // Set flag for left indicator
        } else if (key == e_ind_right) {
            flag = 2;                  // Set flag for right indicator
        } else if (key == e_ind_off) {
            flag = 0;                  // Set flag for indicator OFF
        }

        // Handle left indicator blinking
        if (flag == 1) {
            RIGHT_IND_OFF();          // Ensure right indicator is off
            if (delay++ < 25) {
                LEFT_IND_ON();        // Turn on left indicator
            } else if (delay < 50) {
                LEFT_IND_OFF();       // Turn off left indicator
            } else {
                delay = 0;            // Reset delay counter
            }
        }

        // Handle right indicator blinking
        else if (flag == 2) {
            LEFT_IND_OFF();           // Ensure left indicator is off
            if (delay++ < 25) {
                RIGHT_IND_ON();       // Turn on right indicator
            } else if (delay < 50) {
                RIGHT_IND_OFF();      // Turn off right indicator
            } else {
                delay = 0;            // Reset delay counter
            }
        }

        // Turn off both indicators if flag is 0
        else if (flag == 0) {
            LEFT_IND_OFF();
            RIGHT_IND_OFF();
        }

        can_transmit(INDICATOR_MSG_ID, &flag, 1); // Send indicator status via CAN

        __delay_us(1000);             // Small delay for timing control

        g_rpm = get_rpm();            // Read RPM value from sensor

        // Convert RPM integer to ASCII characters
        rpm[0] = (g_rpm / 1000) % 10 + 48;
        rpm[1] = (g_rpm / 100) % 10 + 48;
        rpm[2] = (g_rpm / 10) % 10 + 48;
        rpm[3] = (g_rpm % 10) + 48;

        can_transmit(RPM_MSG_ID, rpm, 4); // Transmit RPM value over CAN

        __delay_us(4000);             // Delay between successive transmissions
    }
}
