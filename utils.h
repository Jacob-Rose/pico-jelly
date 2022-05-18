#include <FastLED.h>

void toggleOnboardLED(bool state)
{
  pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, state ? HIGH : LOW);
}