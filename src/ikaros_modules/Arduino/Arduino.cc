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
    float currentValue;
    float previousValue;
}

void Arduino::Tick()
{
    s->ReceiveBytes(rcvmsg, 8);
    std::stringstream stream(rcvmsg);
    stream >> currentValue;

    /* Serial communiction sometimes yields invalid results. Filter these out. */
    if (-30 <= currentValue <= 30 && abs(currentValue - previousValue) >= 7.5)
    {
        float value;
        value = currentValue + 150;
        output[0] = value;
        previousValue = value;
        //unsigned int microsecond = 1000000;
        //usleep(3 * microsecond); //sleeps for 3 second
        std::cout << output[0] << "\n";
    }
}

static InitClass init("Arduino", &Arduino::Create, "Source/UserModules/Arduino/");
