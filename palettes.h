#include <FastLED.h>


enum EPalette : uint8_t
{
  OceanFoam,
  CaliSunset,
  Rainbow,
  PurpleFly,
  Clouds,
  Ocean,
  Max
  // To remove palettes from the run without removing their code, put them after max
};

// Gradient palette "bhw2_turq_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_turq.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( ocean_foam_gp ) {
    0,   1, 33, 95,
   38,   1,107, 37,
   76,  42,255, 45,
  127, 255,255, 45,
};

// Gradient palette "bhw1_01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

DEFINE_GRADIENT_PALETTE( cali_sunset_gp ) {
    0, 227,101,  3,
  117, 194, 18, 19,
  255,  92,  8,192};

// Gradient palette "purplefly_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/purplefly.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( purplefly_gp ) {
    0,   0,  0,  0,
   63, 239,  0,122,
  191, 252,255, 78,
  255,   0,  0,  0};



void SetPaletteFromEnum(CRGBPalette16& OutPalette, EPalette PaletteRequested)
{
  switch(PaletteRequested)
  {
    case EPalette::OceanFoam:
      OutPalette = ocean_foam_gp;
      break;
    case EPalette::CaliSunset:
      OutPalette = cali_sunset_gp;
      break;
    case EPalette::PurpleFly:
      OutPalette = purplefly_gp;
      break;
    case EPalette::Rainbow:
      OutPalette = RainbowColors_p;
      break;
    case EPalette::Clouds:
      OutPalette = CloudColors_p;
      break;
    case EPalette::Ocean:
      OutPalette = OceanColors_p;
      break;
  }
}