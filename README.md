### Pzt-Camera
The PZT is controlled to move at a fixed step length, and a series of images can be obtained by taking pictures with an industrial camera after each movement, which can be used to shoot a series of interference fringes with the same position difference.

### Require:

Spinnaker, opencv2, PZT driver file(For example, the E816 PZT requires "E816_DLL.h", "E816_DLL_x64.dll", and "E816_DLL.lib")

### Instructions:

Under the PZT driver file, pzt.h and pzt.c implement the basic functions of PZT, including: connection, initialization, movement, and release.

Under "Spinnaker", camera.h and camera.c realize the basic functions of the camera, including: connection, initialization, accessing pictures, saving pictures and release.

### Start:

MoveSample.cpp

There are three manually adjustable parameters:

'double start_position' represents the initial position of the PZT.

'int range' represents the number of PZT moves.

'double interval' represents the distance that PZT moves each time.

### Results:

Photos taken by the camera are saved in the photo folder, such as "photo/1.bmp"


### Citing code or Paper of Pzt-Camera
If you find the Pzt-Camera useful in your research, please consider staring the repository and citing code or paper:
```
Zhiyao Yin, Renhui Guo, Xin Yang, Chengxing Liu, Jianxin Li. Measurement Method for Surface Defects on ICF Capsules Based on White Light Interferometry[J]. Acta Optica Sinica, 2022, 42(10): 1012004

# or

尹智瑶, 郭仁慧, 杨鑫, 刘成兴, 李建欣. 基于白光干涉的ICF靶丸表面缺陷测量方法[J]. 光学学报, 2022, 42(10): 1012004
```

```
@article{Guo:21,
author = {Renhui Guo and Zhiyao Yin and Hang Fu and Cong Wei and Xin Yang and Jianxin Li and Jun Ma},
journal = {Opt. Express},
keywords = {Fast Fourier transforms; High numerical aperture optics; Holographic microscopy; Image fusion; Phase recovery; Surface measurements},
number = {19},
pages = {30783--30798},
publisher = {Optica Publishing Group},
title = {Surface defect measurement of ICF capsules under a limited depth of field},
volume = {29},
month = {Sep},
year = {2021},
url = {https://opg.optica.org/oe/abstract.cfm?URI=oe-29-19-30783},
doi = {10.1364/OE.433811},
abstract = {A surface defect detection device based on null interferometric microscopy (NIM) enables the measurement of surface defects in inertial confinement fusion (ICF) capsules. However, the microscope objective with a large numerical aperture in NIM causes the depth of field (DOF) of the system to be shallow, limiting the field of view (FOV) of the measurement. To expand the measurement FOV, a reconstruction method for the defocused surface defects in the FOV is presented, the angular spectrum diffraction model from the surface to the tilted plane is established, and the phase recovery method of the defocused surface defects is proposed by the theory of angular spectrum diffraction. Both the simulated and experimental results show that the proposed method can achieve the phase recovery of the surface defects in the defocused state and expand the measurement FOV, which improves the measurement accuracy and efficiency of the surface defects of the ICF capsules.},
}
```
