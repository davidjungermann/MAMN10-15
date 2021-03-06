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

using namespace ikaros;

Module *Arduino::Create(Parameter *p)
{
    return new Arduino(p);
}

Arduino::Arduino(Parameter *p) : Module(p)
{
    s = NULL;
    s = new Serial(GetValue("port"), 57600);
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
    int count = s->ReceiveBytes(rcvmsg, 100, 10);
    // std::cout << rcvmsg;
    // std::cout << "\n";
    std::stringstream stream(rcvmsg);
    int i = 0;
    while (1)
    {
        int n;
        stream >> n;
        if (!stream)
            break;
        //int val =  1024-n;
        int val = n;
        output[i] = val;
        //std::cout << val<< " ";
        i++;
    }
    //std::cout << "\n";
    // for (int i =0; i<12; i++){
    //   std::stringstream st;
    //   st << rcvmsg[i];
    //   int p;
    //   st >> p;
    //   output[i]= p;
    //   std::cout << output[i] << " ";
    //   // std::cout << "\n";
    // }
    //std::cout << "\n";
    // if(count > 0)
    //     std::cout<<rcvmsg;
    // else
    //     std::cout<<"***\n";
}

void Arduino::PrintValue()
{
    std::cout << "Value printed" << std::endl;
}

static InitClass init("Arduino", &Arduino::Create, "Source/UserModules/Arduino/");
