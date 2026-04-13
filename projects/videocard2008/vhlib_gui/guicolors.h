#define VHRGB(A,R,G,B) ((A<<6) + (R<<4) + (G<<2) + B)

#define VHCOLOR_WHITE     VHRGB(3,3,3,3)
#define VHCOLOR_BLACK     VHRGB(0,0,0,0)
#define VHCOLOR_YELLOW    VHRGB(3,3,3,0)
#define VHCOLOR_RED       VHRGB(3,3,0,0)
#define VHCOLOR_RED0      VHRGB(1,3,0,0)
#define VHCOLOR_BLUE      VHRGB(1,0,0,3)
