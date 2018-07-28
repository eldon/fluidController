/*
 * Board: ESP-12E Module
*/

#define LED LED_BUILTIN
#define M1_EN D6
#define M1_L D7
#define M1_R D5

String inputString = "";
int val = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(M1_EN, OUTPUT);
  pinMode(M1_L, OUTPUT);
  pinMode(M1_R, OUTPUT);
  Serial.begin(9600);
  Serial.println("Ready for input");
}

void loop() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    Serial.print(inChar);
    inputString += inChar;
    if (inChar == '\n') {
      val = inputString.toInt();
      if (val == 0) {
        setM1Coast();
        Serial.println("coasting");
      } else if (abs(val) > 255) {
        setM1HardStop();
        Serial.println("hard stop!");
      } else {
        setM1(abs(val), boolean(val < 0));
        Serial.println("speed: " + String(val));
      }
      inputString = "";
    }
  }
}

void setM1(int spd, boolean reverse)
{
  analogWrite(M1_EN, spd);
  digitalWrite(M1_L, ! reverse);
  digitalWrite(M1_R, reverse);
}

void setM1HardStop()
{
  digitalWrite(M1_EN, HIGH);
  digitalWrite(M1_L, LOW);
  digitalWrite(M1_R, LOW);
}

void setM1Coast()
{
  digitalWrite(M1_EN, LOW);
}
