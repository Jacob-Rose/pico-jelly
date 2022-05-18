#include <FastLED.h>

#include "palettes.h"
#include "utils.h"

#define LEG_LED_COUNT 54
#define HEAD_TOP_SIDE_LED_COUNT 30
#define HEAD_BOTTOM_SIDE_LED_COUNT 26
#define HEAD_LED_COUNT HEAD_TOP_SIDE_LED_COUNT + HEAD_BOTTOM_SIDE_LED_COUNT

#define NUM_LEGS 12

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

#define UPDATES_PER_SECOND 60


CRGB legLEDs[NUM_LEGS][LEG_LED_COUNT];
CRGB headLEDs[3][HEAD_LED_COUNT];

#pragma region Pins
#define LEG1PIN 1
#define LEG2PIN 2
#define LEG3PIN 3
#define LEG4PIN 4
#define LEG5PIN 5
#define LEG6PIN 6
#define LEG7PIN 7
#define LEG8PIN 8
#define LEG9PIN 9
#define LEG10PIN 10
#define LEG11PIN 11
#define LEG12PIN 12

#define HEADSIDE1PIN 13
#define HEADSIDE2PIN 14
#define HEADSIDE3PIN 15
#pragma endregion


struct FPaletteCycleVars
{
  bool ShouldAutoSwapPalettes = true;
  float TimeBetweenPaletteSwapping = 5.0f;

  absolute_time_t TimeForNextPaletteSwap;
} PaletteCycleVars;

enum EPattern
{
  PaletteCycle,
  HueCycle,
};

uint8_t indexOffset = 0;

EPattern currentPattern = EPattern::PaletteCycle;

CRGBPalette16 currentPalette(CRGB::Black);
CRGBPalette16 targetPalette = gp_ocean_foam;
EPalette currentPaletteType = EPalette::OceanFoam;

// DA JELLY TOTEM CODE

void setup() 
{
  #pragma region Pins
  FastLED.addLeds<LED_TYPE, LEG1PIN, COLOR_ORDER>(legLEDs[0], 0, LEG_LED_COUNT);
  FastLED.addLeds<LED_TYPE, LEG2PIN, COLOR_ORDER>(legLEDs[1], 0, LEG_LED_COUNT);
  FastLED.addLeds<LED_TYPE, LEG3PIN, COLOR_ORDER>(legLEDs[2], 0, LEG_LED_COUNT);
  FastLED.addLeds<LED_TYPE, LEG4PIN, COLOR_ORDER>(legLEDs[3], 0, LEG_LED_COUNT);
  FastLED.addLeds<LED_TYPE, LEG5PIN, COLOR_ORDER>(legLEDs[4], 0, LEG_LED_COUNT);
  FastLED.addLeds<LED_TYPE, LEG6PIN, COLOR_ORDER>(legLEDs[5], 0, LEG_LED_COUNT);
  FastLED.addLeds<LED_TYPE, LEG7PIN, COLOR_ORDER>(legLEDs[6], 0, LEG_LED_COUNT);
  FastLED.addLeds<LED_TYPE, LEG8PIN, COLOR_ORDER>(legLEDs[7], 0, LEG_LED_COUNT);
  FastLED.addLeds<LED_TYPE, LEG9PIN, COLOR_ORDER>(legLEDs[8], 0, LEG_LED_COUNT);
  FastLED.addLeds<LED_TYPE, LEG10PIN, COLOR_ORDER>(legLEDs[9], 0, LEG_LED_COUNT);
  FastLED.addLeds<LED_TYPE, LEG11PIN, COLOR_ORDER>(legLEDs[10], 0, LEG_LED_COUNT);
  FastLED.addLeds<LED_TYPE, LEG12PIN, COLOR_ORDER>(legLEDs[11], 0, LEG_LED_COUNT);

  FastLED.addLeds<LED_TYPE, HEADSIDE1PIN, COLOR_ORDER>(headLEDs[0], 0, HEAD_TOP_SIDE_LED_COUNT + HEAD_BOTTOM_SIDE_LED_COUNT);
  FastLED.addLeds<LED_TYPE, HEADSIDE2PIN, COLOR_ORDER>(headLEDs[1], 0, HEAD_TOP_SIDE_LED_COUNT + HEAD_BOTTOM_SIDE_LED_COUNT);
  FastLED.addLeds<LED_TYPE, HEADSIDE3PIN, COLOR_ORDER>(headLEDs[2], 0, HEAD_TOP_SIDE_LED_COUNT + HEAD_BOTTOM_SIDE_LED_COUNT);
#pragma endregion

  FastLED.setBrightness(255);

  toggleOnboardLED(true);


  PaletteCycleVars.TimeForNextPaletteSwap = make_timeout_time_ms(static_cast<uint32_t>(PaletteCycleVars.TimeBetweenPaletteSwapping * 1000));
}

void loop() {
  // put your main code here, to run repeatedly:

  switch(currentPattern)
  {
    case EPattern::HueCycle:
      Update_HueCycle();
      break;
    case EPattern::PaletteCycle:
      Update_PaletteCycle();
      break;
  }
  indexOffset++;

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void Update_PaletteCycle()
{
  
  //cycle palettes on timer
  if(absolute_time_diff_us(get_absolute_time(), PaletteCycleVars.TimeForNextPaletteSwap) < 0)
  {
    currentPaletteType = (EPalette)(currentPaletteType + 1);
    if(currentPaletteType == EPalette::Max)
    {
      currentPaletteType = (EPalette)0;
    }
    SetPaletteFromEnum(targetPalette, currentPaletteType);
    Serial.write(currentPaletteType);
    PaletteCycleVars.TimeForNextPaletteSwap = make_timeout_time_ms(static_cast<uint32_t>(PaletteCycleVars.TimeBetweenPaletteSwapping * 1000));
  }

  uint8_t maxChanges = 40; 
  nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);

  for(int legIndex = 0; legIndex < NUM_LEGS; ++legIndex)
  {
    for(int ledIndex = 0; ledIndex < LEG_LED_COUNT; ++ledIndex)
    {
      legLEDs[legIndex][ledIndex] = ColorFromPalette( currentPalette, indexOffset + sin8(ledIndex*4), 255);
    }
  }

  for(int legIndex = 0; legIndex < 3; ++legIndex)
  {
    for(int ledIndex = 0; ledIndex < HEAD_LED_COUNT; ++ledIndex)
    {
      headLEDs[legIndex][ledIndex] = ColorFromPalette( currentPalette, indexOffset + sin8(ledIndex*4), 255);
    }
  }
}

void Update_HueCycle()
{
  CRGB Color = CHSV(indexOffset, 255, 255);

  for(int legIndex = 0; legIndex < NUM_LEGS; ++legIndex)
  {
    for(int ledIndex = 0; ledIndex < LEG_LED_COUNT; ++ledIndex)
    {
      legLEDs[legIndex][ledIndex] = Color;
    }
  }

  for(int legIndex = 0; legIndex < 3; ++legIndex)
  {
    for(int ledIndex = 0; ledIndex < HEAD_LED_COUNT; ++ledIndex)
    {
      headLEDs[legIndex][ledIndex] = Color;
    }
  }
}
