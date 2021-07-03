// stdafx.cpp : source file that includes just the standard includes
// E816_DLL_CONSOLE_SAMPLE.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "pzt.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

int OpenConnection(ConnectionType type)
{
    int iD = -1;
    std::string connType;
    int port = 1;
    int baud = 115200;

    switch (type)
    {
    case Dialog:
        iD = E816_InterfaceSetupDlg(NULL);
        connType = "Dialog";
        break;
    case RS232:
        iD = E816_ConnectRS232(port, baud);
        printf("\n\nE-816 on COM%d, %d Baud\n", port, baud);
        connType = "RS232";
        break;
    case USB:
        char szDevices[1000];
        int nrDevices = E816_EnumerateUSB(szDevices, 999, NULL);
        if (nrDevices <= 0)
        {
            printf("No devices connected to USB");
            break;
        }
        char* p = strtok(szDevices, "\n");
        printf("Found %d devices, connecting to first: \"%s\"\n", nrDevices, szDevices);
        iD = E816_ConnectUSB(szDevices);
        connType = "USB";
        break;
    }

    if (iD < 0)
    {
        ReportError(iD);
        std::cout << "Connect " << connType << ": ERROR" << std::endl;
    }

    return iD;
}

void PrintControllerIdentification(int iD)
{
    char szIDN[1024];

    if (!E816_qIDN(iD, szIDN, 1023)) {
        throw std::runtime_error("qIDN failed. Exiting.");
    }
    std::cout << "qIDN returned: " << szIDN << std::endl;
}

void SetServoState(int ID, std::string axis, BOOL state)
{
    if (!E816_SVO(ID, axis.c_str(), &state))
    {
        throw std::runtime_error("SVO failed. Exiting");
    }

    std::cout << "Turned servo " << (state ? "on" : "off") << std::endl;
}

void CloseConnectionWithComment(int iD, std::string comment)
{
    std::cout << comment << std::endl;

    ReportError(iD);
    E816_CloseConnection(iD);
}

double GetMinPositionLimit(int ID, std::string axis)
{
    double minPosLimit = 0;

    /*  if (!PI_qTMN(ID, axis.c_str(), &minPosLimit))
      {
          throw std::runtime_error("Unable to get minimum position limit.");
      }*/

    return minPosLimit;
}

double GetMaxPositionLimit(int ID, std::string axis)
{
    double maxPosLimit = 100;

    /*if (!PI_qTMX(ID, axis.c_str(), &maxPosLimit))
    {
        throw std::runtime_error("Unable to get maximum position limit.");
    }*/

    return maxPosLimit;
}

bool WaitForMotionDone(int ID, std::string axis)
{
    BOOL reached = FALSE;

    while (!reached)
    {
        if (!E816_qONT(ID, axis.c_str(), &reached))
        {
            throw std::runtime_error("Unable to retrieve motion state.");
        }
        //Sleep(100);
        //Sleep(10);
        Sleep(5);
    }

    return true;
}

void ReportError(int iD)
{
    int err = E816_GetError(iD);
    char szErrMsg[300];

    if (E816_TranslateError(err, szErrMsg, 299))
    {
        std::cout << "Error " << err << " occurred: " << szErrMsg << std::endl;
    }
}

void InitializeCamera(std::string path) {

}

void GetAndSavePhoto(std::string path) {

}