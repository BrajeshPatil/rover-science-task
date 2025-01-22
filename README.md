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
- Collect three soil samples—two of which will be tested directly on the rover, while the third sample will remain untouched and returned to the base station.
- The sample to be collected at least 10cm below the surface.
- Analysis should be conducted on both soil and atmosphere.

**Hardware Architecture**

<img src="https://github.com/user-attachments/assets/4a7da446-41b4-45cb-a813-346f8f3a9b57" alt="Hardware Architecture" style="width: 800px;">

**Mechanical Design for the Science Task**
<div style="display: flex; gap: 50px;">
  <img src="https://github.com/user-attachments/assets/25ba1a3a-6c04-4f86-8cbf-a7758d4d1227" style="height:400px;">
  <img src="https://github.com/user-attachments/assets/a7b5eeca-0aac-46d9-84c4-707d1d9a66e2" style="height:400px;">
</div>

**Component placement:**
- Nema17 placed under position 1 marked in the LHS image.
- The position 2 points to the drill motor to which the 3D printed drill is attached.
- Behind the actuator at position 3 is the ****Arduino MEGA with the shield****. Following components are present on the PCB:
  -  A4988 Stepper Motor Driver
  -  BMP180
  -  DHT22
- The SHT20 and MQ135 sensors will pr present inside the white containers for gas detection after the reaction and temperature and humidity tesing of soil.
- Position 4 points to the L298N motor drivers.
- Position 5 is the actuator.
- The MLX90614 sensor has been attached below the box pointing towards the ground.
- The right hand side image showcases the containers for storing the chemicals and the solenoid valves for pumping the chemicals whenever required.

**Working**
- We employed an MLX90614 infrared temperature sensor which was pointing towards the ground and was checking for any sudden changes in temperature.
- If sudden changes in temperature were found the particular site would be used for testing.
- Once a site is decided, soil collection will take place as follows:
    - The actuator will move downwards, and the drill will rotate in a clockwise direction. The soil sample settles on the steps of the drill as it digs into the ground.
    - The drill being still, actuator will move upwards. Now the stepper motor will move and make sure it is just below the drill.
    - The drill will now move in anti-clockwise direction and soil will be collected in the testing containers.
    - Further, some chemicals will be added to the soil. If methane gas is generate it would be detected by the MQ135 sensor prediction above life can be made.
- Same procedure will followed by finding a new location and testing soil in the other container.
- Now for the third location we dont need to test but only collect the soil and bring it to the base station untouched.
