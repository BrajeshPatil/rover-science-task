#include <Arduino.h>
#include <AccelStepper.h> // Library for controlling NEMA 17 Stepper Motor
#include <Wire.h> // I2C Communication Library for Arduino
#include <Adafruit_BMP085.h> // Library for interfacing BMP180 sensor
#include <DHT.h> // Library for DHT22 temperature and humidity sensor
#include <Adafruit_MLX90614.h> // Used for interfacing MLX90614 infrared sensor.
#include <MQ135.h> // Supports MQ135 air quality gas sensor
#include <DFRobot_SHT20.h> // Used for interfacing DFRobot SHT20 sensor

// Constants
#define SEA_LEVEL_PRESSURE_HPA 1013.25
#define DHTPIN 44
#define DHTTYPE DHT22
#define ANALOGPIN_MQ135 A2
#define MOTOR_INTERFACE_TYPE 1

// Pin Definitions
const int actuatorPins[] = {26, 27}; // [0] = Positive, [1] = Negative
const int drillPins[] = {12, 26, 27}; // [0] = Enable, [1] = IN1, [2] = IN2
const int chemicalPins[] = {13, 24, 25}; // [0] = Enable, [1] = IN1, [2] = IN2
const int stepperPins[] = {22, 23}; // [0] = DIR, [1] = STEP

struct SensorData {
  float bmpTemp;
  float bmpPressure;
  float dhtTemp;
  float dhtHumidity;
  float mlxAmbient;
  float mlxObject;
  float mq135PPM;
};

// Objects
AccelStepper stepper(MOTOR_INTERFACE_TYPE, stepperPins[1], stepperPins[0]);
Adafruit_BMP085 bmp;
DHT dht(DHTPIN, DHTTYPE);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
DFRobot_SHT20 sht20;
MQ135 gasSensor(ANALOGPIN_MQ135);

void setup() {
  Serial.begin(9600);

  // Initialize Actuator, Drill, Chemical Motors
  for (int pin : drillPins) pinMode(pin, OUTPUT);
  for (int pin : chemicalPins) pinMode(pin, OUTPUT);
  for (int pin : actuatorPins){
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  } 

  // Initialize Stepper Motor
  stepper.setMaxSpeed(1000);

  // Initialize BMP085 Sensor
  if (!bmp.begin()) {
    Serial.println("Could not find a BMP sensor. Please check the wiring!");
    while (1) {}
  }

  // Initialize DHT22 Sensor
  dht.begin();

  // Initialize MLX90614 Sensor
  mlx.begin();

  // Initialize SHT20 Sensor
  sht20.initSHT20();
  delay(100);
  sht20.checkSHT20();

  // Initialize MQ135 Sensor
  gasSensor.getRZero();
}

void controlMotor(const int pins[], int dir) {
  digitalWrite(pins[1], dir == 0 ? HIGH : LOW);  // 0 for CLOCKWISE, 1 for ANTICLOCKWISE
  digitalWrite(pins[2], dir == 0 ? LOW : HIGH);
  analogWrite(pins[0], 255);
}

void actuatorControl(int direction) {
  digitalWrite(actuatorPins[0], direction == 0 ? LOW : HIGH);
  digitalWrite(actuatorPins[1], direction == 0 ? HIGH : LOW);
  delay(3000);
  digitalWrite(actuatorPins[0], HIGH);
  digitalWrite(actuatorPins[1], HIGH);
}

void drillControl(int direction) {
  controlMotor(drillPins, direction);  // Pass the direction as an integer directly
  delay(3000);
  analogWrite(drillPins[0], 0);
}

void nema17Control(int position) {
  int steps[] = {33, 67, 100, -33, -67, -100};
  if (position >= 0 && position < 6) {
    stepper.move(steps[position]);
    stepper.setSpeed(60);
  }
}

void chemicalControl() {
  controlMotor(chemicalPins, 0);
  delay(3000);
  analogWrite(chemicalPins[0], 0);
}

SensorData readSensors() {
  SensorData data;

  data.bmpTemp = bmp.readTemperature();
  data.bmpPressure = bmp.readPressure();
  data.dhtTemp = dht.readTemperature();
  data.dhtHumidity = dht.readHumidity();
  data.mlxAmbient = mlx.readAmbientTempC();
  data.mlxObject = mlx.readObjectTempC();
  data.mq135PPM = gasSensor.getPPM();

  return data;
}

int main(){
  bool running = true;
  while (running) {
    int action;
    scanf("%d", &action);
    switch (action) {
      case 0:
        actuatorControl(0);
        drillControl(0);
        actuatorControl(1);
        nema17Control(0);
        drillControl(1);
        nema17Control(1);
        chemicalControl();
        break;
      case 1:
        actuatorControl(0);
        drillControl(0);
        actuatorControl(1);
        nema17Control(0);
        drillControl(1);
        break;
      case 2:
        chemicalControl();
        break;
      case 3: {
        int n;
        scanf("%d", &n);
        nema17Control(n);
        break;
      }
      case 4: {
        int d;
        scanf("%d", &d);
        drillControl(d);
        break;
      }
      case 5: {
        int dir;
        scanf("%d", &dir);
        actuatorControl(dir);
        break;
      }
      case 6:
        running = false;
        break;
      default:
        Serial.println("Invalid Action!");
        break;
    }
  }
}
