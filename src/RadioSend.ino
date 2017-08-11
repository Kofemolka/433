///*
//Example for different sending methods
//
//https://github.com/sui77/rc-switch/
//
//*/
//
//#include "RCSwitch.h"
//#include "msg.h"
//
//RCSwitch mySwitch = RCSwitch();
//
//void setup() {
//
//	Serial.begin(9600);
//
//	// Transmitter is connected to Arduino Pin #10  
//	mySwitch.enableTransmit(10);
//
//	// Optional set protocol (default is 1, will work for most outlets)
//	mySwitch.setProtocol(1);
//
//	// Optional set pulse length.
//	// mySwitch.setPulseLength(320);
//
//	// Optional set number of transmission repetitions.
//	mySwitch.setRepeatTransmit(4);
//
//}
//
//void loop() {
//
//	for (int i = 0; i < 4096; i++)
//	{
//		mySwitch.send(i, 12);
//	}
//	return;
//
//	/* See Example: TypeA_WithDIPSwitches */
//	mySwitch.switchOn("11111", "00010");
//	delay(1000);
//	mySwitch.switchOff("11111", "00010");
//	delay(1000);
//
//	/* Same switch as above, but using decimal code */
//	mySwitch.send(5393, 24);
//	delay(1000);
//	mySwitch.send(5396, 24);
//	delay(1000);
//
//	/* Same switch as above, but using binary code */
//	mySwitch.send("000000000001010100010001");
//	delay(1000);
//	mySwitch.send("000000000001010100010100");
//	delay(1000);
//
//	/* Same switch as above, but tri-state code */
//	mySwitch.sendTriState("00000FFF0F0F");
//	delay(1000);
//	mySwitch.sendTriState("00000FFF0FF0");
//	delay(1000);
//
//	delay(5000);
//}

int send_code_pin = 10;
//int send_code = 3061;// это код определенный методом перебора для моего шлагбаума

void setup()
{
	pinMode(send_code_pin, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
	for (int send_code = 0; send_code < 4096; send_code++) // этот цикл после того как код определен необходимо убрать
	{
		for (int j = 0; j <4; j++) // достаточно 4-х, но из-за помех поставил 7
		{
			digitalWrite(send_code_pin, HIGH); // стартовый импульс
			delayMicroseconds(700);
			digitalWrite(send_code_pin, LOW);
			for (int i = 12; i > 0; i--)
			{
				boolean bit_code = bitRead(send_code, i - 1);
				if (bit_code)
				{
					digitalWrite(send_code_pin, LOW); // единица
					delayMicroseconds(1400);
					digitalWrite(send_code_pin, HIGH);
					delayMicroseconds(700);
				}
				else
				{
					digitalWrite(send_code_pin, LOW); // ноль
					delayMicroseconds(700);
					digitalWrite(send_code_pin, HIGH);
					delayMicroseconds(1400);
				}
			}
			digitalWrite(send_code_pin, LOW); // пилотный период
			delayMicroseconds(25200);
		}

		delay(500);
	}

	digitalWrite(LED_BUILTIN, HIGH);
	for (;;);	
}