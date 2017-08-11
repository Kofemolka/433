#include "RCSwitch.h"
#include "msg.h"

RCSwitch mySwitch = RCSwitch();

void setup() {
	Serial.begin(9600);
	mySwitch.enableReceive(digitalPinToInterrupt(2));  // Receiver on interrupt 0 => that is pin #2
	
	pinMode(LED_BUILTIN, OUTPUT);

	digitalWrite(LED_BUILTIN, HIGH);
	delay(20);
	digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
	if (mySwitch.available()) {
		output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(), mySwitch.getReceivedProtocol());
		
		if (mySwitch.getReceivedValue() == 9831122)
		{
		//	Serial.println("OK");
			digitalWrite(LED_BUILTIN, HIGH);
			delay(20);
			digitalWrite(LED_BUILTIN, LOW);
		}

		mySwitch.resetAvailable();
	}
}