//
//    Summation.cc  This file is a part of the IKAROS project
//    Pointless example module summing its inputs.
//
//    Copyright (C) 2001-2011 Jan Morén
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// Created: 2001-12-01
//
// 2003-01-14 and 2007-01-01 Updated for the new simulator

#include "Summation.h"

void Summation::Init()
{
    size = GetInputSize("INPUT1");
    input1 = GetInputArray("INPUT1");
    input2 = GetInputArray("INPUT2");
    output = GetOutputArray("OUTPUT");
}

void Summation::Tick()
{
    int i;

    // Summation in action. input1 and input2 are pointers to the current input
    // vectors and output points to the output vector that will be sent
    // along to whatever modules it is connected to.

    for (i = 0; i < size; i++)
    {
        output[i] = input1[i] + input2[i];
    }
}

// Install the module. This code is executed during start-up.

static InitClass init("Summation", &Summation::Create, "Source/UserModules/Summation/");