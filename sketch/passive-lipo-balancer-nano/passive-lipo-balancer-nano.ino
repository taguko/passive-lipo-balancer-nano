// passive-lipo-balancer-nano

// OLED
#include "oled.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const float allowable_error = 0.005;

const uint32_t cycle = 20;  // [ms]

const float R1 = 100000;
const float R2 = 8200;
const float voltage_division_ratio = R2 / (R2 + R1);

const int SW1 = 8;

const int Sink_Cell1 = 2;
const int Sink_Cell2 = 3;
const int Sink_Cell3 = 4;

const int V_Cell1 = A0;
const int V_Cell2 = A1;
const int V_Cell3 = A2;

float voltage_cell[] = { 0, 0, 0 };

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Serial Port
  Serial.begin(9600);

  // pinMode
  analogReference(INTERNAL);  // 1V1

  pinMode(SW1, INPUT_PULLUP);

  pinMode(Sink_Cell1, OUTPUT);
  pinMode(Sink_Cell2, OUTPUT);
  pinMode(Sink_Cell3, OUTPUT);

  pinMode(V_Cell1, INPUT);
  pinMode(V_Cell2, INPUT);
  pinMode(V_Cell3, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  // setup
  oled_setup();
}

void loop() {
  uint32_t preMillis = millis();

  // Ready
  digitalWrite(Sink_Cell1, LOW);
  digitalWrite(Sink_Cell2, LOW);
  digitalWrite(Sink_Cell3, LOW);

  // Voltage check
  voltage_cell[0] = mapf(analogRead(V_Cell1), 0, 1023, 0, 1.1) / voltage_division_ratio;
  voltage_cell[1] = mapf(analogRead(V_Cell2) - analogRead(V_Cell1), 0, 1023, 0, 1.1) / voltage_division_ratio;
  voltage_cell[2] = mapf(analogRead(V_Cell3) - analogRead(V_Cell2), 0, 1023, 0, 1.1) / voltage_division_ratio;
  serial_handle();
  oled_handle();

  // Mode choose & run discharge
  if (digitalRead(SW1) == HIGH)
    Storage_discharge();
  else
    Balance_discharge();

  // Wait
  while ((millis() - preMillis) < cycle)
    ;
}

void serial_handle() {
  if (digitalRead(SW1) == HIGH)
    Serial.print("Balance mode ");
  else
    Serial.print("Storage mode ");
  String info;
  info = "V_Cell1:" + String(voltage_cell[0]) + "V ";
  Serial.print(info);
  info = "V_Cell2:" + String(voltage_cell[1]) + "V ";
  Serial.print(info);
  info = "V_Cell3:" + String(voltage_cell[2]) + "V";
  Serial.println(info);
}

float mapf(float x, float in_min, float in_max,
           float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min)
           / (in_max - in_min)
         + out_min;
}
