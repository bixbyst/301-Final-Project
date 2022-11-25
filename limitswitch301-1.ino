
//Pin connections
const int switch1 = 2;   //0 or 360 degrees 
const int switch2 = 4;   //120 degrees 
const int switch3 = 8;   //240 degrees 
const int startbutton = 7; 
const int LEDon = 9;   //On 
const int LEDdone = 10;   //Done
  
//int i;
int count = 0; //switch count variable 
int pass = 0; //number of passes per section

int switch1state = 0;
int switch2state = 0;
int switch3state = 0;
int startstate = 0;

int lastswitch1state;
int lastswitch2state;
int lastswitch3state;
int laststartstate;

int switch1currentstate;
int switch2currentstate;
int switch3currentstate;
int laststartstate; 

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; 

void setup(){

  //Pin Initialization 
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  pinMode(startbutton, INPUT); 
  
  pinMode(LED1, OUTPUT);
//  pinMode(LED2, OUTPUT);
  
  Serial.begin(9600);//<-- note that  is default (slow/lame) //115200

}

void loop(){

  switch1state = digitalRead(switch1);
  switch2state = digitalRead(switch2);
  switch3state = digitalRead(switch3);
  startstate = digitalRead(startbutton);

 //If START button has been pressed, enter switch statements
   //digitalWrite(LED1, HIGH); indicating to user that it has started



 switch(count) {
//Case 0 + 1: CW/CCW rotation for section 1 (1st and 2nd button)
//Case 2 + 3: CW/CCW rotation for section 2 (1st and 3rd button)
//Case 4 + 5: CW/CCW rotation for section 3 (2nd and 3rd button)

  case 0: //off state 
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);

    if(switch1state != lastswitch1state){
      lastDebounceTime = millis();
    }

    if((millis() - lastDebounceTime) > debounceDelay) {
  
      if(startstate != startcurrentstate){
        startcurrentstate = startstate;

      if(startcurrentstate == HIGH){                        //If user presses the start button - LED1 on 
        Serial.println("Start Button has been pressed");
        //motor starts 
        digitalWrite(LED1, HIGH);
        count++;
       }
       } 
    }
    
     laststartstate = startstate; 
  } //end
  
  
  case 1:  //Section 1 rotated CW to 120 
  {
    
    if(switch2state != lastswitch2state){
      lastDebounceTime = millis();
    }

 if((millis() - lastDebounceTime) > debounceDelay) {
  
    if(switch2state != switch2currentstate){
      switch2currentstate = switch2state;

      if(switch2currentstate == HIGH){              //If switch2 pressed -- S1 turned CW 
        Serial.println("\nSwitch 2 Section 1"); 
        count++;                                    //count = 2
       }
    } 
   }
 
 lastswitch2state = switch2state; 
} //end

  
  case 2: //Section 1 turned CCW back to 0 
   {
  
   if(switch1state != lastswitch1state){
      lastDebounceTime = millis();
    }

  if((millis() - lastDebounceTime) > debounceDelay) {
  
    if(switch1state != switch1currentstate){
      switch1currentstate = switch1state;

      if(switch1currentstate == HIGH){       //If switch 1 pressed -- S1 turned CCW
         pass++;                             //First pass complete  (4 total) 
      
          Serial.println("\nSwitch 1 Section 1");
          Serial.print("\n Pass = ");
          Serial.print(pass);
   
        if(pass == 3){                      //If this is the fourth pass, skip to case 3
          count = 3;
          Serial.println("\nEnd of section 1");
          pass = 0;
        }
      else{
        count = 1;                          //If 4 passes have not been completed, repeat 
      }
     }
    } 
   }
 
 lastswitch1state = switch1state; 
}
   
     
    
   case 3: //Section 2 exposed (switches 3 & 1) 
{
   //If toggle turned CCW from switch 1 to switch 3  (0 -> 240 degrees) 
     
      if(switch3state != lastswitch3state){
      lastDebounceTime = millis();
    }

 if((millis() - lastDebounceTime) > debounceDelay) {
  
    if(switch3state != switch3currentstate){
      switch3currentstate = switch3state;

      if((switch3currentstate == HIGH) && (count == 3)){
        count++;
       Serial.println("\nSwitch 3 Section 2");            //If switch 3 pressed -- S3 CCW
 
       if(pass == 4){                                   //if it is the fifth pass, skip to case 5
        count = 5;
        pass = 0;
      
      }
       }
    } 
   }
 
 lastswitch3state = switch3state; 
} //end

   
   case 4: 
{
   //Turned CW to 360 or 0 degrees
    
     if(switch1state != lastswitch1state){
      lastDebounceTime = millis();
      }

 if((millis() - lastDebounceTime) > debounceDelay) {
  
    if(switch1state != switch1currentstate){
      switch1currentstate = switch1state;

      if((switch1currentstate == HIGH) && (count == 4)){
         pass++;
         Serial.println("\nSwitch 1 Section 2");
         Serial.print("\n Pass = ");
         Serial.print(pass);
         count = 3;                               //repeat cases 3 & 4 
       }
    } 
   }
 
 lastswitch1state = switch1state; 
} //end of debounce 



 
  case 5: //Section 3 exposed 
  {  
     if(switch2state != lastswitch2state){
      lastDebounceTime = millis();
    }

 if((millis() - lastDebounceTime) > debounceDelay) {
  
    if(switch2state != switch2currentstate){
      switch2currentstate = switch2state;

      if((switch2currentstate == HIGH) && (count == 5)){
         count = 6;
         Serial.println("\nSwitch 2 Section 3");
       } 
      }
    } 
   
 
 lastswitch2state = switch2state; 
} //end 
     
case 6: 
   {

     if(switch3state != lastswitch3state){
      lastDebounceTime = millis();
    }

    if((millis() - lastDebounceTime) > debounceDelay) {
  
    if(switch3state != switch3currentstate){
      switch3currentstate = switch3state;

      if((switch3currentstate == HIGH) && (count == 6)){
         pass++;
         Serial.println("\nSwitch 3 Section 3");
         Serial.print(count);
         Serial.println("\n Pass = ");
         Serial.print(pass);
     
        if(pass == 4){                                //5 passes complete
                                                     // Done - return bag and turn LED on 
           digitalWrite(LED1, LOW); 
           digitalWrite(LED2, HIGH);
           count = 7;
           pass = 0;
        }
      
        else {
        count = 4; 
        }

     }
    } 
   }
 
 lastswitch3state = switch3state; 
} //end
    
  case 6: 
   break;
   
  
 } //switch end bracket
 
 // Serial.print(count);
 // delay(500);
}
