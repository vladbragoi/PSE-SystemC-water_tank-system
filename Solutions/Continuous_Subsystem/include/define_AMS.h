//
// Created by vlad on 21/12/18.
//

#pragma once

#include <systemc-ams.h>

struct iostruct
{
    typedef enum
    {
        IDLE,
        CLOSE,
        OPEN
    } COMMAND;
};

#define ADDRESS_TYPE int
#define DATA_TYPE iostruct
