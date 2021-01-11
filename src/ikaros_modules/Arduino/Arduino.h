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
class Arduino : public Module
{
public:
    Serial *s;
    char *rcvmsg;
    Arduino(Parameter *p);
    virtual ~Arduino();
    static Module *Create(Parameter *p);
    void Init();
    void Tick();
    bool isValueInArray(float inputAngle, float applicableValues[]);
    bool isPositionValid(float inputAngle, float currentPosition, float goalPosition);
    float *output;
    float *currentPositionArray;
    float *goalPositionArray;
    float inputAngle;
    float previousInputAngle;
    float applicableValues[8];
};
#endif /* Arduino_h*/
