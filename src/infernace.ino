#include "model.h"                    
#include <TensorFlowLite.h>            
#include <tensorflow/lite/micro/all_ops_resolver.h>  
#include <tensorflow/lite/micro/tflite_bridge/micro_error_reporter.h>  
#include <tensorflow/lite/micro/micro_interpreter.h>  
#include <tensorflow/lite/schema/schema_generated.h> 
#include "Arduino_BMI270_BMM150.h"    

// Tensor Arena Configuration: This defines the memory size for TensorFlow Lite model inference
constexpr int kTensorArenaSize = 16 * 1024;  // 16KB tensor arena size
uint8_t tensor_arena[kTensorArenaSize];  // Array to hold the Tensor Arena

// Declare global variables for TensorFlow Lite
tflite::MicroInterpreter* interpreter = nullptr;  // Pointer to the TensorFlow Lite interpreter
tflite::ErrorReporter* error_reporter = nullptr;  // Pointer to the error reporter for logging
const tflite::Model* model = nullptr;  // Pointer to the model

// Window configuration for sliding window mechanism
constexpr int kWindowSize = 50;  // Number of samples per window (5 seconds at 10 Hz)
float input_window[kWindowSize][3];  // 2D array to store 50 samples (3-axis data: x, y, z)
int windowIndex = 0;  // Index to track position in the input window

// Variable for mode selection (accelerometer, gyroscope, magnetometer)
int selectedMode = 0;  // 0: Not set, 1: Accelerometer, 2: Gyroscope, 3: Magnetometer

// Function to read IMU sensor data based on the selected mode
bool readSensorData(float& x, float& y, float& z) {
  switch (selectedMode) {
    case 1:  // Accelerometer mode
      if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(x, y, z);  // Read accelerometer data
        return true;
      }
      break;
    case 2:  // Gyroscope mode
      if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(x, y, z);  // Read gyroscope data
        return true;
      }
      break;
    case 3:  // Magnetometer mode
      if (IMU.magneticFieldAvailable()) {
        IMU.readMagneticField(x, y, z);  // Read magnetometer data
        return true;
      }
      break;
  }
  return false;  // Return false if data is not available
}

// Function to add sensor data to the window
void addToWindow(float x, float y, float z) {
  input_window[windowIndex][0] = x;  // Store x-axis data
  input_window[windowIndex][1] = y;  // Store y-axis data
  input_window[windowIndex][2] = z;  // Store z-axis data

  windowIndex++;  // Increment the index for the next sample
  if (windowIndex >= kWindowSize) {  // If the window is full, reset the index
    windowIndex = 0;
  }
}

// Function to check if the window is full
bool isWindowFull() {
  return (windowIndex == 0);  // Return true if the window index wraps around to 0
}

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
  while (!Serial);  // Wait until the Serial Monitor is available

  // Initialize IMU (accelerometer, gyroscope, magnetometer)
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");  // If initialization fails, print an error message
    while (1);  // Halt the program in an infinite loop
  }
  Serial.println("IMU initialized successfully.");  // If initialization succeeds, print success message

  // Initialize the TensorFlow Lite model
  static tflite::MicroErrorReporter micro_error_reporter;  // Create error reporter object
  error_reporter = &micro_error_reporter;  // Assign error reporter

  // Load the pre-trained TensorFlow Lite model into memory
  model = tflite::GetModel(model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter->Report("Model schema version mismatch!");  // Report version mismatch if detected
    while (1);  // Halt the program in an infinite loop
  }

  // Set up the TensorFlow Lite interpreter with the model and operations resolver
  static tflite::AllOpsResolver resolver;  // Resolver to register all operations used in the model
  interpreter = new tflite::MicroInterpreter(model, resolver, tensor_arena, kTensorArenaSize);  // Create interpreter instance

  // Allocate memory for the tensors required by the model
  if (interpreter->AllocateTensors() != kTfLiteOk) {
    error_reporter->Report("Tensor allocation failed!");  // Report error if allocation fails
    while (1);  // Halt the program in an infinite loop
  }

  Serial.println("Setup complete. Enter 1 for Accelerometer, 2 for Gyroscope, 3 for Magnetometer:");  // Indicate setup completion
}

void loop() {
  // Read user input for selecting the sensor mode
  if (Serial.available()) {
    char input = Serial.read();  // Read the character input from the Serial Monitor
    if (input == '1' || input == '2' || input == '3') {
      selectedMode = input - '0';  // Set the mode based on user input ('1' -> Accelerometer, '2' -> Gyroscope, '3' -> Magnetometer)
      Serial.print("Selected mode: ");
      if (selectedMode == 1) Serial.println("Accelerometer");
      else if (selectedMode == 2) Serial.println("Gyroscope");
      else if (selectedMode == 3) Serial.println("Magnetometer");
    } 
    delay(500);  // Delay to allow user to input again
    return;
  }

  // Skip prediction if no mode is selected
  if (selectedMode == 0) return;

  float x, y, z;  // Variables to store sensor data

  // Read sensor data based on the selected mode
  if (!readSensorData(x, y, z)) return;  // If data is not available, skip

  // Add the sensor data to the sliding window
  addToWindow(x, y, z);

  // Perform prediction when the window is full
  if (isWindowFull()) {
    // Prepare the input tensor with the sensor data
    float* model_input = interpreter->input(0)->data.f;
    for (int i = 0; i < kWindowSize; i++) {
      model_input[i * 3 + 0] = input_window[i][0];  // Assign x-axis data to the input tensor
      model_input[i * 3 + 1] = input_window[i][1];  // Assign y-axis data to the input tensor
      model_input[i * 3 + 2] = input_window[i][2];  // Assign z-axis data to the input tensor
    }

    // Invoke the model to perform inference
    if (interpreter->Invoke() == kTfLiteOk) {
      // Process model output
      float* output = interpreter->output(0)->data.f;  // Get the output probabilities
      int predicted_class = 0;  // Variable to store the predicted class
      float max_probability = output[0];  // Initialize with the first class probability

      // Find the class with the maximum probability
      for (int i = 1; i < 6; i++) {  // Assuming there are 6 classes (including "unknown")
        if (output[i] > max_probability) {
          max_probability = output[i];  // Update max probability
          predicted_class = i;  // Update predicted class
        }
      }

      // Print predicted class and output probabilities
      Serial.print("Predicted Class: ");
      Serial.println(predicted_class);
      Serial.print("Prediction Probabilities: ");
      for (int i = 0; i < 6; i++) {
        Serial.print(output[i], 6);  // Print the probabilities with 6 decimal places
        Serial.print(" ");
      }
      Serial.println();
    } else {
      Serial.println("Model inference failed!");  // If inference fails, print an error message
    }
  }

  delay(100);  // Control the sampling rate (100 ms delay between each loop iteration)
}
