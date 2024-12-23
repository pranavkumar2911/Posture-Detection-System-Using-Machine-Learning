# Usage Guide

## Setting Up the Hardware
1. Connect the BMI270 sensor to your Arduino board using I2C.
2. Upload the `data_collection.ino` file from the `src` folder to your Arduino to collect data.

## Training the Model
1. Preprocess the IMU data using the `model_training.ipynb` notebook.
2. Train the model and save it as `model.tflite`.

## Deploying the Model
1. Replace the placeholder model in the `inference.ino` file with your `model.tflite`.
2. Upload the code to the Arduino for real-time inference.
