# Rover Science Task
Module designed for in-situ soil testing directly on the rover.

# Table of Contents
- [Rover Science Task](#rover-science-task)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [About the project](#about-the-project)
    - [Requirements of the Science Module](#requirements-of-the-science-module)
    - [Working](#working)
    - [Tech Stack](#tech-stack)
    - [File Structure](#file-structure)
    - [Data Processing](#data-processing)
    - [Program Flow](#program-flow)
  - [A2DP-Sink](#a2dp-sink)
  - [Example Output](#example-output)
  - [WM8960](#wm8960)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
  - [Usage](#usage)
    - [Configuration](#configuration)
  - [Contributors](#contributors)
  - [Acknowledgements and Resources](#acknowledgements-and-resources)

# Overview
Vishwa, Vjti participated in the International Rover Challenge 2023. The rover primarily was supposed to perform four tasks: 
1. Science Task: The rover has to collect samples, perform analysis and seek signs of life.
2. Reconnaissance and Delivery Operation: The rover reconnaissance an area to search, locate, pick up, and deliver objects to specific locations.
3. Instrument Deployment and Maintenance Operation: The rover has to operate on a mock-up instrument panel to perform a set of precise operations.
4. Autonomous Mission: The rover is required to traverse between markers across moderately rugged terrain autonomously using arrow signs.

This repository primarily provides hardware designs and code samples for the **Science Task**. 

# About the project
Requirements of the Science Module:
- Collect three soil samples—two of which will be tested directly on the rover, while the third sample will remain untouched and returned to the base station.
- The sample to be collected at least 10cm below the surface.
- Analysis should be conducted on both soil and atmosphere.

Mechanical Design for the Science Task
<div style="display: flex; gap: 10px;">
  <img src="https://github.com/user-attachments/assets/505d1ccb-4033-4dc9-970c-caf54a1e185e" style="height:400px;">
  <img src="https://github.com/user-attachments/assets/cf1292f8-9e6c-47e9-9faf-bec5a3ce0b93" style="height:400px;">
</div>

Working
- We employed an MLX90614 infrared temperature sensor which was pointing towards the ground and was checking for any sudden changes in temperature.
- If sudden changes in temperature were found the particular site would be used for testing.
- Once a site is decided, soil collection will take place as follows:
    - The actuator will move downwards, and the drill will rotate in a clockwise direction. The soil sample settles on the steps of the drill as it digs into the ground.
    - The drill being still, actuator will move upwards. Now the stepper motor will move and make sure it is just below the drill.
    - The drill will now move in anti-clockwise direction and soil will be collected in the testing containers.
    - Further, some chemicals will be added to the soil. If methane gas is generate it would be detected by the MQ135 sensor prediction above life can be made.
- Same procedure will followed by finding a new location and testing soil in the other container.
- Now for the third location we dont need to test but only collect the soil and bring it to the base station untouched.

File Structure

.
├── hardware                    # Contains data sheets and PCB manufacturing files
│   ├── datasheets              # Data sheets for sensors and components
│   ├── pcb                     # PCB-related files
│   │   ├── PCB_Gerber_Files    # Gerber files for PCB manufacturing
│   ├── README.md               # Information about hardware components and designs
├── lib                           # Libraries used in the project
│   ├── AccelStepper-1.64.0.zip  # Stepper motor library
│   ├── Adafruit_BMP085_Library-1.2.4.zip  # Library for BMP085 sensor
│   ├── Adafruit_MLX90614_Library-2.1.5.zip  # Library for MLX90614 sensor
│   ├── DFRobot_SHT20-1.0.0.zip  # Library for SHT20 sensor
│   ├── DHT-sensor-library-master.zip  # DHT sensor library
│   ├── MQ135-1.1.1.zip  # MQ135 air quality sensor library
│   ├── README.md   # Documentation for libraries used
├── src                           # Source code for the rover project
│   ├── science_task.ino  # Main sketch for the Science Task
├── LICENSE                       # License file for the project
└── README.md                     # Main README file for the repository

