/*
   Move the mouse in a small circle every N minutes.
   To keep the screensaver/screenlock from activating.
   in environments (corp/admin lock) that don't allow disabling screenlock (!)

   For teensy2
   
   by anon 12/6/2012
*/

#ifdef ARDUINO_AVR_DIGISPARK
#include <DigiMouse.h>
#endif
#ifdef CORE_TEENSY
#include "Mouse.h"
#include <keylayouts.h>
#endif

const long intervalsec = 6 * 60 ; // e.g. 15 * 60 = 15 minutes
const long speedms = 5; // how fast the circle motion (bigger==slower)
const long radius = 3;  // radius of circle, not sure what units

void mydelay( int d)
{
#ifdef ARDUINO_AVR_DIGISPARK
        DigiMouse.delay( d);
#else
	delay( d);
#endif

}

void mousemove( long x, long y)
{
#ifdef ARDUINO_AVR_DIGISPARK
	DigiMouse.moveX( x);
	DigiMouse.moveY( y);
#endif
#ifdef CORE_TEENSY
	Mouse.move(x,y);
#endif
}

// Move the mouse in a circle.
// R is not actually the radius--
// I can't say exactly what it is right now, but 
// if you give a bigger R, you get a bigger circle
void circle(int r)  
{
   int delta=60;
   double rad=0;
   double raddelta = 2*PI/delta;
      for ( ;rad < 2*PI; rad+=raddelta)
      {
          long x = r * cos(rad);
          long y = r * sin(rad);
          mousemove(x,y);
	  mydelay( speedms );
      }
}


void setup() 
{
	// give some time for USB to come up
	delay(2000);
#ifdef ARDUINO_AVR_DIGISPARK
	DigiMouse.begin();
#endif
#ifdef CORE_TEENSY
	// nothing necessary
#endif
	delay(2000);

}

long lasttime = -intervalsec * 1000L;
void loop() 
{
	if ( millis() - lasttime > (intervalsec * 1000L))
	{
		circle ( radius );
		lasttime = millis();
	}
 	mydelay( 1);  
}


/* digispark other
  // If not using plentiful DigiMouse.delay(), make sure to call
  // DigiMouse.update() at least every 50ms
  
  // move across the screen
  // these are signed chars
  DigiMouse.moveY(10); //down 10
  DigiMouse.delay(500);
  DigiMouse.moveX(20); //right 20
  DigiMouse.delay(500);
  DigiMouse.scroll(5);
  DigiMouse.delay(500);
  
  // or DigiMouse.move(X, Y, scroll) works
  
  // three buttons are the three LSBs of an unsigned char
  DigiMouse.setButtons(1<<0); //left click
  DigiMouse.delay(500);
  DigiMouse.setButtons(0); //unclick all
  DigiMouse.delay(500);

  //or you can use these functions to click
  DigiMouse.rightClick();
  DigiMouse.delay(500);
  DigiMouse.leftClick();
  DigiMouse.delay(500);
  DigiMouse.middleClick();
  DigiMouse.delay(500);

  //for compatability with other libraries you can also use DigiMouse.move(X, Y, scroll, buttons)
*/


