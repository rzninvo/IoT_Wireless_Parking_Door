#include <Keypad.h>

char message;
char keys[4][3] ={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[4] = {22, 23, 24, 25};
byte colPins[3] = {26, 27, 28};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, 4, 3);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = kpd.getKey();
  if (key != NO_KEY)
  {
    Serial.println(key);
  }
}
