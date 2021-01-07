//
//  Arduino.h
//
//
//  Created by David Jungermann on 2020-12-03.
//

#ifndef Arduino_
#define Arduino_

#include "IKAROS.h"
#include "stdio.h"
class Arduino: public Module
{
public:
    Serial *s;
    char    *rcvmsg;
    Arduino(Parameter * p);
    virtual ~Arduino();
    static Module *Create(Parameter * p);
    void Init();
    void Tick();
    float *	output;
};
#endif /* Arduino_h*/
