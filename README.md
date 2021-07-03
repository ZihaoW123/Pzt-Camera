# Pzt-Camera
The PZT is controlled to move at a fixed step length, and a series of images can be obtained by taking pictures with an industrial camera after each movement, which can be used to shoot a series of interference fringes with the same position difference.

Require:
Spinnaker, opencv2, PZT driver file("E816_DLL.h")

Start:

MoveSample.cpp
There are three manually adjustable parameters:
'double start_position' represents the initial position of the PZT
'int range' represents the number of PZT moves
'double interval' represents the distance that PZT moves each time.

Results:
Photos taken by the camera are saved in the photo folder, such as "photo/1.bmp"
