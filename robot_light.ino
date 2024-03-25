//ENGINES
const int EN1 = 9; // Enable engine 1
const int MC1 = 3; // H-bridge controls for engine 1
const int MC2 = 2; // H-bridge controls for engine 1

const int EN2 = 10; // Enable engine 2
const int MC3 = 4;  // H-bridge controls for engine 2
const int MC4 = 5;  // H-bridge controls for engine 2

//EYES
const int L_EYE = A0; // LDR 1
const int R_EYE = A1; // LDR 2

int serial_disp = 0; // read data from LDRs  

int left_input = 0; // light force from the left LDR
int right_input = 0; // light force from the right LDR
int differ = 0; // light force difference 

void setup() {


  // initialize pins for engine 1
  pinMode(EN1,OUTPUT);
  pinMode(MC1,OUTPUT);
  pinMode(MC2,OUTPUT);
  // initialize pins for engine 2
  pinMode(EN2,OUTPUT);
  pinMode(MC3,OUTPUT);
  pinMode(MC4,OUTPUT);
  
  Serial.begin(9600); // serial port configuration and initialization
  
  // analog read from LDR
  pinMode(L_EYE,INPUT);
  pinMode(R_EYE,INPUT); 

}
/*
void forward(int rate) // 
{
  digitalWrite(EN1,LOW); // shout down engines to prevent H-bridge damage
  digitalWrite(EN2,LOW);
  delay(50);
  digitalWrite(MC1,HIGH); // H-bridge for engine 1 forward
  digitalWrite(MC2,LOW);
  
  digitalWrite(MC3,HIGH); // H-bridge for engine 2 forward
  digitalWrite(MC4,LOW);

  analogWrite(EN1,rate); // Send PWM signal to engines 
  analogWrite(EN2,rate);
}
*/

void reverse(int rate)
{
  digitalWrite(EN1,LOW);// shout down engines to prevent H-bridge damage
  digitalWrite(EN2,LOW);
  delay(50);
  
  digitalWrite(MC1,LOW);  // H-bridge for engine 1 reverse
  digitalWrite(MC2,HIGH);
  
  
  digitalWrite(MC3,LOW);  // H-bridge for engine 2 reverse
  digitalWrite(MC4,HIGH);

  analogWrite(EN1,rate); // Send PWM signal to engines 
  analogWrite(EN2,rate);
}

void right(int rate)
{
  digitalWrite(EN1,LOW); // shout down engines to prevent H-bridge damage
  digitalWrite(EN2,LOW);
  delay(50);
  
  digitalWrite(MC1,LOW); // H-bridge for engine 1 reverse
  digitalWrite(MC2,HIGH);
  
  
  digitalWrite(MC3,LOW); // H-bridge for engine 2 STOP
  digitalWrite(MC4,LOW);
  
  analogWrite(EN1,rate); // Send PWM signal to engines 
  analogWrite(EN2,rate);
}

void left(int rate)
{
  digitalWrite(EN1,LOW); // shout down engines to prevent H-bridge damage
  digitalWrite(EN2,LOW);
  delay(50);
  
  digitalWrite(MC1,LOW); // H-bridge for engine 1 STOP
  digitalWrite(MC2,LOW);
  
  
  digitalWrite(MC3,LOW); // H-bridge for engine 2 reverse
  digitalWrite(MC4,HIGH);
  
  analogWrite(EN1,rate); // Send PWM signal to engines 
  analogWrite(EN2,rate);
}

void monitor(int val)
{
  Serial.println(val);
  delay(500);
}



void loop() {
  
  // left  eye
  serial_disp = analogRead(L_EYE); // read data from left LDR
  serial_disp = map(serial_disp,10,500,0,255); // linear maping for 8-bit number
  serial_disp = constrain(serial_disp,0,255); // avoid numbers in range other than 0-255
  
  
 // Serial.println("lewe_oko:"); 
 // Serial.println(serial_disp);
  
  left_input=serial_disp;
  
  // right eye
  serial_disp = analogRead(R_EYE); // read data from right LDR
  serial_disp = map(serial_disp,10,500,0,255); // linear maping for 8-bit number
  serial_disp = constrain(serial_disp,0,255); // avoid numbers in range other than 0-255
  
//  Serial.println("prawe_oko:");
//  Serial.println(serial_disp);
  
  right_input=serial_disp;
  
  
  differ = abs(left_input-right_input);  // difference in light power
  
  if( differ < 40) // light to weak
  {
    reverse(150);
  }
  else
  {
  
    if(left_input > right_input) // left light stronger
    {
      left(205); //robot turns left
  
    }
    else if(left_input <= right_input) // right light stronger
    { 
      right(205); //robot turns right
      
    }
  
  }

}
