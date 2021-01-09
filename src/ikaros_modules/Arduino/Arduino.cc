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
    float value;
}

void Arduino::Tick()
{
    s->ReceiveBytes(rcvmsg, 8);
    std::stringstream stream(rcvmsg);
    stream >> value;

    /* Hopefully this adds the last value to the output array. */
    if (value >= 30)
    {
        output[0] = value;
        std::cout << output[0] << "\n";
    }
}

static InitClass init("Arduino", &Arduino::Create, "Source/UserModules/Arduino/");
