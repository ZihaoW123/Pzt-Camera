// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#include <iostream>
#include <tchar.h>

#include <windows.h>
#include <string>
#include <time.h>
#include <vector>

#include <opencv2/opencv.hpp>
#include <Spinnaker.h>

#include "E816_DLL.h"
//#include "PI_GCS2_DLL.h"

const BOOL SERVO_ON = TRUE;
const BOOL SERVO_OFF = FALSE;

enum ConnectionType
{
    Dialog,
    RS232,
    USB
};


int OpenConnection(ConnectionType type);
void PrintControllerIdentification(int iD);
void CloseConnectionWithComment(int iD, std::string comment);


double GetMinPositionLimit(int ID, std::string axis);
double GetMaxPositionLimit(int ID, std::string axis);
bool WaitForMotionDone(int ID, std::string axis);

void GetAndSavePhoto(std::string path);

void SetServoState(int ID, std::string axis, BOOL state);
void ReportError(int iD);