#pragma once
#include <iostream>
#include <sstream>
#include <tchar.h>

#include <windows.h>
#include <string>
#include <time.h>
#include <vector>

#include <opencv2/opencv.hpp>
#include <Spinnaker.h>


using namespace Spinnaker;
using namespace cv;

class MyCamera
{
public:
    //��������Ϊ������
    
    bool OpenCamera();
    void getImage(int imageCnt);
    void CloseCamera();
    void set_exposure_value(double e);
    void set_gain_value(double g);
    void set_brightness_value(double b);
    void set_contrast_value(double c);
    void set_default_parameters(double e, double d, double b, double c);

private:
    //��������Ϊ������
   Mat frame;             // �����������ı���
    SystemPtr system;      // ���ϵͳ����
    CameraList cameralist; // ����б����
    CameraPtr pCam = nullptr;// ���ָ�����
    double value_exposure;
    double value_gain;
    double value_brightness;
    double value_contrast;

};