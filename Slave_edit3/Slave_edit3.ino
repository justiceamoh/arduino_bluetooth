
 
#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 6
#define TxD 7                  // Software serial pins


//define variables to hold the integer value of the recived data
int datain=0;

 
SoftwareSerial blueToothSerial(RxD,TxD);

void setupBlueToothConnection()
{
  blueToothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  blueToothSerial.print("\r\n+STNA=SeeedBTSlave\r\n"); //set the bluetooth name as "SeeedBTSlave"
  blueToothSerial.print("\r\n+STPIN=0000\r\n");//Set SLAVE pincode"0000"
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  blueToothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
  Serial.println("The slave bluetooth is inquirable!");
  delay(2000); // This delay is required.
  blueToothSerial.flush();
}
 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBlueToothConnection(); 
} 
 
//Checks if the response "OK" is received.
void CheckOK(){
  char a,b;
  while(1){
    if(int len = blueToothSerial.available()){
      a = blueToothSerial.read();
      if('O' == a){
        b = blueToothSerial.read();
        if('K' == b){
          Serial.println("BLUETOOTH OK");
          while( (a = blueToothSerial.read()) != -1){
            Serial.print(a);
          }
          break;
        }
      }
    }
  }
  while( (a = blueToothSerial.read()) != -1){
    Serial.print(a);
  }
} 


//Send the command to Bluetooth Bee
void sendBlueToothCommand(char command[]){
    blueToothSerial.print(command);
    CheckOK();   
}



void loop() 
{ 
  char recvChar;
  while(1){
    if(blueToothSerial.available()){//check if there's any data sent from the remote bluetooth shield
      recvChar = blueToothSerial.read();
      Serial.print(recvChar);
    }
    if(Serial.available()){//check if there's any data sent from the local serial terminal, you can add the other applications here
      recvChar  = Serial.read();
      blueToothSerial.print(recvChar);
    }
    
    if(recvChar=='q') 
      break;
  }
  
  blueToothSerial.flush();
  delay(2000);

      
//      blueToothSerial.println("The following data was recived from AI proccessed by the arduino and sent back");
//      blueToothSerial.print("Datain: ");
//      blueToothSerial.println(datain,DEC);
  
} 
 



