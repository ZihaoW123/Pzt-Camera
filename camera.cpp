#include "camera.h"



bool MyCamera::OpenCamera()
{
    MyCamera::system = System::GetInstance();     // 新建相机系统
    MyCamera::cameralist = MyCamera::system->GetCameras();  // 获取相机列表
    const unsigned int numCameras = cameralist.GetSize();
    std::cout << "Number of cameras detected: " << numCameras << std::endl << std::endl;
    if (numCameras == 0)
    {
        // Clear camera list before releasing system
        MyCamera::cameralist.Clear();

        // Release system
        system->ReleaseInstance();

        std::cout << "Not enough cameras!" << std::endl;
        std::cout << "Done! Press Enter to exit..." << std::endl;
        getchar();

        return FALSE;
    }
    MyCamera::pCam = nullptr;
    MyCamera::pCam = MyCamera::cameralist.GetByIndex(0);   // 相机实例化，由于只有一个相机，相机的index为当前第几个
    MyCamera::pCam->Init();                       // 相机初始化
    //MyCamera::pCam->BeginAcquisition();           // 开始采集图像

    return TRUE;
}

void MyCamera::CloseCamera()
{
    
    //capture1.release();
    //MyCamera::pCam->EndAcquisition();   // 停止采集图像
    MyCamera::pCam->DeInit();      // 相机卸载
    MyCamera::pCam = nullptr;      // 清空相机指针
    MyCamera::cameralist.Clear();  // 清空相机列表
    MyCamera::system->ReleaseInstance();   // 释放相机系统
}

//取图并保存
void MyCamera::getImage(int imageCnt=-1)
{   

    MyCamera::pCam->BeginAcquisition();           // 开始采集图像
    ImagePtr pResultImage = MyCamera::pCam->GetNextImage();    // 创建图像指针并获取下一帧图像
    const size_t width = pResultImage->GetWidth();   // 图像宽度
    const size_t height = pResultImage->GetHeight(); // 图像高度
    //QLabel_camera->setFixedSize(width * scale, height * scale);

    // Convert image to mono 8
    ImagePtr convertedImage = pResultImage->Convert(PixelFormat_Mono8, HQ_LINEAR);   // 图像格式转换

    // Create a unique filename
    if (imageCnt > -1){
        std::ostringstream filename;
        filename << "photo/"<<imageCnt << ".bmp";
        convertedImage->Save(filename.str().c_str());
        std::cout << "Image saved at " << filename.str() << std::endl;
    }
    pResultImage->Release();    // 释放图像指针
    MyCamera::pCam->EndAcquisition();   // 停止采集图像
}

//曝光
void MyCamera::set_exposure_value(double e)
{
    //capture1.set(CV_CAP_PROP_EXPOSURE, e);
}
//增益
void MyCamera::set_gain_value(double g)
{
    //capture1.set(CV_CAP_PROP_GAIN, g);
}
//亮度
void MyCamera::set_brightness_value(double b)
{
    //capture1.set(CV_CAP_PROP_BRIGHTNESS, b);
}

//对比度
void MyCamera::set_contrast_value(double c)
{
    //capture1.set(CV_CAP_PROP_CONTRAST, c);
}
//恢复默认值
void MyCamera::set_default_parameters(double e = -6, double g = 32, double b = 0, double c = 1.0)
{
    MyCamera::set_exposure_value(e);
    MyCamera::set_gain_value(g);
    MyCamera::set_brightness_value(b);
    MyCamera::set_contrast_value(c);
}
