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
    float currentInputAngle;
    float newInputAngle;
    float currentHeadPosition;
    float newHeadPosition;
}

void Arduino::Tick()
{
    /* Den tickar varje gång och sätter värdet + vinkeln varje gång, därför vi antingen alltid kommer till 30 eller 330.  */
    /* Ett annat problem är att den rör sig, och sen tar in nya värden innan den är framme. */

    float applicableValues[8] = {-30.0, -22.5, -15.0, -7.5, 7.5, 15.0, 22.5, 30.0};
    s->ReceiveBytes(rcvmsg, 8);
    std::stringstream stream(rcvmsg);
    stream >> newInputAngle;

    /* Serial communiction sometimes yields invalid results. Filter these out. */

    if (stream)
    {
        if (isValueInArray(newInputAngle, applicableValues))
        {
            if (newInputAngle >= 0)
            {
                newHeadPosition = min(newInputAngle + currentHeadPosition, maxAnglePosition);
            }
            else
            {
                newHeadPosition = max(newInputAngle + currentHeadPosition, minAnglePosition);
            }

            output[0] = newHeadPosition;
            currentInputAngle = newInputAngle;
            currentHeadPosition = newHeadPosition;
            std::cout << output[0] << "\n";
        }
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

static InitClass init("Arduino", &Arduino::Create, "Source/UserModules/Arduino/");
