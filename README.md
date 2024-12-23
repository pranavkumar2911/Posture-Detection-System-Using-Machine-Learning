# Posture-Detection-System-Using-Machine-Learning

A real-time, orientation-independent posture detection system leveraging the BMI270 sensor, Arduino, and embedded machine learning for healthcare, ergonomics, and sports applications.

---

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [System Architecture](#system-architecture)
4. [Setup and Installation](#setup-and-installation)
5. [Usage](#usage)
6. [Project Structure](#project-structure)
7. [Results](#results)
8. [Applications](#applications)
9. [Future Improvements](#future-improvements)
10. [License](#license)

---

## Introduction

Posture detection and classification are essential for applications such as healthcare monitoring, rehabilitation, ergonomic assessments, and wearable devices. This project aims to provide a robust, real-time system for posture detection using the BMI270 inertial sensor, Arduino, and TensorFlow Lite.

Key objectives:
- Ensure portability and privacy by eliminating reliance on cameras.
- Enable real-time classification with minimal hardware resources.

---

## Features

- Real-time posture classification for six classes: **Supine**, **Prone**, **Side**, **Sitting**, **Standing**, and **Unknown**.
- Orientation-independent detection for practical deployment.
- Sensor noise reduction using a low-pass filter.
- Lightweight model deployed using TensorFlow Lite for embedded devices.

---

## System Architecture

The project comprises three main components:

1. **Hardware**
   - BMI270 inertial sensor (accelerometer, gyroscope, magnetometer).
   - Arduino microcontroller for data acquisition and model inference.

2. **Software**
   - Embedded TensorFlow Lite model for posture classification.
   - Arduino-based data collection and preprocessing.

3. **Machine Learning Model**
   - Neural network trained to classify six postures using raw sensor data.
   - Sliding window preprocessing with a FIFO buffer for time-series data.

---

## Setup and Installation

### **Hardware Requirements**
- Arduino (compatible board, e.g., Arduino Nano 33 BLE Sense).
- BMI270 sensor.
- USB cable for Arduino connection.
- Computer for development and deployment.

### **Software Requirements**
1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Install the necessary libraries:
   - TensorFlow Lite
   - BMI270 driver libraries
3. Install a serial communication tool (e.g., CoolTerm).

### **Steps**
1. Clone this repository:
   ```bash
   git clone https://github.com/<your-username>/posture-detection-system.git
   cd posture-detection-system
