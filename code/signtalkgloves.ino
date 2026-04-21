#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

const int flexPin = A5;
int threshold = 500;

DFRobotDFPlayerMini myDFPlayer;
SoftwareSerial mySoftwareSerial(9, 10);

const unsigned long cooldownPeriod = 3000;
unsigned long lastPlaybackTime = 0;

void setup()
{
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);

  Serial.println("Initializing DFPlayer...");

  if (!myDFPlayer.begin(mySoftwareSerial))
  {
    Serial.println("DFPlayer not detected. Check connections.");
    while (true);
  }

  Serial.println("DFPlayer Mini online.");
  myDFPlayer.volume(25);
}

void loop()
{
  int flexValue = analogRead(flexPin);

  Serial.print("Flex Value: ");
  Serial.println(flexValue);

  unsigned long currentTime = millis();

  if ((currentTime - lastPlaybackTime) > cooldownPeriod)
  {
    if (flexValue > threshold)
    {
      Serial.println("Gesture detected: PLAY 1");
      myDFPlayer.play(1);
      lastPlaybackTime = millis();
    }
    else if (flexValue < threshold - 50)
    {
      Serial.println("Gesture detected: PLAY 2");
      myDFPlayer.play(2);
      lastPlaybackTime = millis();
    }
  }

  delay(100);
}
