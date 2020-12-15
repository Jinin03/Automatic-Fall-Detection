# Automatic-Fall-Detection

# Fall Detection Model

To detect the various states of motion - stand, fall, transition, and sit we used a YOLOv3 based model. The Xilinx Vitis-AI consists of several AI models, but none of the models can be used for fall detection. Therefore, we re-trained the YOLOv3 network on a custom fall detection dataset.

# Model files
We obtained the Darknet model and pre-trained weights from the YOLOv3 model (Darknet YOLOv3) and re-trained it on the custom fall detection dataset. We further used Xilinx Quantizer and Xilinx Compiler to quantize the model, and generate the compiled executable files (.elf) that can be deployed on the Xilinx ZCU104 FPGA. 
The software deployment flow from training to deploying it on the Xilinx ZCU104 FPGA is shown in the figure below



The folder board_file_zcu104_fall_256 contains the model files (.prototxt and .elf) that were deployed on the ZCU104 FPGA. 


