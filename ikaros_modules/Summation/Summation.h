//
//    Summation.h  This file is a part of the IKAROS project
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

#ifndef SUMMATION_
#define SUMMATION_

#include "IKAROS.h"

class Summation : public Module
{

public:
    // This is all boilerplate code to declare the needed methods
    // for initialization of the module. Just change 'Summation' to
    // whatever name your module has.

    static Module *Create(Parameter *p) { return new Summation(p); }

    Summation(Parameter *p) : Module(p){};
    virtual ~Summation(){};

    void Init();
    void Tick();

    // Declare variable for size of input

    int size;

    // the input and output vectors. The storage is declared and handled by
    // Ikaros so you do not have to.

    float *input1;
    float *input2;
    float *output;
};

#endif