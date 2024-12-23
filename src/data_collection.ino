#include "Arduino_BMI270_BMM150.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("ax,ay,az,gx,gy,gz,mx,my,mz,label");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  float aX, aY, aZ;
  float gX, gY, gZ;
  float mX, mY, mZ;

  // Checking if data is available from accelerometer, gyroscope, and magnetometer
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable() && IMU.magneticFieldAvailable()) {
    IMU.readAcceleration(aX, aY, aZ);        // Reading accelerometer data
    IMU.readGyroscope(gX, gY, gZ);        // Reading gyroscope data
    IMU.readMagneticField(mX, mY, mZ);       // Reading magnetometer data

    // Print data in CSV format: Accelerometer, Gyroscope, Magnetometer, Label
    Serial.print(aX); Serial.print("   "); Serial.print(aY); Serial.print("   "); Serial.print(aZ); Serial.print("   ");
    Serial.print(gX); Serial.print("   "); Serial.print(gY); Serial.print("   "); Serial.print(gZ); Serial.print("   ");
    Serial.print(mX); Serial.print("   "); Serial.print(mY); Serial.print("   "); Serial.print(mZ); Serial.print("   ");
    
    // Add a label if needed (e.g., 1 for "supine," 2 for "prone", 3 for "side", 2 for "sitting", 2 for "unknown".)
    int label = 1;  // Changing this label manually based on the posture being collected
    Serial.println(label);
  }

  delay(100);  // Adjusting the delay to control sampling rate; 100 ms for ~10 Hz
}
