// E816_DLL_CONSOLE_SAMPLE.cpp : Defines the entry point for the console application.
//

#ifdef WIN32
#include "stdafx.h"
#include "pzt.h"
#include "camera.h"
#include "conio.h" // for getch()
#include <Windows.h>
#else
#include <stdlib.h>
#include <stdio.h>
#endif

#define SINGLE_AXIS 1
#define INTERFACE_USB

int main(int argc, char* argv[])
{
    // try to open communication
    int ID = -1;
#ifdef INTERFACE_RS232
    ID = OpenConnection(RS232)
#endif
#ifdef INTERFACE_SETUP_DLG
    ID = OpenConnection(Dialog);
#endif
#ifdef INTERFACE_USB
    ID = OpenConnection(USB);
#endif

    if (ID < 0)
    {
        std::cout << "Unable to connect.";
        return 1;
    }

    MyCamera camera;
    if (!camera.OpenCamera())
    {
        throw std::runtime_error("Unable to Open Camera.");
    };

    try
    {
        PrintControllerIdentification(ID);
        ////////////////////////////////////////////////////////////////////////////////
        char* sspa = "AAAAAAAAAA";
        double spa[10];
        int spacmd[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        int svo[2] = { 1, 1 };

        char sSAI[1024];
        if (!E816_qSAI(ID, sSAI, 1023)) ReportError(ID); 
        printf("SAI?: \"%s\"\n\n", sSAI);

        printf("SPA TEST ");
        if (!E816_qSPA(ID, sspa, spacmd, spa)) ReportError(ID); 
        printf("SPA for A:");
        for (int i = 0; i < 10; i++)
            printf("   %d:%f\n", i + 1, spa[i]);
        ////////////////////////////////////////////////////////////////////////////////

        std::string sAxis = "A";
        SetServoState(ID, sAxis, SERVO_ON);

        double minPosLimit = GetMinPositionLimit(ID, sAxis);
        double maxPosLimit = GetMaxPositionLimit(ID, sAxis);


        double initial_pos = 0.0;
        if (!E816_qPOS(ID, sAxis.c_str(), &initial_pos)) ReportError(ID);
        printf("Pzt initial position%8.4f\n", initial_pos);


        //double start_position = 35.2;  // Initial Position


       double start_position = 36.4;  // 50-0.068*200 Change  NO.1

        if (!E816_MOV(ID, sAxis.c_str(), &start_position))
        {
            throw std::runtime_error("Unable to approach initial_position.");
        }
        WaitForMotionDone(ID, sAxis);
        printf("Pzt move to start position%8.4f\n", start_position);

        int range = 400;
        double interval = 0.068;   // White Light 60nm   NO.1
        double targetPos = start_position;
         for (int i=0; i<range; i++)
        {
            //if (!(i%10)) printf(".");
            targetPos = targetPos + interval;
            if ((targetPos < minPosLimit) || (targetPos > maxPosLimit)){
                throw std::runtime_error("Unable to approach minimum or Maximum position limit.");
            }

            if(! E816_MOV(ID, sAxis.c_str(), &targetPos))
            {
                throw std::runtime_error("Unable to approach tgt position.");
            }

            WaitForMotionDone(ID, sAxis);

            
            //Sleep(10);
            double pos=0.0;
            for (int j=0; j<2; j++)
            {
                if (! E816_qPOS(ID, sAxis.c_str(), &pos) ) ReportError(ID);
                printf("postion %d Current position of E-816: ", i);
                printf("B = %8.4f\n", pos);
            }
            camera.getImage(i);
            
        }

         if (!E816_MOV(ID, sAxis.c_str(), &initial_pos))
             throw std::runtime_error("Unable to approach tgt position.");
         WaitForMotionDone(ID, sAxis);
         double end_pos = 0.0;
         if (!E816_qPOS(ID, sAxis.c_str(), &end_pos)) ReportError(ID);
         printf("Pzt back to the initial position%8.4f\n", end_pos);

         SetServoState(ID, sAxis, SERVO_OFF); 
         

         E816_CloseConnection(ID);
         std::cout << "Closing Pzt connection." << std::endl;
         camera.CloseCamera();
         std::cout << "Closing Camera connection." << std::endl;

    }
    catch (std::runtime_error e)
    {
        CloseConnectionWithComment(ID, e.what());
        camera.CloseCamera();
        return 1;
    }
    return 0;
}
    

