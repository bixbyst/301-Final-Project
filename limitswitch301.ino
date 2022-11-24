
//Pin connections
const int switch1 = 2;   //0 or 360 degrees 
const int switch2 = 4;   //120 degrees 
const int switch3 = 8;   //240 degrees 
//const int LED1 = 7;   //On 
//const int LED2 = 6;   //Done
  
//int i;
int count = 0; //switch count variable 
int pass = 0; //pass per section
int passtotal = 0; //total number of passes
int switch1state = 0;
int switch2state = 0;
int switch3state = 0;

void setup(){
 // i = 0;
  //Pin Initialization 
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
//  pinMode(LED1, OUTPUT);
//  pinMode(LED2, OUTPUT);
  
  Serial.begin(9600);//<-- note that  is default (slow/lame) //115200
 // Serial.println("Welcome to Arduino Serial");
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
   
    if(switch2state == HIGH){    
      Serial.println("\nSwitch 2 Section 1");
      count++;  //First section turned CW -> count = 1
      
    }
  case 1: //Section 1 turned CCW back to 0 (360) 
   
   if((switch1state == HIGH)){ //button was hit a second time while completing the pass 

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
      }}
      
    
   case 2: //Section 2 exposed (switches 3 & 1) 

   //If toggle turned CCW from switch 1 to switch 3  (0 -> 240 degrees) 
     
     if((switch3state == HIGH) && (count == 2)){   
       count++;
       Serial.println("\nSwitch 3 Section 2");
 
       if(pass == 4){  //if it is the fifth pass skip to case 4
        count = 4;
        pass = 0;
      
      } }
   
   case 3: 

   //Turned CW to 360 or 0 degrees
    
     if((switch1state == HIGH) && (count == 3)){   
      pass++;
      Serial.println("\nSwitch 1 Section 2");
      Serial.print("\n Pass = ");
      Serial.print(pass);
   
        count = 2; 
     
    }  
 
  case 4: //Section 3 exposed 
     
     if((switch2state == HIGH) && (count == 4)){   
       count = 5;
      Serial.println("\nSwitch 2 Section 3");
      } 
   
   case 5: 
     if((switch3state == HIGH) && (count == 5)){   
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
    
    
  case 6: 
   break;
   
  
 } //switch end bracket

  Serial.print(count); 
  delay(500); //need to add debounce function 
}
