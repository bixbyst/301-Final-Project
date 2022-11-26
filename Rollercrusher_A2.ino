#define CW 5
#define CCW 6 

char black = 8;
char green = 12;
char red = 7;
char start = 4;
unsigned long startTime;
unsigned long currentTime;
int count=0;
unsigned long state = 0;
int debounceDelay = 50;

void setup() {
  pinMode(CW,OUTPUT); //IN2 pin -- DC Motor
  pinMode(CCW,OUTPUT); //IN1 pin -- DC Motor

  digitalWrite(CCW, HIGH); //Starts the DC motor rotating in a forward direction
  digitalWrite(CW, HIGH);
  Serial.begin(9600);
}

void loop() {
  //startTime = millis();
  
  
switch(state){

    case 0: //state

    if (pressed (start)){
    digitalWrite(CW,HIGH);
    digitalWrite(CCW, LOW);
    count = 0;
    state = 1;
    Serial.println("The rollers are crushing");
  }

      break;

    case 1: //first section going back and forth
    
    while (count<50){
    if (pressed (green)){
    digitalWrite(CW,LOW);
    digitalWrite(CCW,HIGH);
    //state = 1;
    count = count+1;
    Serial.println("green");
    Serial.println(count);
    }
    if (pressed (red)){
    digitalWrite(CW,HIGH);
    digitalWrite(CCW,LOW);
    //state == 1;
    count = count+1;
    Serial.println("red");
    Serial.println(count);
  }
  }
    if (count == 4){
      state = 2;
    }
      break;

    case 2: //done with first section, rolling backwards

    digitalWrite(CW,LOW);
    digitalWrite(CCW,HIGH);

      break;
}

//  if (pressed (black)){
//    digitalWrite(CW,HIGH);
//    digitalWrite(CCW, LOW);
//    count = cou;
//    Serial.println("The motor is going forward");
//  }

 
}

bool pressed(char pin){ //Custom function checking to see if the button is being pressed or not
  if(digitalRead(pin)==HIGH) //if the button is being pressed, return true
    return true;
    else
    return false; //if the button is not being pressed, return false
}
