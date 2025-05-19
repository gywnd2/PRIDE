#include <main.h>
#include <Global.h>

void setup ()
{
    Serial.begin( SERIAL_BAUDRATE ); /* prepare for possible serial debug */
    serial_bt.begin("PRIDE_ESP32", true);

    storage.InitStorage();
    storage.UpdateSplashEEPROM();
    display.InitDisplay();
    dfp.InitMp3();
    welcome.InitWelcome();
    widget.InitWidget();
    obd.InitOBD();
    trip.InitTrip();

    Serial.println( "Setup done" );
}

void loop ()
{

}