void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}

int readedbyte = 0;
int trigger = 0;
int data1 = 0;
int data2 = 0;

void loop() {
  if (Serial.available())
  {
    readedbyte = Serial.read();

    if(readedbyte != 0x55)
      return;

    while(!Serial.available())
    {
      delay(1);
    }

    readedbyte = Serial.read();
    
    if(readedbyte != 0x11)
      return;

    while(!Serial.available())
    {
      delay(1);
    }

    data1 = Serial.read();

    while(!Serial.available())
    {
      delay(1);
    }

    data2 = Serial.read();

    if((data1 & 0xE0) == 0x00)
    {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        return;
    }

    if((data2 & 0x40) == 0x40)
    {
      if(trigger == 1)
      {
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        trigger = 0;
      }
      else
      {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        trigger = 1;
      }
    }
    
    delay(300);

    while(Serial.available())
    {
      Serial.read();
    }
  }
}
