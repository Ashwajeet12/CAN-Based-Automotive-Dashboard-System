#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"

volatile unsigned char led_state = LED_OFF, status = e_ind_off;

void handle_speed_data(uint8_t *data, uint8_t len)
{
    unsigned char sp = (data[0] / 10) + '0';      // Extract tens place of speed and convert to ASCII
    unsigned char spl = (data[0] % 10) + '0';     // Extract units place of speed and convert to ASCII
    clcd_print("SP",LINE1(0));                    // Display label "SP" on first line of LCD
    clcd_putch(sp, LINE2(1));                     // Display tens digit on second line
    clcd_putch(spl, LINE2(2));                    // Display units digit on second line
}

void handle_gear_data(uint8_t *data, uint8_t len)
{
    clcd_print("GR",LINE1(4));                    // Display label "GR" on first line of LCD
    clcd_putch(data[0], LINE2(4));                // Show current gear value on second line
}

void handle_rpm_data(uint8_t *data, uint8_t len)
{
    clcd_print("RPM",LINE1(8));                   // Display label "RPM" on first line
    int line = 7;                                  // Start position to display RPM digits
    for (int i = 0; i < len; i++)
    {
        clcd_putch(data[i], LINE2(line));         // Show each digit of RPM on second line
        line++;                                   // Move to next LCD position
    }
}

void handle_engine_temp_data(uint8_t *data, uint8_t len)
{
    // Engine temperature logic can be implemented here
}

void handle_indicator_data(uint8_t *data, uint8_t len)
{
    clcd_print("IND",LINE1(12));                  // Show label "IND" for indicator status
    if (data[0] == 0)
    {
        clcd_print("OFF", LINE2(12));             // Show "OFF" if no indicator is active
        RIGHT_IND_OFF();                          // Turn off right indicator
        LEFT_IND_OFF();                           // Turn off left indicator
    }
    else if (data[0] == 1)
    {
        clcd_print("LFT", LINE2(12));             // Show "LFT" for left indicator
        RIGHT_IND_OFF();                          // Turn off right indicator
        LEFT_IND_ON();                            // Turn on left indicator
    }
    else if (data[0] == 2)
    {
        clcd_print("RHT", LINE2(12));             // Show "RHT" for right indicator
        LEFT_IND_OFF();                           // Turn off left indicator
        RIGHT_IND_ON();                           // Turn on right indicator
    }
}

void process_canbus_data()
{
    uint16_t msg_id;
    uint8_t data[8];
    uint8_t len;

    can_receive(&msg_id, data, &len);             // Receive message from CAN bus

    switch (msg_id)
    {
        case SPEED_MSG_ID:
            handle_speed_data(data, len);         // Process speed-related data
            break;

        case GEAR_MSG_ID:
            handle_gear_data(data, len);          // Process gear-related data
            break;

        case RPM_MSG_ID:
            handle_rpm_data(data, len);           // Process RPM-related data
            break;

        case ENG_TEMP_MSG_ID:
            handle_engine_temp_data(data, len);   // Process engine temperature data
            break;

        case INDICATOR_MSG_ID:
            handle_indicator_data(data, len);     // Process indicator (turn signal) status
            break;
    }
}
