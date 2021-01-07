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
    rcvmsg = new char[8];
    output = GetOutputArray("OUTPUT");
}

void Arduino::Tick()
{
    int count = s->ReceiveBytes(rcvmsg, 8);
    std::cout << rcvmsg;
}

static InitClass init("Arduino", &Arduino::Create, "Source/UserModules/Arduino/");
