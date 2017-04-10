#ifndef I2C_VPINS_PROTOCOL_DEF
#define I2C_VPINS_PROTOCOL_DEF

	#include <Arduino.h>
	#include <Wire.h>

	//I2C hardware port
	class I2CBranch:public portBranch {
	public:
		TwoWire& Wire;
		char serverId;//like i2c server or slave
		I2CBranch(TwoWire & wire,char id,char local,char sz=1);
		virtual void mode();
		virtual void in();
		virtual void out();
		virtual void io();
	};

	//virtual port over I2c (target can be any hardware or virtual port at server)
	class I2CServerBranch:public I2CBranch {
	private:
		void dispatch(char op);
	public:
		char hostPort;//host port nr
		I2CServerBranch(TwoWire & wire,char id,char local,char host,char sz=1);
		bool begin();
		virtual void mode();
		virtual void in();
		virtual void out();
	};
#endif
