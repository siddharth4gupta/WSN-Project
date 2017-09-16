#include <SoftwareSerial.h>

SoftwareSerial GPRS(7, 8);  


int bluetoothTx = 13;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 12;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothRx, bluetoothTx);

String rcv_data;
String bt_rcv;
int bt_count=0;

String t_old; 
String p_old; 
String h_old; 
String temp,humid,pressure; 

#define cmd1 "AT+SAPBR=3,1,\"APN\",\"epc.t-mobile.com\"\r"
#define cmd2 "AT+SAPBR=3,1,\"USER\",\"guest\"\r" 
#define cmd3 "AT+SAPBR=3,1,\"PWD\",\"guest\"\r" 
#define cmd4 "AT+SAPBR=1,1\r"
#define cmd5 "AT+HTTPINIT\r"
#define cmd6 "AT+HTTPPARA=\"URL\",\"wsn-keer.c9users.io/?h=45\"\r"
#define cmd7 "AT+HTTPPARA=\"PROPORT\",\"8080\"\r"
#define cmd8 "AT+HTTPACTION=0\r"
#define cmd9 "AT+HTTPREAD=0,100\r"



void setup() {
  // put your setup code here, to run once:
  GPRS.begin(2400);               // the GPRS baud rate   
  Serial.begin(9600);
  bluetooth.begin(9600);

  GPRS.write(cmd1);
  Serial.println(cmd1); 
  delay(1000);
  
  GPRS.write(cmd2);
  Serial.println(cmd2); 
  delay(1000);
  
  GPRS.write(cmd3);
  Serial.println(cmd3); 
  delay(1000);

  GPRS.write(cmd4);
  Serial.println(cmd4); 
  delay(1000);
  
  GPRS.write(cmd5);
  Serial.println(cmd5); 
  delay(1000);

}

void loop() {

  
  if (GPRS.available()){         // if date is comming from softwareserial port ==> data is comming from gprs shield

    rcv_data = GPRS.readString();
    Serial.print(rcv_data);

  }

  if (Serial.available()){         // if data is available on hardwareserial port ==> data is comming from PC or notebook
     GPRS.write(Serial.read());  
  }


  bluetooth.listen();

  if (bt_count==0){
    

      if (bluetooth.available()){
    
        t_old=temp;
        p_old=pressure;
        h_old=humid;
    
        bt_rcv = bluetooth.readString();
        Serial.println(bt_rcv);
        //Serial.println("bt part");
    
        
        int commaIndex = bt_rcv.indexOf(',');
        //  Search for the next comma just after the first
        int secondCommaIndex = bt_rcv.indexOf(',', commaIndex+1);
        temp = bt_rcv.substring(0, commaIndex);
        humid = bt_rcv.substring(commaIndex+1, secondCommaIndex);
        pressure = bt_rcv.substring(secondCommaIndex+1);
        String pa = "AT+HTTPPARA=\"URL\",\"wsn-keer.c9users.io";
        
        if(temp!=t_old)
        {
        Serial.println("New temp = "+temp);
        String path1 = pa+"/?t="+temp+"\"\r";
        int str_len = path1.length() + 1;
        char charBuf[str_len];
        path1.toCharArray(charBuf,str_len);
        gprs_call(charBuf);
        }
        delay(1000);
        if(humid!=h_old)
        {
        Serial.println("New humid = "+humid);
        String path2 = pa+"/?h="+humid+"\"\r";
        int str_len = path2.length() + 1;
        char charBuf[str_len];
        path2.toCharArray(charBuf,str_len);
        gprs_call(charBuf);
        }
           delay(1000);
        if(pressure!=p_old)
        {          
         String path3 = pa+"/?p="+pressure+"\"\r";
         Serial.println("New pressure = "+pressure);
         int str_len = path3.length() + 1;
         char charBuf[str_len];
         path3.toCharArray(charBuf,str_len);
         gprs_call(charBuf);

        }
        
          delay(1000);
     

         //bt_count++;
        

        
    
  }
  }

}


void gprs_call(char charurl[]){
  
          GPRS.listen();
   
          GPRS.write(charurl);
          Serial.println(charurl); 
          delay(1000);
          
          GPRS.write(cmd7);
          Serial.println(cmd7); 
          delay(1000);
          
          GPRS.write(cmd8);
          Serial.println(cmd8); 
          delay(1000);
        
          GPRS.write(cmd9);
          Serial.println(cmd9); 
          delay(1000);
}

