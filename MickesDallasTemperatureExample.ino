/*
 Name:		MickesDallasTemperatureExample.ino
 Created:	6/26/2015 5:50:31 AM
 Author:	Micke
*/

//Downloaded Libraries
#include <LedControl.h>
#include <DallasTemperature.h>
#include <OneWire.h>

//Mikes own Libraries
#include "MickesLedControl.h"
#include "MickeDallasTemperature.h"
#include "TemperatureDisplay.h"

//Pin nummer konfigurationen som enheterna är
//inkopplade på
#define LEDCONTROL_DATA_PIN 12
#define LEDCONTROL_CLOCK_PIN 11
#define LEDCONTROL_CS_PIN 10

#define ONE_WIRE_CONTROL_PIN 3

//Antal inkopplade MAX 7219 ledcontrol enheter
#define NUM_OF_LEDCONTROLS 1
#define NUM_OF_REMOTE_SENSORS 1

//Skapa det globala Micke Led control objektet
MickesLedControl MickeLC(LEDCONTROL_DATA_PIN, LEDCONTROL_CLOCK_PIN,
	LEDCONTROL_CS_PIN, NUM_OF_LEDCONTROLS);

//Skapa led display objekt.
TemperatureDisplay TempDisplay = TemperatureDisplay(0, 0, 0, MickeLC);

OneWire oWire(ONE_WIRE_CONTROL_PIN);
MickeDallasTemperature mDallasTemp(&oWire);


void setup() {
	Serial.begin(9600); //For debugging

	mDallasTemp.InitSensors();

	//Starta upp led displayen;
	MickeLC.initLedDisplay();
}

// the loop function runs over and over again until power down or reset
void loop() {
	float temp;
	temp = mDallasTemp.getSensorTempC(0);
	TempDisplay.showTemperature(temp);
	Serial.print("Temperature = ");
	Serial.println(temp);
	delay(1000);
}
