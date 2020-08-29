#include <Parking.h>
#include <DigitalIO.h>
#include <LCD.h>

/***************Local variables********************/
static uint8_t parkingNrOfFreeParkingSpots;
static uint8_t parkingLastNrOfFreeParkingSpots;
/**************************************************/

/***************Local functions********************/
/**************************************************/

/***************External variables*****************/

/**************************************************/

/***************External functions*****************/
/**************************************************/

void parkingInit(void)
{
    digitalInit();
    lcdInit();
}

void parking_main(void)
{
   parkingNrOfFreeParkingSpots = digilatGetParkingSpotsStatus();         //process parking spot first
   if(parkingNrOfFreeParkingSpots != parkingLastNrOfFreeParkingSpots)
   {
       lcdAvailableParkingSpotsNr();
       parkingLastNrOfFreeParkingSpots = parkingNrOfFreeParkingSpots;
   }
}

