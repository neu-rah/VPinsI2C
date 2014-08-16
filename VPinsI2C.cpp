#include <virtual_pins.h>
#include <Arduino.h>
#include "VPinsI2C.h"
#include <Wire.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////
I2CBranch::I2CBranch(TwoWire & wire,char id,char local,char sz)
	:Wire(wire),serverId(id),portBranch(local,sz) {
}

void I2CBranch::io() {in();out();}
void I2CBranch::mode() {}//TODO: see PCA9557, derive the class to support specific hardware or family
void I2CBranch::in() {}//TODO: test i2c input shift registers...

void I2CBranch::out() {
  Wire.beginTransmission(serverId);
  for(int n=localPort;n<localPort+size;n++)
    while (Wire.write(*portOutputRegister(n))!=1);
  Wire.endTransmission(serverId);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
I2CServerBranch::I2CServerBranch(TwoWire & wire,char id,char local,char host,char sz):hostPort(host),I2CBranch(wire,id,local,sz) {}

bool I2CServerBranch::begin() {
	//wait for server ready
	do Wire.beginTransmission(serverId);
	while(Wire.endTransmission());
}

void I2CServerBranch::mode() {dispatch(0b00);}
void I2CServerBranch::in() {
	char op=0b10;
  Wire.beginTransmission(serverId);
  Wire.write((hostPort<<2)|op);//codify operation on lower 2 bits
	int nbytes=Wire.requestFrom(serverId, 1);
  	*(portInputRegister(localPort))=Wire.read();
  Wire.endTransmission(serverId);
}
void I2CServerBranch::out() {dispatch(0b01);}

//op is port data info (3 bytes) index, avr ports compatible
void I2CServerBranch::dispatch(char op) {
	//Serial.print("i2c dispatch ");
	//Serial.println(op,BIN);
  Wire.beginTransmission(serverId);
  Wire.write((hostPort<<2)|op);//codify operation on lower 2 bits
  for(int n=0;n<size;n++) {
  	Wire.write(*(portModeRegister(localPort+n)+op));
  }
  Wire.endTransmission(serverId);
}


