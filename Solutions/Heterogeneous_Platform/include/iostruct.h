//
// Created by vlad on 05/01/19.
//

#pragma once

struct xtea_data
{
    sc_uint<32> word[2];
    sc_uint<32> key[4];
};

struct tank_data
{
    double water_level;
};
