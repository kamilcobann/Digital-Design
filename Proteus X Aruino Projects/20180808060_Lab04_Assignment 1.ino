const int inPin=A0;
const int outPin=9;
int sensorVal=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorVal=analogRead(inPin);
  Serial.println();

  if(sensorVal >= 823){
    digitalWrite(outPin,LOW);
  }else{
    digitalWrite(outPin, HIGH);
  }
  Serial.print("LDR VALUE: ");
  Serial.print(sensorVal);
  Serial.print("LED STATUS: ");

  if(sensorVal >= 823){
    Serial.print("0");
   
  }else{
    Serial.print("1");
  }
}
