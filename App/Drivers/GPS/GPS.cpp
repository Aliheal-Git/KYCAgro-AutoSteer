#include "GPS.hpp"
#include "CANSPI.h"

GPS::GPS() {
    CANSPI_Initialize();
}

void GPS::receiveGPSData() {
    if(CANSPI_Receive(&rxMessage)){
        if (rxMessage.frame.id == VALVE_ID){
            if(rxMessage.frame.dlc == 0x08){
                uint16_t valveStates = 0;
                valveStates = (uint16_t)rxMessage.frame.data6<<8;
                valveStates |= rxMessage.frame.data7;
                for (uint8_t i = 0;  i < MAX_VALVE_COUNT; i++)
                {
                    if (valveStates&(1<<i))
                        valveStatus[(MAX_VALVE_COUNT - 1) - i] = true;
                    else
                        valveStatus[(MAX_VALVE_COUNT - 1) - i] = false;
                }
            }
        }
        else if (rxMessage.frame.id == SPEED_ID){
            uint16_t tempSpeed = 0;
            tempSpeed = (uint16_t)rxMessage.frame.data0<<8;
            tempSpeed |= rxMessage.frame.data1;
            tempSpeed -= (++tempSpeed)%10;
            speed = tempSpeed / 100.0f;
        }
    }
}