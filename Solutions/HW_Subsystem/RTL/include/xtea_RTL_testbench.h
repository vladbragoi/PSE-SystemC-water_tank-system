//
// Created by vlad on 21/11/18.
//

#pragma once

#include <systemc.h>
<<<<<<< HEAD
#define PERIOD 10

SC_MODULE(xtea_RTL_testbench)
{
  private:
    void run();
    void clk_gen();

  public:
=======

#define PERIOD 10

SC_MODULE(xtea_RTL_testbench) {
private:
    void run();

    void clk_gen();

public:
>>>>>>> PSE-univr-project/master
    sc_out<sc_logic> clk;
    sc_out<bool> rst;
    sc_out<sc_uint<32>> word0;
    sc_out<sc_uint<32>> word1;
    sc_out<sc_uint<32>> key0;
    sc_out<sc_uint<32>> key1;
    sc_out<sc_uint<32>> key2;
    sc_out<sc_uint<32>> key3;
    sc_out<bool> mode;
    sc_out<bool> din_rdy;

    sc_in<sc_uint<32>> result0;
    sc_in<sc_uint<32>> result1;
    sc_in<bool> dout_rdy;

<<<<<<< HEAD
    SC_CTOR(xtea_RTL_testbench)
    {
=======
    SC_CTOR(xtea_RTL_testbench) {
>>>>>>> PSE-univr-project/master
        SC_THREAD(run);
        sensitive << clk.pos();

        SC_THREAD(clk_gen);
    }
};
