RTC_DATA_ATTR int bootCount = 0;
byte counter = 0;

void setup(){
  Serial.begin(115200);
  delay(1000); 
  pinMode(33, INPUT_PULLUP);
  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //Print the wakeup reason for ESP32
  //if (bootCount > 1)
    print_wakeup_reason();

  //Configure GPIO33 as ext0 wake up source for HIGH logic level
  if (digitalRead(33) == 1)
  {
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, LOW);
    Serial.println("Waiting on LOW interrupt");
  }

  if (digitalRead(33) == 0)
  {
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, HIGH);
    Serial.println("Waiting on HIGH interrupt");
  }

  Serial.println("Going to sleep");
  delay(500);
  //Go to sleep now
  esp_deep_sleep_start();
}

void loop()
{
  //esp_deep_sleep_start();
  Serial.println(counter);
  counter++;
}

//Function that prints the reason by which ESP32 has been awaken from sleep
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch(wakeup_reason)
  {
    case 1  : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case 2  : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case 3  : Serial.println("Wakeup caused by timer"); break;
    case 4  : Serial.println("Wakeup caused by touchpad"); break;
    case 5  : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.println("Wakeup was not caused by deep sleep"); break;
  }
}
