#include "camera.h"



bool MyCamera::OpenCamera()
{
    MyCamera::system = System::GetInstance();     // �½����ϵͳ
    MyCamera::cameralist = MyCamera::system->GetCameras();  // ��ȡ����б�
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
    MyCamera::pCam = MyCamera::cameralist.GetByIndex(0);   // ���ʵ����������ֻ��һ������������indexΪ��ǰ�ڼ���
    MyCamera::pCam->Init();                       // �����ʼ��
    //MyCamera::pCam->BeginAcquisition();           // ��ʼ�ɼ�ͼ��

    return TRUE;
}

void MyCamera::CloseCamera()
{
    
    //capture1.release();
    //MyCamera::pCam->EndAcquisition();   // ֹͣ�ɼ�ͼ��
    MyCamera::pCam->DeInit();      // ���ж��
    MyCamera::pCam = nullptr;      // ������ָ��
    MyCamera::cameralist.Clear();  // �������б�
    MyCamera::system->ReleaseInstance();   // �ͷ����ϵͳ
}

//ȡͼ������
void MyCamera::getImage(int imageCnt=-1)
{   

    MyCamera::pCam->BeginAcquisition();           // ��ʼ�ɼ�ͼ��
    ImagePtr pResultImage = MyCamera::pCam->GetNextImage();    // ����ͼ��ָ�벢��ȡ��һ֡ͼ��
    const size_t width = pResultImage->GetWidth();   // ͼ����
    const size_t height = pResultImage->GetHeight(); // ͼ��߶�
    //QLabel_camera->setFixedSize(width * scale, height * scale);

    // Convert image to mono 8
    ImagePtr convertedImage = pResultImage->Convert(PixelFormat_Mono8, HQ_LINEAR);   // ͼ���ʽת��

    // Create a unique filename
    if (imageCnt > -1){
        std::ostringstream filename;
        filename << "photo/"<<imageCnt << ".bmp";
        convertedImage->Save(filename.str().c_str());
        std::cout << "Image saved at " << filename.str() << std::endl;
    }
    pResultImage->Release();    // �ͷ�ͼ��ָ��
    MyCamera::pCam->EndAcquisition();   // ֹͣ�ɼ�ͼ��
}

//�ع�
void MyCamera::set_exposure_value(double e)
{
    //capture1.set(CV_CAP_PROP_EXPOSURE, e);
}
//����
void MyCamera::set_gain_value(double g)
{
    //capture1.set(CV_CAP_PROP_GAIN, g);
}
//����
void MyCamera::set_brightness_value(double b)
{
    //capture1.set(CV_CAP_PROP_BRIGHTNESS, b);
}

//�Աȶ�
void MyCamera::set_contrast_value(double c)
{
    //capture1.set(CV_CAP_PROP_CONTRAST, c);
}
//�ָ�Ĭ��ֵ
void MyCamera::set_default_parameters(double e = -6, double g = 32, double b = 0, double c = 1.0)
{
    MyCamera::set_exposure_value(e);
    MyCamera::set_gain_value(g);
    MyCamera::set_brightness_value(b);
    MyCamera::set_contrast_value(c);
}
