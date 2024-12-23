# Posture-Detection-System-Using-Machine-Learning

Real-time posture classification using the BMI270 sensor and TensorFlow Lite for embedded systems. This project enables accurate detection of various postures like sitting, standing, and lying down, enhancing healthcare, ergonomics, and sports monitoring.

---

## Table of Contents

- [Introduction](#introduction)
- [Motivation](#motivation)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Setup and Installation](#setup-and-installation)
- [Usage Guide](#usage-guide)
- [Project Structure](#project-structure)
- [Future Plans](#future-plans)
- [Contributing](#contributing)
- [Acknowledgments](#acknowledgments)
- [License](#license)

---

## Introduction

The **Posture Detection System** is an embedded machine learning project designed to detect human postures in real-time using the BMI270 inertial measurement unit (IMU). The system leverages a TensorFlow Lite model optimized for microcontrollers, ensuring low latency and high efficiency in embedded environments.

---

## Motivation

While wearable and portable posture monitoring systems are becoming common, many rely on cloud computation, compromising privacy and increasing latency. This project brings real-time inference to the edge, making it ideal for applications in:

- Healthcare: Monitoring patient or elderly postures for fall detection or recovery tracking.
- Ergonomics: Ensuring proper posture in workplaces to avoid injuries.
- Sports: Enhancing athlete performance and detecting incorrect movements.

---

## Features

- **Real-Time Inference**: Classify postures as sitting, standing, lying down, or unknown in milliseconds.
- **Orientation Independence**: Works effectively regardless of sensor orientation.
- **Efficient Design**: Designed for low-power, resource-constrained microcontrollers.
- **Expandability**: Easily adaptable for new postures or additional sensors.

---

## Technologies Used

- **Hardware**:
  - Arduino Nano 33 BLE Sense or similar microcontroller.
  - BMI270 sensor for IMU data collection.
- **Software**:
  - TensorFlow Lite for Microcontrollers.
  - Python for model training and conversion.
  - Arduino IDE for firmware development.
- **Languages**:
  - C++ for embedded system programming.
  - Python for data preprocessing and model training.

---

## Setup and Installation

### Prerequisites

1. **Hardware**:
   - Arduino board and BMI270 sensor connected via I2C.
   - USB cable for programming and power.

2. **Software**:
   - Install [Arduino IDE](https://www.arduino.cc/en/software).
   - Install the TensorFlow Lite and BMI270 libraries via the Arduino Library Manager.

### Steps

1. Clone this repository:
   ```bash
   git clone https://github.com/your-username/posture-detection-system.git
   cd posture-detection-system
   ```

2. Upload the `data_collection.ino` file to your Arduino board to collect IMU data.

3. Use Python scripts in the `src/model_training` directory to preprocess data and train the model.

4. Convert the trained model to TensorFlow Lite format and deploy it by uploading `inference.ino`.

---

## Usage Guide

1. **Data Collection**:
   - Run `data_collection.ino` on the Arduino to stream IMU data to your computer.
   - Label and save the collected data for training.

2. **Model Training**:
   - Use `model_training.ipynb` to preprocess the data and train the neural network.
   - Save the trained model in TensorFlow Lite format.

3. **Deployment**:
   - Deploy the model by embedding it into `inference.ino` and upload the code to your Arduino.

4. **Real-Time Posture Detection**:
   - Open the serial monitor in the Arduino IDE.
   - Observe the detected posture in real-time.

---

## Project Structure

```
posture-detection-system/
├── README.md                  # Project documentation
├── data/                      # Collected IMU data
├── models/                    # Pre-trained and TFLite models
├── src/
│   ├── data_collection.ino    # Arduino code for data collection
│   ├── inference.ino          # Arduino code for real-time inference
│   ├── model_training/        # Python scripts for training and preprocessing
├── LICENSE                    # License information
└── docs/                      # Additional documentation
```

---

## Future Plans

1. **Integration of Additional Sensors**: Add more IMU devices for increased accuracy.
2. **Quaternion Data Analysis**: Improve orientation tracking using quaternion math.
3. **Cloud Connectivity**: Optional cloud data storage for long-term monitoring.
4. **Mobile Integration**: Develop an app to display real-time posture analysis.

---

## Contributing

Contributions are welcome! Follow these steps:

1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes and push to the branch:
   ```bash
   git commit -m "Added feature-name"
   git push origin feature-name
   ```
4. Open a pull request for review.

Please ensure your contributions adhere to the [Contributor Covenant](https://www.contributor-covenant.org/).

---

## Acknowledgments

Special thanks to:

- The [TensorFlow Lite](https://www.tensorflow.org/lite) team for enabling ML on edge devices.
- Open-source contributors for their BMI270 drivers and Arduino support libraries.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

