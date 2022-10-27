#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

#define BLE_UUID_ACCELEROMETER_SERVICE "1101"
#define BLE_UUID_ACCELEROMETER_X "2101"
#define BLE_UUID_ACCELEROMETER_Y "2102"
#define BLE_UUID_ACCELEROMETER_Z "2103"

#define BLE_DEVICE_NAME "Elfo"
#define BLE_LOCAL_NAME "Elfo"

BLEService accelerometerService(BLE_UUID_ACCELEROMETER_SERVICE);

BLEFloatCharacteristic accelerometerCharacteristicX(BLE_UUID_ACCELEROMETER_X, BLERead | BLENotify);
BLEFloatCharacteristic accelerometerCharacteristicY(BLE_UUID_ACCELEROMETER_Y, BLERead | BLENotify);
BLEFloatCharacteristic accelerometerCharacteristicZ(BLE_UUID_ACCELEROMETER_Z, BLERead | BLENotify);

float x, y, z;

long previousMillis = 0;  // last time the imu was checked, in ms

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");

  // initialize BLE
  if (!BLE.begin()) {
    Serial.println("Starting Bluetooth® Low Energy module failed!");
    while (1)
      ;
  }

  // set advertised local name and service UUID
  BLE.setLocalName("Nano 33 IoT");
  BLE.setAdvertisedService(accelerometerService);

  // add characteristics
  accelerometerService.addCharacteristic(accelerometerCharacteristicX);
  accelerometerService.addCharacteristic(accelerometerCharacteristicY);
  accelerometerService.addCharacteristic(accelerometerCharacteristicZ);

  // add service
  BLE.addService(accelerometerService);

  // start advertising
  BLE.advertise();

  Serial.println("BLE Accelerometer Peripheral");
}

void loop() {
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // turn on the LED to indicate the connection:
    digitalWrite(LED_BUILTIN, HIGH);

    while (central.connected()) {
      long currentMillis = millis();
      // if 200ms have passed, update the imu data
      if (currentMillis - previousMillis >= 200) {
        previousMillis = currentMillis;
        updateImuData();
      }
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }

}

void updateImuData() {
  // Read the current accelerometer data and updates the relevant ble characteristics

  // obtain and write accelerometer data
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
  }

  accelerometerCharacteristicX.writeValue(x);
  accelerometerCharacteristicY.writeValue(y);
  accelerometerCharacteristicZ.writeValue(z);

}