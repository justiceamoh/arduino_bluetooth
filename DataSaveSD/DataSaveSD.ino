/*
Author: Justice
Date: 01/11/13
Description: Sketch for reading/writing data to microSD card using SD shield. 
             Based on SdFat Library by Bill Greiman, adapted from Sparkfun SD tutorial   
 */
 
//Add the SdFat Libraries
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <ctype.h>

//Data structures to be used by SdFat Library
Sd2Card card;
SdVolume volume;
SdFile root;
SdFile file;

char fname[] = "Image.txt";     //Create an array that contains the name of our file.
char contents[256];             //This will be a data buffer for writing contents to the file.
char in_char=0;
int index=0;                    //Index will keep track of our position within the contents buffer.

void setup(void)
{  
    Serial.begin(9600);        //Start a serial connection.
    pinMode(10, OUTPUT);       //Pin 10 must be set as an output for the SD communication to work.
    card.init();               //Initialize the SD card and configure the I/O pins.
    volume.init(card);         //Initialize a volume on the SD card.
    root.openRoot(volume);     //Open the root directory in the volume. 
}


void loop(void){    
    file.open(root, fname, O_CREAT | O_APPEND | O_WRITE);    //Open or create the file 'name' in 'root' for writing to the end of the file.
    sprintf(contents, "Millis: %d    ", millis());    //Copy the letters 'Millis: ' followed by the integer value of the millis() function into the 'contents' array.
    file.print(contents);    //Write the 'contents' array to the end of the file.
    file.close();            //Close the file.
    
    file.open(root, fname, O_READ);    //Open the file in read mode.
    in_char=file.read();              //Get the first byte in the file.
    //Keep reading characters from the file until we get an error or reach the end of the file. (This will output the entire contents of the file).
    while(in_char >=0){            //If the value of the character is less than 0 we've reached the end of the file.
        Serial.print(in_char);    //Print the current character
        in_char=file.read();      //Get the next character
    }
    file.close();    //Close the file
    delay(1000);     //Wait 1 second before repeating the process.
}




