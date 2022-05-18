#include <FastLED.h>


enum EPalette : uint8_t
{
  OceanFoam,
  CaliSunset,
  Rainbow,
  Max
};

// Gradient palette "bhw2_turq_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_turq.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( gp_ocean_foam ) {
    0,   1, 33, 95,
   38,   1,107, 37,
   76,  42,255, 45,
  127, 255,255, 45,
};

// Gradient palette "bhw1_01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

DEFINE_GRADIENT_PALETTE( gp_cali_sunset ) {
    0, 227,101,  3,
  117, 194, 18, 19,
  255,  92,  8,192};


void SetPaletteFromEnum(CRGBPalette16& OutPalette, EPalette PaletteRequested)
{
  switch(PaletteRequested)
  {
    case EPalette::OceanFoam:
      OutPalette = gp_ocean_foam;
      break;
    case EPalette::CaliSunset:
      OutPalette = gp_cali_sunset;
      break;
    case EPalette::Rainbow:
      OutPalette = RainbowColors_p;
      break;
  }
}