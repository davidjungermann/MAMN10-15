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
    int nbrOfTicks = 0;
}

void Arduino::Tick()
{
    s->Flush();
    float inputAngle;
    float currentPosition = currentPositionArray[0];
    float goalPosition = goalPositionArray[0];
    bool moving = abs(goalPosition - currentPosition) >= 2;

    if (nbrOfTicks == 0)
    {
        /* First iteration - turn head to 150 in order to prevent servo arm from attempting to turn outside of valid degrees. */
        output[0] = 150;
        nbrOfTicks++;
        return;
    }

    /* If the head is moving, we don't consider further input. */
    if (!moving)
    {
        float applicableValues[8] = {-30.0, -22.5, -15.0, -7.5, 7.5, 15.0, 22.5, 30.0};
        /* Angles are separated with X from Arduino program. */
        s->ReceiveUntil(rcvmsg, 'X');
        std::stringstream stream(rcvmsg);
        stream >> inputAngle;
        stream.str("");

        if (isValueInArray(inputAngle, applicableValues) && isPositionValid(inputAngle, currentPosition, goalPosition))
        {
            float newHeadPosition = 0;
            newHeadPosition = currentPosition + inputAngle;
            output[0] = newHeadPosition;

            std::cout << "-----------------------------"
                      << "\n";
            std::cout << "Input angle: " << inputAngle << "\n";
            std::cout << "New head position: " << newHeadPosition << "\n";
            std::cout << "-----------------------------"
                      << "\n";
        }
    }
    else
    {
        std::cout << "Moving..."
                  << "\n";
        nbrOfTicks++;
        return;
    }
    nbrOfTicks++;
}

/* Helper method to check if a value in array of applicableValues */
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

/* Serial communication can yield invalid numbers, check that the value received is correct.  */
bool Arduino::isPositionValid(float inputAngle, float currentPosition, float goalPosition)
{
    if (goalPosition <= maxAnglePosition && goalPosition >= minAnglePosition && currentPosition + inputAngle <= maxAnglePosition && currentPosition + inputAngle >= minAnglePosition)
    {
        return true;
    }
    if (nbrOfTicks != 0)
    {
        std::cout << "Servo too close to threshold value to rotate. "
                  << "\n";
    }
    return false;
}

static InitClass init("Arduino", &Arduino::Create, "Source/UserModules/Arduino/");
