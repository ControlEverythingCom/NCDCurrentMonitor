/*
 * Bazinga.cpp
 *
 *  Created on: Oct 1, 2015
 *      Author: travis
 */
#include "Current_Monitor.h"

int address = 0x2A;

CurrentMonitor::CurrentMonitor(){}

void CurrentMonitor::setAddress(int a0, int a1, int a2, int a3){
	address = 0x2A;
	int retrys = 0;
	if(a0 == 1){
		address = address | 1;
	}
	if(a1 == 1){
		address = address | 2;
	}
	if(a2 == 1){
		address = address | 4;
	}
	if(a3 == 1){
		address = address | 8;
	}
    //Start I2C port
    Wire.begin();
    //Open connection to specified address
    retryAddress1:
    Wire.beginTransmission(address);
    //Set all channels to outputs
    //Determine if device is present at that address
    int status = Wire.endTransmission();
    if(status != 0){
        if(retrys < 3){
    #ifdef LOGGING
            Serial.println("Retry set address command");
    #endif
            retrys++;
            goto retryAddress1;
        }else{
    #ifdef LOGGING
            Serial.println("Set Address failed");
    #endif
            initialized = false;
            retrys = 0;
        }

    }else{
//         Serial.println("Command Successful");
        initialized = true;
        retrys = 0;
    }
}

int CurrentMonitor::readCurrent(int channel){
	Wire.beginTransmission(address);
	Wire.write(1);
	Wire.write(1);
	int status = Wire.endTransmission();
	if(status != 0){
		Serial.println("Something went wrong");
	}
	delay(100);
	Wire.requestFrom(address, 4);
	delay(100);
//	Serial.print("available bytes in wire: ");
//	Serial.println(Wire.available());
	int channelNumber = Wire.read();
	int MSB1 = Wire.read();
	int MSB = Wire.read();
	int LSB = Wire.read();
//	Serial.print("channel: ");
//	Serial.println(channelNumber);
//	Serial.print("MSB: ");
//	Serial.println(MSB);
//	Serial.print("LSB: ");
//	Serial.println(LSB);
	int val = (MSB1*65536)+(MSB*256)+LSB;
	return val;
}

int CurrentMonitor::readVoltage(int channel){
	Wire.beginTransmission(address);
	Wire.write(2);
	Wire.write(8);
	int status = Wire.endTransmission();
	if(status != 0){
		Serial.println("Something went wrong");
	}
	delay(100);
	Wire.requestFrom(address, 4);
	delay(100);
	Serial.print("available bytes in wire: ");
	Serial.println(Wire.available());
	int channelNumber = Wire.read();
	int MSB1 = Wire.read();
	int MSB = Wire.read();
	int LSB = Wire.read();
	int val = (MSB1*65536)+(MSB*256)+LSB;
	return val;
}

void CurrentMonitor::readCalibration(){
	Wire.beginTransmission(address);
	Wire.write(2);
	Wire.write(1);
	int status = Wire.endTransmission();
	if(status != 0){
		Serial.println("Something went wrong");
	}
	delay(100);
	Wire.requestFrom(address, 3);
	delay(100);
	int first = Wire.read();
	int second = Wire.read();
	int third = Wire.read();
	Serial.print(first);
	Serial.print(", ");
	Serial.print(second);
	Serial.print(", ");
	Serial.println(third);
}



