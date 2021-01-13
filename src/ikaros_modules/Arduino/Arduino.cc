//
//  Arduino.cc
//
//
//  Created by David Jungermann on 2020-12-03.
//

#include "Arduino.h"
#include "../Kernel/IKAROS_Serial.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <unistd.h>

using namespace ikaros;

#define maxAnglePosition 330.0
#define minAnglePosition 30.0

Module *Arduino::Create(Parameter *p)
{
    return new Arduino(p);
}

Arduino::Arduino(Parameter *p) : Module(p)
{
    s = NULL;

    /* Retrieves port where Arduino is connected from class file. Default is /dev/ttyACM0 on my Ubuntu 20.10 machine. */
    s = new Serial(GetValue("port"), 9600);
}

Arduino::~Arduino()
{
    s->Close();
}

void Arduino::Init()
{
    s->Flush();
    rcvmsg = new char[1];
    output = GetOutputArray("OUTPUT");
    currentPositionArray = GetInputArray("CURRENT_POSITION");
    goalPositionArray = GetInputArray("GOAL_POSITION");
    float inputAngle;
    float previousInputAngle;
}

void Arduino::Tick()
{
    float currentPosition = currentPositionArray[0];
    float goalPosition = goalPositionArray[0];
    bool moving = abs(goalPosition - currentPosition) >= 2;

    if (!moving)
    {
        float applicableValues[8] = {-30.0, -22.5, -15.0, -7.5, 7.5, 15.0, 22.5, 30.0};
        s->ReceiveBytes(rcvmsg, 8);
        std::stringstream stream(rcvmsg);
        stream >> inputAngle;

        if (isValueInArray(inputAngle, applicableValues) && isPositionValid(inputAngle, currentPosition, goalPosition) && inputAngle != previousInputAngle)
        {
            float newHeadPosition = 0;
            newHeadPosition = currentPosition + inputAngle;
            output[0] = newHeadPosition;
            stream = std::stringstream();
            previousInputAngle = inputAngle;
            std::cout << "Input angle: " << inputAngle << "\n";
            std::cout << "New head position: " << output[0] << "\n";
            std::cout << "----------------"
                      << "\n";
        }
    }
    else
    {
        std::cout << "Moving..."
                  << "\n";
        return;
    }
}

bool Arduino::isValueInArray(float inputAngle, float applicableValues[])
{
    for (int i = 0; i < 8; i++)
    {
        if (applicableValues[i] == inputAngle)
        {
            return true;
        }
    }
    return false;
}

bool Arduino::isPositionValid(float inputAngle, float currentPosition, float goalPosition)
{
    if (goalPosition <= maxAnglePosition && goalPosition >= minAnglePosition && currentPosition + inputAngle <= maxAnglePosition && currentPosition + inputAngle >= minAnglePosition)
    {
        return true;
    }
    std::cout << "Servo too close to threshold value to rotate. "
              << "\n";
    return false;
}

static InitClass init("Arduino", &Arduino::Create, "Source/UserModules/Arduino/");