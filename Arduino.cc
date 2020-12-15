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
    rcvmsg = new char[100];
    output = GetOutputArray("OUTPUT");
}

void Arduino::Tick()
{
    int count = s->ReceiveBytes(rcvmsg, 100);
    std::cout << rcvmsg;
    std::cout << "\n";
    std::stringstream stream(rcvmsg);
    int i = 0;
    while (1)
    {
        int n;
        stream >> n;
        if (!stream)
            break;
        int val = n;
        output[i] = val;
        std::cout << val << " ";
        i++;
    }
}

void Arduino::PrintValue()
{
    std::cout << "Value printed" << std::endl;
}

static InitClass init("Arduino", &Arduino::Create, "Source/UserModules/Arduino/");
