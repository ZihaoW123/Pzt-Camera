# Pzt-Camera
The PZT is controlled to move at a fixed step length, and a series of images can be obtained by taking pictures with an industrial camera after each movement, which can be used to shoot a series of interference fringes with the same position difference.

Require:

Spinnaker, opencv2, PZT driver file(For example, the E816 PZT requires "E816_DLL.h", "E816_DLL_x64.dll", and "E816_DLL.lib")

Instructions:

Under the PZT driver file, pzt.h and pzt.c implement the basic functions of PZT, including: connect, initialize, move, and end release.

Under "Spinnaker", camera.h and camera.c realize the basic functions of the camera, including: connection, initialization, access to pictures, save pictures and end the release.

Start:

MoveSample.cpp
There are three manually adjustable parameters:
'double start_position' represents the initial position of the PZT
'int range' represents the number of PZT moves
'double interval' represents the distance that PZT moves each time.

Results:

Photos taken by the camera are saved in the photo folder, such as "photo/1.bmp"


```bibtex
@misc{
  PZT_Camera,
  title   = {Attention Is All You Need},
  author  = {Zihao Wang, Zhiyao Yin},
  year    = {2021},
  publisher = {GitHub},
  journal = {GitHub repository},
  howpublished = {\url{https://github.com/ZihaoW123/Pzt-Camera/}}
}
```
