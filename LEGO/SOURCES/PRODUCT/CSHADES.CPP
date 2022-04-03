#include <windows.h>

#include <stdio.h>
#include <conio.h>
#include <dos.h>

//#include "CyberShades.h"
#include "CShades.h"

vTimerData vdata;

// Serial port display bits
#define SER_D_LEFT  0x1
#define SER_D_RIGHT 0x3
#define SER_D_OFF   0x0

// Parallel port display bits
#define PAR_D_LEFT  (0xff)
#define PAR_D_RIGHT (~(1<<2))
#define PAR_D_OFF   0x0


#define COM_OFFSET 0x4 // Offset to COM I/O pins

//static ushort * serPort = (ushort *)0x400; // Low memory address tables
//static ushort * parPort = (ushort *)0x408;


//---------------------------------------------------------------------------
void FlipShades(void) 
{

    // Flip LCD shutters and display pages
    vdata.view ^= 1;

    // Flip LCD shutters
    if (/*vdata.flipLCDs &&*/ vdata.VSport) 
    {
        if (vdata.view)
        {
            __asm 
            {
                mov dx, 0x378
                mov ax, PAR_D_RIGHT
                out dx, al
            }
        }
        else 
        {
            __asm 
            {
                mov dx, 0x0378
                mov ax, PAR_D_LEFT
                out dx, al
            }
        }
    }

}


//---------------------------------------------------------------------------
// Initialize the LCD shutter timer and display systems
void initLCDsys(stereo3Dport sp) 
{

    clearLCDs();

    // Set up I/O port to drive LCD hardware
    // AG: I use LPT1: only 
    vdata.VSport  = 0x0378;
    vdata.VSleft  = PAR_D_LEFT;
    vdata.VSright = PAR_D_RIGHT;
    vdata.VSoff   = PAR_D_OFF;

    clearLCDs();

} // initLCDsys


//---------------------------------------------------------------------------
void clearLCDs(void) 
{
    if (vdata.VSport)
    {
        __asm 
        {
            mov dx, 0x0378
            mov ax, PAR_D_OFF
            out dx, al
        }
    }
}


//---------------------------------------------------------------------------
void LCDsOn(void) 
{
  vdata.flipLCDs = 1;
}


//---------------------------------------------------------------------------

void LCDsOff(void) 
{
  vdata.flipLCDs = 0;
  clearLCDs();
}


