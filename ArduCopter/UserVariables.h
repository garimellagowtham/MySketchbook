// agmatthews USERHOOKS
// user defined variables
//trying for 200Hz loop:
uint8_t Fifty_Hzcounter = 0;

uint16_t armpwm1;
uint16_t armpwm2;
uint16_t armpwm3;

// example variables used in Wii camera testing - replace with your own
// variables
#if WII_CAMERA == 1
WiiCamera           ircam;
int                 WiiRange=0;
int                 WiiRotation=0;
int                 WiiDisplacementX=0;
int                 WiiDisplacementY=0;
#endif


