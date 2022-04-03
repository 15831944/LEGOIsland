#ifndef CSHADES_H
#define CSHADES_H

// PC I/O ports for LCD driver hardware
typedef enum {
  STEREO3D_PORT_LPT1=0,
  STEREO3D_PORT_LPT2,
  STEREO3D_PORT_LPT3,
  STEREO3D_PORT_LPT4,
  STEREO3D_PORT_COM1,
  STEREO3D_PORT_COM2,
  STEREO3D_PORT_COM3,
  STEREO3D_PORT_COM4,
  STEREO3D_PORT_NONE
} stereo3Dport;

typedef struct {
  long VSport;  // View synchronization I/O port
  long VSleft;  // Left/right/off bits patterns to write to I/O port
  long VSright;
  long VSoff;
} portInfo;

typedef struct 
{
  long view;     // Stereo view: 0 = left, 1 = right
  long flipLCDs;

  long VSport;   // View Synchronization I/O Port
  long VSleft;
  long VSright;
  long VSoff;
} vTimerData;

// Initialize the LCD timer and display systems
void initLCDsys(stereo3Dport sp=(stereo3Dport)0) ;

// Turn the LCD shutter system on and off
void LCDsOn(void);
void LCDsOff(void);

// Set both LCDs clear
void clearLCDs(void);

void FlipShades(void);

#endif


