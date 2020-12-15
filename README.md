# Automatic-Fall-Detection

# Fall Detection Model

To detect the various states of motion - stand, fall, transition, and sit we used a YOLOv3 based model. The Xilinx Vitis-AI consists of several AI models, but none of the models can be used for fall detection. Therefore, we re-trained the YOLOv3 network on a custom fall detection dataset.

# Model files
We obtained the Darknet model and pre-trained weights from the YOLOv3 model (Darknet YOLOv3) and re-trained it on the custom fall detection dataset. We further used Xilinx Quantizer and Xilinx Compiler to quantize the model, and generate the compiled executable files (.elf) that can be deployed on the Xilinx ZCU104 FPGA. 
The software deployment flow from training to deploying it on the Xilinx ZCU104 FPGA is shown in the figure below

![alt text](https://github.com/Jinin03/Automatic-Fall-Detection/blob/main/Images/Hardware_software_integration.webp)

The folder board_file_zcu104_fall_256 contains the model files (.prototxt and .elf) that were deployed on the ZCU104 FPGA. 


# Live Fall Detection for Elderly Homes

Once the algorithms was ready, we integrated the software and hardware together. We took input from a live USB camera and connected it to the Xilinx ZCU104 FPGA board. A block diagram representation of the same is given below. 

![alt text](https://github.com/Jinin03/Automatic-Fall-Detection/blob/main/Images/software_flow_chain.webp)

The USB camera records video in the H.265 format, which is fed as input to the Video Codec Unit (VCU) in-built inside the ZU7EV FPGA. After the VCU processes the images, they are processed by the YOLOv3 fall detection algorithm using the Vitis AI APIs. If a fall is detected, an emergency alert SMS is sent to the relative. We used the FAST2SMS API to send messages to the emergency contact person. 

Whenever a fall is detected, the "fall_detection_video" generates a "test_sms.txt" file. Another python code "sms_send.py" running in parallel constantly checks, if the file contains any output or not. If the file contains a line "Fall Detected", immediately an SMS alert is sent to a relative. We performed live demo tests for the same. 



https://youtu.be/Ll2Qb7lwaAg

# Multi-camera implementation

