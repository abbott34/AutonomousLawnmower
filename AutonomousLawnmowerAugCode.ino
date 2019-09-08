//INITIALIZATION
#define S0 2 //SCALING OUTPUT FREQUENCIES
#define S1 3 //SCALING OUTPUT FREQUENCIES
#define S2 4 //PHOTODILE TYPE
#define S3 5 //PHOTODILE TYPE
#define SensorOut 6

int In1 = 7; //SPIN LEFT WHEEL CLOCKWISE
int In2 = 8; //SPIN LEFT WHEEL COUNTER CLOCKWISE
int ENA = 9; //SPEED CONTROL LEFT WHEEL
int In3 = 10; //SPIN RIGHT WHEEL CLOCKWISE
int In4 = 11; //SPING RIGHT WHEEL COUNTER CLOCKWISE
int ENB = 12; //SPEED COONTROL RIGHT WHEEL
int SPEED = 255; //PWM SIGNAL, MAX SPEED
int ValueofGreen = 0;
int r_frequency = 0; //FREQUENCY OF RED LIGHT
int g_frequency = 0; //FREQUENCY OF GREEN LIGHT
int b_frequency = 0; //FREQUENCY OF BLUE LIGHT
int greenval = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SensorOut, INPUT);
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);
  pinMode(ENB, OUTPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

//FUNCTIONS

//WHEEL CONTROL
void WheelControl(int ValueofGreen){
  while(ValueofGreen > 150) {
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    analogWrite(ENA, SPEED);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(ENB, SPEED);
  }
}

//COLOR SENSING
int ColorDetect(){
  //RED DETECTION
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  r_frequency = pulseIn(SensorOut, LOW);
  //REMAPPING TO PWM VALUES
  r_frequency = map(r_frequency, 20, 80, 255, 0);

  //GREEN DETECTION
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  g_frequency = pulseIn(SensorOut, LOW);
  //REMAPPING TO PWM VALUES
  g_frequency = map(g_frequency, 20, 80, 255, 0);

  //BLUE DETECTION
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  b_frequency = pulseIn(SensorOut, LOW);
  //REMAPPING TO PWM VALUES  
  b_frequency = map(b_frequency, 20, 80, 255, 0);
  
  return(g_frequency);
}
//TURNING FUNCTION
void turning(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  analogWrite(ENA, SPEED);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  analogWrite(ENB, SPEED);
}
void loop() {
  // put your main code here, to run repeatedly:
greenval = ColorDetect();
WheelControl(greenval);
if (greenval < 150){
  turning();
  }
}
