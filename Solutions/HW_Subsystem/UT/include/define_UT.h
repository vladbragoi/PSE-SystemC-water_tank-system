//
// Created by vlad on 18/12/18.
//

#pragma once

#include <systemc.h>

<<<<<<< HEAD
struct iostruct
{
=======
struct iostruct {
>>>>>>> PSE-univr-project/master
    sc_uint<32> word0;
    sc_uint<32> word1;
    sc_uint<32> key0;
    sc_uint<32> key1;
    sc_uint<32> key2;
    sc_uint<32> key3;
    bool mode;

    sc_uint<32> result0;
    sc_uint<32> result1;
};
<<<<<<< HEAD

#define ADDRESS_TYPE int
#define DATA_TYPE iostruct
=======
>>>>>>> PSE-univr-project/master
