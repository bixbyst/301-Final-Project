
//Pin connections
const int switch1 = 2;   //0 or 360 degrees 
const int switch2 = 4;   //120 degrees 
const int switch3 = 8;   //240 degrees 
//const int LED1 = 7;   //On 
//const int LED2 = 6;   //Done
  
//int i;
int count = 0; //switch count variable 
int pass = 0; //number of passes per section

int switch1state = 0;
int switch2state = 0;
int switch3state = 0;

int lastswitch1state;
int lastswitch2state;
int lastswitch3state;

int switch1currentstate;
int switch2currentstate;
int switch3currentstate;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; 

void setup(){

  //Pin Initialization 
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  
//  pinMode(LED1, OUTPUT);
//  pinMode(LED2, OUTPUT);
  
  Serial.begin(9600);//<-- note that  is default (slow/lame) //115200

}

void loop(){

  switch1state = digitalRead(switch1);
  switch2state = digitalRead(switch2);
  switch3state = digitalRead(switch3);

 //If START button has been pressed, enter switch statements
   //digitalWrite(LED1, HIGH); indicating to user that it has started



 switch(count) {
//Case 0 + 1: CW/CCW rotation for section 1 (1st and 2nd button)
//Case 2 + 3: CW/CCW rotation for section 2 (1st and 3rd button)
//Case 4 + 5: CW/CCW rotation for section 3 (2nd and 3rd button)

  case 0: //Section 1 rotated CW to 120 
   {
    if(switch2state != lastswitch2state){
      lastDebounceTime = millis();
    }

 if((millis() - lastDebounceTime) > debounceDelay) {
  
    if(switch2state != switch2currentstate){
      switch2currentstate = switch2state;

      if(switch2currentstate == HIGH){
        Serial.println("\nSwitch 2 Section 1");
        count++;  //First section turned CW -> count = 1
       }
    } 
   }
 
 lastswitch2state = switch2state; 
} //end

  
  case 1: //Section 1 turned CCW back to 0 (360) 
   {
  
   if(switch1state != lastswitch1state){
      lastDebounceTime = millis();
    }

  if((millis() - lastDebounceTime) > debounceDelay) {
  
    if(switch1state != switch1currentstate){
      switch1currentstate = switch1state;

      if(switch1currentstate == HIGH){
         pass++; //section 1, pass 1 complete 
      
          Serial.println("\nSwitch 1 Section 1");
          Serial.print("\n Pass = ");
          Serial.print(pass);
   
        if(pass == 3){  //if it is the fourth pass, skip to case 2
          count = 2;
          Serial.println("\nEnd of section 1");
          pass = 0;
        }
      else{
        count = 0; //repeat 
      }
     }
    } 
   }
 
 lastswitch1state = switch1state; 
}
   
      
    
   case 2: //Section 2 exposed (switches 3 & 1) 
{
   //If toggle turned CCW from switch 1 to switch 3  (0 -> 240 degrees) 
     
      if(switch3state != lastswitch3state){
      lastDebounceTime = millis();
    }

 if((millis() - lastDebounceTime) > debounceDelay) {
  
    if(switch3state != switch3currentstate){
      switch3currentstate = switch3state;

      if((switch3currentstate == HIGH) && (count == 2)){
        count++;
       Serial.println("\nSwitch 3 Section 2");
 
       if(pass == 4){  //if it is the fifth pass skip to case 4
        count = 4;
        pass = 0;
      
      }
       }
    } 
   }
 
 lastswitch3state = switch3state; 
} //end

   
   case 3: 
{
   //Turned CW to 360 or 0 degrees
    
     if(switch1state != lastswitch1state){
      lastDebounceTime = millis();
      }

 if((millis() - lastDebounceTime) > debounceDelay) {
  
    if(switch1state != switch1currentstate){
      switch1currentstate = switch1state;

      if((switch1currentstate == HIGH) && (count == 3)){
         pass++;
         Serial.println("\nSwitch 1 Section 2");
         Serial.print("\n Pass = ");
         Serial.print(pass);
         count = 2; 
       }
    } 
   }
 
 lastswitch1state = switch1state; 
} //end of debounce 

 
  case 4: //Section 3 exposed 
  {  
     if(switch2state != lastswitch2state){
      lastDebounceTime = millis();
    }

 if((millis() - lastDebounceTime) > debounceDelay) {
  
    if(switch2state != switch2currentstate){
      switch2currentstate = switch2state;

      if((switch2currentstate == HIGH) && (count == 4)){
         count = 5;
         Serial.println("\nSwitch 2 Section 3");
       } 
      }
    } 
   
 
 lastswitch2state = switch2state; 
} //end 
     
case 5: 
   {

     if(switch3state != lastswitch3state){
      lastDebounceTime = millis();
    }

    if((millis() - lastDebounceTime) > debounceDelay) {
  
    if(switch3state != switch3currentstate){
      switch3currentstate = switch3state;

      if((switch3currentstate == HIGH) && (count == 5)){
         pass++;
      Serial.println("\nSwitch 3 Section 3");
      Serial.print(count);
      Serial.println("\n Pass = ");
      Serial.print(pass);
     
        if(pass == 4){ //done
           count = 6;
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
 
 
 // delay(500); //need to add debounce function 
}
