int JoyStick_X = A0; // x
int JoyStick_Y = A1; // y
int JoyStick_Z = A2; // button
void ChangeValue(int);
void(* resetFunc) (void) = 0;
int x, y, z, a, b, para, val, count = 0;
void setup() {
  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);
  pinMode (JoyStick_Z, INPUT);
  Serial.begin (9600);
  Serial1.begin(9600, SERIAL_7E1);
  Serial.println("Read or Write");
}
void loop() {
  //x = analogRead (JoyStick_X);
  while (Serial.available() > 0)
  {
    char inputValue = Serial.read();
    if ((inputValue == 'R') or (inputValue == 'r')) {
      Read();
    }
    else if ((inputValue == 'W') or (inputValue == 'w'))
    {
      Write();
    }
  }
}

void Read() {
  Serial1.begin(9600, SERIAL_7E1);
  Serial.println("Reading");

  //AMPLITUDE
  Serial1.write("#Pn%");
  Serial1.write('\r');
  delay(100);
  int Amp = Serial1.read();
  Serial.println(Amp);
  //TIME
  Serial1.write("#Tn");
  Serial1.write('\r');
  delay(100);
  int Tim = Serial1.read();
  Serial.println(Tim);
  //PULSE
  Serial1.write("#Tp%");
  Serial1.write('\r');
  delay(100);
  int Pulse = Serial1.read();
  Serial.println(Pulse);
  delay(500);
  resetFunc();
}
void Write()
{
  Serial.println("Choose parameter");
  while (1)
  {
    Serial.print("Count:");
    Serial.println(count);
    delay(500);
    y = analogRead (JoyStick_Y);
    z = analogRead (JoyStick_Z);
    if (y == 1023)
    {
      count = constrain(count, 1, 5);
      count++;
    }
    else if (y == 0)
    {
      count = constrain(count, 1, 5);
      count--;
    }
    else if (z == 0)
    {
      Serial.println("BUTTON is PRESSED");
      para = count;
      Serial.print("para:");
      Serial.println(para);
      delay(1000);
      ChangeValue(para);
      break;
    }

  }
  //resetFunc();
}
void ChangeValue(int s) {
  Serial.print("You choose to change ");
  switch (s)
  {
    case 1:
      Serial.println("Amplitude");
      setAmplitude();
      break;
    case 2:
      Serial.println("Time");
      settime();
      break;
    case 3:
      Serial.print("Pulse");
      setPulse();
      break;
    case 4:
      Serial.print("Poweron");
      //setpowerOn();
      break;
    default:
      Serial.print("exit");
      break;
  }
  //resetFunc();
  // return 0;
}
void setAmplitude()
{
  Serial1.write("#Pn%");
  Serial1.write('\r');
  delay(100);
  int oldAmp = 20; // change 0 to Serial1.read();
  Serial.print("OldAmp: ");
  Serial.println(oldAmp);
  int newAmp = oldAmp;
  while (1)
  {
    Serial.print("newAmp:");
    Serial.println(newAmp);
    delay(500);
    x = analogRead (JoyStick_X);
    b = analogRead (JoyStick_Z);
    if (x == 1023)
    {
      newAmp++;
      newAmp = constrain(newAmp, 0, 70);// change 0 to 20
      //Serial.println(newAmp);
    }
    else if (x == 0)
    {
      newAmp--;
      newAmp = constrain(newAmp, 0, 70);// change 0 to 20
      //Serial.println(newAmp);
    }
    else if (b == 0)
    {
      Serial.println("BUTTON is PRESSED");
      val = newAmp;
      Serial.print("Changed Value:");
      Serial.println(val);
      delay(1000);
      break;
    // ChangeValue(para);
    //break;
    }
  }
  Serial1.write("#Pn%");
  Serial1.write(val);
  delay(100);
  Serial.print("Uploaded to machine");
  Write();
}
void settime()
{
  Serial1.write("#Tn");
  Serial1.write('\r');
  delay(100);
  int oldTime = 0; // change 0 to Serial1.read();
  Serial.print("oldTime: ");
  Serial.println(oldTime);
  int newTime = oldTime;
  while (1)
  {
    Serial.print("newTime:");
    Serial.println(newTime);
    delay(500);
    x = analogRead (JoyStick_X);
    b = analogRead (JoyStick_Z);
    if (x == 1023)
    {
      newTime++;
      newTime = constrain(newTime, 0, 70);// change 0 to 20
      //Serial.println(newAmp);
    }
    else if (x == 0)
    {
      newTime--;
      newTime = constrain(newTime, 0, 70);// change 0 to 20
      //Serial.println(newAmp);
    }
    else if (b == 0)
    {
      Serial.println("BUTTON is PRESSED");
      val = newTime;
      Serial.print("Changed Value:");
      Serial.println(val);
      delay(1000);
      break;
    // ChangeValue(para);
    //break;
    }
  }
  Serial1.write("#Tn%");
  Serial1.write(val);
  delay(100);
  Serial.print("Uploaded to machine");
  Write();
}
void setPulse()
{
  Serial1.write("#Tp%");
  Serial1.write('\r');
  delay(100);
  int oldPulse = 0; // change 0 to Serial1.read();
  Serial.print("oldPulse: ");
  Serial.println(oldPulse);
  int newPulse = oldPulse;
  while (1)
  {
    Serial.print("newPulse:");
    Serial.println(newPulse);
    delay(500);
    x = analogRead (JoyStick_X);
    b = analogRead (JoyStick_Z);
    if (x == 1023)
    {
      newPulse++;
      newPulse = constrain(newPulse, 0, 70);// change 0 to 20
      //Serial.println(newAmp);
    }
    else if (x == 0)
    {
      newPulse--;
      newPulse = constrain(newPulse, 0, 70);// change 0 to 20
      //Serial.println(newAmp);
    }
    else if (b == 0)
    {
      Serial.println("BUTTON is PRESSED");
      val = newPulse;
      Serial.print("Changed Value:");
      Serial.println(val);
      delay(1000);
      break;
    // ChangeValue(para);
    //break;
    }
  }
  Serial1.write("#Tp%");
  Serial1.write(val);
  delay(100);
  Serial.print("Uploaded to machine");
  Write();
}
