/***********************************************************************
 * Project      :     tiny32_SCD41
 * Description  :     this code is template source code Interface test
 *                    between tiny32 and The tiny32_SCD41 CO₂
 *                    Humidity and Temperature Sensor - SCD41 (Qwiic)
 * Hardware     :     tiny32_v4
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     21/10/2024
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     +66 89-140-7205
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>
#include <esp_task_wdt.h>
#include <stdio.h>
#include <stdint.h>
#include <Wire.h>
#include "SparkFun_SCD4x_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD4x

/**************************************/
/*          Firmware Version          */
/**************************************/
String version = "1.0";

/**************************************/
/*          Header project            */
/**************************************/
void header_print(void)
{
    Serial.printf("\r\n***********************************************************************\r\n");
    Serial.printf("* Project      :     tiny32_SCD41\r\n");
    Serial.printf("* Description  :     this code is template source code Interface test  \r\n");
    Serial.printf("*                    between tiny32 and The tiny32_SCD41 CO₂ Humidity and Temperature Sensor - SCD41 (Qwiic) \r\n");
    Serial.printf("* Hardware     :     tiny32_v4\r\n");
    Serial.printf("* Author       :     Tenergy Innovation Co., Ltd.\r\n");
    Serial.printf("* Date         :     22/06/2023\r\n");
    Serial.printf("* Revision     :     %s\r\n", version);
    Serial.printf("* Rev1.0       :     Origital\r\n");
    Serial.printf("* website      :     http://www.tenergyinnovation.co.th\r\n");
    Serial.printf("* Email        :     uten.boonliam@tenergyinnovation.co.th\r\n");
    Serial.printf("* TEL          :     +66 89-140-7205\r\n");
    Serial.printf("***********************************************************************/\r\n");
}

/**************************************/
/*        define object variable      */
/**************************************/
tiny32_v3 mcu;
SCD4x mySensor;

/**************************************/
/*   MultiTasking function define     */
/**************************************/

/**************************************/
/*            GPIO define             */
/**************************************/

/**************************************/
/*       Constand define value        */
/**************************************/
#define WDT_TIMEOUT 10

/**************************************/
/*       eeprom address define        */
/**************************************/

/**************************************/
/*        define global variable      */
/**************************************/

/**************************************/
/*           define function          */
/**************************************/

/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    Serial.begin(115200);
    header_print();

    Serial.println(F("SCD4x Example"));
    Wire.begin();

    // mySensor.enableDebugging(); // Uncomment this line to get helpful debug messages on Serial

    //.begin will start periodic measurements for us (see the later examples for details on how to override this)
    if (mySensor.begin() == false)
    {
        Serial.println(F("Sensor not detected. Please check wiring. Freezing..."));
        while (1)
            ;
    }

    Serial.print("Configuring WDT...");
    esp_task_wdt_init(WDT_TIMEOUT, true); // enable panic so ESP32 restarts
    esp_task_wdt_add(NULL);
    Serial.println("done");
    mcu.TickBuildinLED(1);
    mcu.buzzer_beep(2);
}

/***********************************************************************
 * FUNCTION:    loop
 * DESCRIPTION: loop process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void loop()
{
    if (mySensor.readMeasurement()) // readMeasurement will return true when fresh data is available
    {
        Serial.println();

        Serial.print(F("CO2(ppm):"));
        Serial.print(mySensor.getCO2());

        Serial.print(F("\tTemperature(C):"));
        Serial.print(mySensor.getTemperature(), 1);

        Serial.print(F("\tHumidity(%RH):"));
        Serial.print(mySensor.getHumidity(), 1);

        Serial.println();
    }
    else
        Serial.print(F("."));
    delay(1000);

    esp_task_wdt_reset();
}
