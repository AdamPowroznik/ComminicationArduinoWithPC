String inputString = "";
bool stringComplete = false;
String commandString = "" ;
bool isConnected = false;

#define ledPin 13
#define mainLight 8

void setup() {
 pinMode(ledPin, OUTPUT);
 pinMode(mainLight, OUTPUT);
 digitalWrite(mainLight, HIGH);
 Serial.begin(9600);
 pinMode(2, INPUT_PULLUP);
 pinMode(7, INPUT_PULLUP);
}

void loop() {
  if(stringComplete){
    stringComplete = false;
    getCommand();
    
  if(commandString.equals("STOP"))
    turnLedOff(ledPin);
  
  else if(commandString.equals("LED1")){
   // if(inputString.substring(5
    bool ledState = getLedState();
    if(ledState == true)
    turnLedOn(ledPin);
    else
    turnLedOff(ledPin);
  }

  else if(commandString.equals("ML01")){
     bool ledState = getLedState();
      if(ledState == true)
      turnLedOff(mainLight);
      else
      turnLedOn(mainLight);
  }

  else if(commandString.equals("PWM1")){
     int PWM1 = getPwm();
      analogWrite(ledPin, PWM1);
  }
  
  inputString="";
}

}

bool getLedState(){
  bool state =  false;
  if(inputString.substring(5,inputString.length()-1).equals("ON"))
  state = true;
  else 
  state = false;
  return state;
}

void getCommand(){
  if(inputString.length()>0)
  commandString = inputString.substring(1,5);
}

void turnLedOn(int pin)
{
  digitalWrite(pin,HIGH);
}

void turnLedOff(int pin)
{
  digitalWrite(pin,LOW);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

int getPwm(){
  int pwm = 0;
  pwm = inputString.substring(5,8).toInt();
  return pwm;
}


