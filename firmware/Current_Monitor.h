/*
 * Bazinga.h
 *
 *  Created on: Oct 1, 2015
 *      Author: travis
 */

#include "spark_wiring_i2c.h"
#include "spark_wiring_usbserial.h"
#include "spark_wiring.h"
 class CurrentMonitor{
 public:
	 CurrentMonitor(void);
	 void setAddress(int a0, int a1, int a2, int a3);

	 int readCurrent(int channel);

	 int readVoltage(int channel);

	 bool initialized = false;
 private:

 };
