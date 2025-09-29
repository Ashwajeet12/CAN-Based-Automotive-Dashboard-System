# CAN-Based-Automotive-Dashboard-System

🚗 Project Overview
A distributed automotive dashboard system using Controller Area Network (CAN) protocol with three independent Electronic Control Units (ECUs) communicating over a CAN bus. 
This project demonstrates real-time vehicle data acquisition, processing, and display in an automotive environment. 

🏗️ System Architecture
ECU1 - Sensor and Input Processing Unit
Location: Vehicle input panel

Responsibilities:
Speed sensing via ADC
Gear position input via digital keypad
Collision detection
CAN data transmission

ECU2 - Engine Monitoring and Indicator Control Unit
Location: Engine compartment

Responsibilities:
RPM monitoring via ADC
Turn signal indicator control
Physical LED management
CAN data transmission

ECU3 - Dashboard Display Unit
Location: Driver dashboard
Responsibilities:
CAN data aggregation from all ECUs
Real-time LCD display
Central indicator control

System monitoring hub
