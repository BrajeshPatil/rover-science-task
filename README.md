# Rover Science Task
Module designed for in-situ soil testing directly on the rover.

# Overview
Vishwa, Vjti participated in the International Rover Challenge 2023. The rover primarily was supposed to perform four tasks: 
1. Science Task: The rover has to collect samples, perform analysis and seek signs of life.
2. Reconnaissance and Delivery Operation: The rover reconnaissance an area to search, locate, pick up, and deliver objects to specific locations.
3. Instrument Deployment and Maintenance Operation: The rover has to operate on a mock-up instrument panel to perform a set of precise operations.
4. Autonomous Mission: The rover is required to traverse between markers across moderately rugged terrain autonomously using arrow signs.

This repository primarily provides hardware designs and code samples for the **Science Task**. 

# About the project
**Requirements of the Science Module:**
- Sample Collection:
  - Collect three soil samples:
    1. Two samples tested directly on the rover.
    2. One sample returned to the base station untouched.
  - Samples must be collected from at least 10 cm below the surface.
- Analysis:
  - Conduct tests on both soil and atmosphere.

**Hardware Architecture**

<img src="https://github.com/user-attachments/assets/f27057eb-0e8e-4ae2-a33c-66cae70ec69e" alt="Hardware Architecture" style="width: 600px;">

**Mechanical Design for the Science Task**
<div style="display: flex; gap: 50px;">
  <img src="https://github.com/user-attachments/assets/25ba1a3a-6c04-4f86-8cbf-a7758d4d1227" style="height:400px;">
  <img src="https://github.com/user-attachments/assets/a7b5eeca-0aac-46d9-84c4-707d1d9a66e2" style="height:400px;">
</div>

**Component placement:**
- Position 1: Nema17 stepper motor placed under the marked area in the left-hand side (LHS) image.
- Position 2: Drill motor with a 3D-printed drill attached.
- Position 3: Behind the actuator lies the Arduino MEGA with the shield. Components on the PCB include:
  - A4988 Stepper Motor Driver
  - BMP180
  - DHT22
- Other Sensors:
  - SHT20 and MQ135 are placed inside white containers for gas detection (post-reaction) and soil temperature and humidity testing.
- Position 4: L298N motor drivers.
- Position 5: Actuator.
- MLX90614: Infrared temperature sensor placed below the box, pointing towards the ground.
- Chemical Storage and Pumping:
  - The right-hand side (RHS) image shows chemical containers and solenoid valves for pumping chemicals as needed.

**Working**
1. Site Identification:
    - The MLX90614 infrared temperature sensor scans the ground for sudden changes in temperature.
    - If significant temperature changes are detected, the site is selected for testing.
2. Soil Collection:
    - The actuator moves downward while the drill rotates clockwise, digging into the ground.
    - Soil samples settle on the steps of the drill.
    - Once the sample is collected, the actuator moves upwards, keeping the drill stationary.
    - The stepper motor ensures the testing container is positioned directly beneath the drill.
3. Soil Transfer:
    - The drill rotates counter-clockwise to release soil into the testing containers.
4. Chemical Testing:
    - Chemicals are added to the soil.
    - If methane gas is detected (via the MQ135 sensor), the presence of life can be inferred.
5. Repetition:
    - The above procedure is repeated for a second site to test another soil sample in a new container.
6. Sample Return:
    - For the third location, the soil is collected without testing and returned to the base station untouched.

# File Structure
```
.
├───hardware                                  # Directory containing hardware-related files and documentation
│   ├───datasheets                            # Folder containing datasheets for various components
│   └───pcb                                   # Folder containing PCB design files and documentation
│       │   README.md                         # General information about the Arduino MEGA Shield
│       └───PCB_Gerber_Files                  # Gerber files used for PCB manufacturing
├───lib                                       # Directory containing library files used in projects
│       AccelStepper-1.64.0.zip               # AccelStepper library version 1.64.0
│       Adafruit_BMP085_Library-1.2.4.zip     # Adafruit BMP085 library version 1.2.4
│       Adafruit_MLX90614_Library-2.1.5.zip   # Adafruit MLX90614 library version 2.1.5
│       DFRobot_SHT20-1.0.0.zip               # DFRobot SHT20 library version 1.0.0
│       DHT-sensor-library-master.zip         # DHT sensor library
│       MQ135-1.1.1.zip                       # MQ135 sensor library version 1.1.1
│       README.md                             # General information about libraries included
├───src                                       # Directory containing the main source code for the project
|       science_task.ino                      # Main Arduino sketch for the science task implementation
├───LICENSE                                   # License file for the project
├───README.md                                 # General information about the project
```
