
#define CLEAR -1

//defining three pins of 74HC595
int latchPin = 4;//ST_CP
int clockPin = 5;//SH_CP 
int dataPin = 2; //DS 

//defining three key input
int key1 = A1;
int key2 = A2;
int key3 = A3;

//buzzer pin
int buzzer = 3;

//pin definition of flowing light
int led1 = 13;
int led2 = 12;
int led3 = 11;
int led4 = 10;
int led5 = 9;
int led6 = 8;

int dat_segment[4]={0x01,0x02,0x04,0x08};    //LED Segment Displays
//showing 1--4
int dat_number[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; //LED Segment Displays showing 0--9
char i=0; 

int tones[ ] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440,466, 494};
                       // mid C C# D D# E F F# G G# A

void BCD_write(int number, int segment){

  //Enable latch
  digitalWrite(latchPin,LOW);

  //Clear screen
  if(number == CLEAR){
    shiftOut(dataPin, clockPin, MSBFIRST ,0x00);
    shiftOut(dataPin, clockPin, MSBFIRST ,0x00);
  }

  //Show number in the specified segment
  else {
    shiftOut(dataPin, clockPin, MSBFIRST ,dat_number[number]);
    shiftOut(dataPin, clockPin, MSBFIRST ,dat_segment[segment]);     
  }

  //Disable latch
  digitalWrite(latchPin,HIGH);
}

void setup ()
{
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT); 
  
  pinMode(key1,INPUT); 
  pinMode(key2,INPUT); 
  pinMode(key3,INPUT); 
  
  pinMode(buzzer,OUTPUT);
}

void loop(){
  int wait = 1000;

    for(int j = 10; j >= 0; j--){
      for(int i = 59; i >= 0; i--)
      {
        int wait_end, wait_start;

        //The speaker sound each second
        tone(buzzer, 1, wait);

        
        wait_start = millis();
        do{

          //If button 1 is pressed, the counter increase speed x10 times
          if(digitalRead(key1) == LOW) wait = 100;

          //If button 2 is pressed, the minutes are setted to 0
          else if(digitalRead(key2) == LOW) j = 0;
    
          
          //Show Minutes
          BCD_write(j/10, 0);         
          BCD_write(j%10, 1);
          
          
          //Show Seconds
          BCD_write(i%10, 3);
          BCD_write(i/10, 2);
          
          wait_end = millis();

        //Don't update BCD panel until reach 1 second
        }while(wait_end - wait_start < wait);
        
       }//end for i
     }//end for j

    //End counter
    BCD_write(CLEAR, 0);
    tone(buzzer, 1);

    //Don't restart counter until button 3 is pressed
    while(digitalRead(key3) == HIGH);

}

