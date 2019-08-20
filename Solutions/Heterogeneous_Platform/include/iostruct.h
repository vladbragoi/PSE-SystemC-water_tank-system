//
// Created by vlad on 05/01/19.
//

#pragma once

<<<<<<< HEAD
struct xtea_data
{
    sc_uint<32> word[2];
    sc_uint<32> key[4];
};

struct tank_data
{
    double water_level;
};
=======
#include <systemc.h>

typedef struct {
    /**
     * Should be a vector of length 2
     */
    sc_uint<32> command[2];

    /**
     * Should be a vector of length 2
     */
    sc_uint<32> threshold[2];
} xtea_data;

typedef struct {
    double water_level;
} tank_data;

enum {
    ENCRYPT = 0,
    DECRYPT = 1
} MODE;
>>>>>>> PSE-univr-project/master
