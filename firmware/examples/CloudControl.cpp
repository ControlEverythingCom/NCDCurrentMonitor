/* Includes ------------------------------------------------------------------*/
#include "application.h"
#include "spark_wiring_print.h"

SYSTEM_MODE(AUTOMATIC);

CurrentMonitor controller;

int current = 0;
int voltage = 0;

/* This function is called once at start up ----------------------------------*/
void setup()
{
	Serial.begin(115200);
	controller.setAddress(0,0,0,0);
	Particle.variable("Current", &current, INT);
	Particle.variable("Voltage", &voltage, INT);

}

/* This function loops forever --------------------------------------------*/
void loop()
{
	current = controller.readCurrent(1);
	voltage = controller.readVoltage(1);
	Serial.print("Current: ");
	Serial.println(current);
	Serial.print("Voltage: ");
	Serial.println(voltage);
	Particle.variable("Current", &current, INT);
	Particle.variable("Voltage", &voltage, INT);
	delay(2000);
}
