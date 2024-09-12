# UNOBB (Uno Black Box)

## Overview

**UNOBB** is an Arduino Uno-based black box system designed for vehicles, specifically to connect via the 12V OBD-II port. This system can track vehicle anomalies, provide crucial driving data, and help companies like invoice or insurance providers detect fraud or suspicious activity. For example, the system can capture data during small crashes, identifying potential fraud like staged accidents or late-night damage. Users who install the black box can benefit from lower tariffs due to more accurate and reliable driving records.

## Features

- **Real-Time Data Collection**: Captures OBD-II data and other driving information in real-time.
- **Anomaly Detection**: Tracks anomalies such as sudden braking, sharp turns, or potential collision events.
- **Data Logging**: Logs critical driving data for post-incident analysis, including speed, acceleration, and crash information.
- **Fraud Detection**: Helps detect insurance fraud by tracking unusual driving patterns or inconsistencies in crash reports.
- **Cost Reduction for Users**: Provides a benefit for users by offering lower tariffs based on verified driving behavior, rewarding safe driving.

## Use Case

- **Invoice and Insurance Companies**: Allows companies to make more accurate decisions about invoices and insurance claims by analyzing real-world driving data.
- **Fraud Detection**: Detects and logs possible fraud attempts, such as deliberately crashing a car at night to claim insurance.
- **Customer Incentives**: Users who install the system on their vehicles can benefit from lower monthly premiums or tariffs.

## Hardware Requirements

To build and set up the UNOBB system, you’ll need the following hardware components:
- **Arduino Uno**: The microcontroller that processes the data.
- **OBD-II Adapter**: To connect the Arduino to the car’s OBD-II port for reading data.
- **SD Card Module**: For logging driving data to an SD card.
- **Accelerometer/Gyroscope** (Optional): For detecting sudden movements, crashes, or unusual driving behavior.
- **12V to 5V DC Converter**: To safely power the Arduino from the car's 12V system.
- **Cables and Connectors**: To interface between the Arduino, OBD-II adapter, and any other sensors.

## Project Structure

- **src/**: Contains the main code for the UNOBB system.
  - This code reads data from the OBD-II port, detects anomalies, and logs data for analysis.
- **lib/**: Libraries required for OBD-II communication, sensor readings, and data logging.
- **include/**: Header files for the project.
- **test/**: Unit and integration tests for ensuring system accuracy and reliability.
- **platformio.ini**: PlatformIO configuration file for building and flashing the Arduino code.
- **.clang_complete, .gcc-flags.json**: Configuration files for the development environment.

## Installation

1. **Set Up Arduino**:
   - Connect the Arduino Uno to the OBD-II port using an OBD-II to UART adapter.
   - Connect the accelerometer/gyroscope (if used) to the Arduino to monitor car movement.
   - Optionally, connect an SD card module to store data for offline analysis.

2. **Configure PlatformIO**:
   - Open the project in the PlatformIO IDE or Visual Studio Code with the PlatformIO extension.
   - Ensure the correct board (`Arduino Uno`) is selected in `platformio.ini`.
   
3. **Upload the Code**:
   - Compile and upload the code from the `src/` directory to the Arduino.
   
4. **Power the System**:
   - Attach the Arduino to the car’s 12V power system using a 12V-to-5V converter.
   
5. **Begin Logging**:
   - Once powered on, the system will start reading data from the OBD-II port and log it. In the event of an anomaly, the data will be stored for later analysis.

## Usage

1. **Data Logging**: The system will log data about the vehicle’s speed, braking, acceleration, and other metrics to detect any irregularities.
   
2. **Anomaly Detection**: If a sudden event occurs (e.g., crash or sharp turn), the system will flag the event and log the necessary data.

3. **Post-Event Analysis**: Companies can download the data from the SD card or connect to the system to retrieve the data for review. This data can then be used to make decisions about invoices or insurance claims.

## Future Improvements

- **GPS Integration**: Add a GPS module to track the location of events or incidents.
- **Wireless Communication**: Implement Bluetooth or GSM modules for real-time data transmission to a central server.
- **Enhanced Fraud Detection**: Develop algorithms that can better detect fraudulent driving behaviors and provide alerts.
- **Data Encryption**: Secure the data storage and transmission to protect sensitive information from tampering.
