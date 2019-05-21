//
// Created by vlad on 14/11/18.
//

#pragma once

#include <systemc.h>

// SystemC struct
SC_MODULE(xtea_RTL) {

    // INPUTS
    sc_in<sc_logic> clk;
    sc_in<sc_uint<32>> word0;
    sc_in<sc_uint<32>> word1;
    sc_in<sc_uint<32>> key0;
    sc_in<sc_uint<32>> key1;
    sc_in<sc_uint<32>> key2;
    sc_in<sc_uint<32>> key3;
    sc_in<bool> din_rdy;
    sc_in<bool> mode;
    sc_in<bool> rst;

    // OUTPUTS
    sc_out<sc_uint<32>> result0;
    sc_out<sc_uint<32>> result1;
    sc_out<bool> dout_rdy;

    /**
     * STATES:
     *  - RESET
     *  - ST_READ   -> wait for the data input
     *  - ST_M0     -> encipher mode selected
     *  - ST_M1     -> decipher mode selected
     *  - ST_K      -> choose the 32-bit key
     *  - ST_CALC   -> perform computation for v0 and/or v1 signal
     *  - ST_SUM    -> update `sum` variable
     *  - ST_WRITE  -> write the result to the output variable
     */
    typedef enum {
        RESET,
        ST_READ,
        ST_M0,
        ST_M1,
        ST_K,
        ST_CALC,
        ST_SUM,
        ST_WRITE
    } STATES;

    // sc_signal<STATES> STATUS, NEXT_STATUS;
    sc_signal<int> STATUS, NEXT_STATUS;

    /**
     * Internal variables
     */
    sc_signal<sc_uint<32>> k;       // choose which 32-bit key to select
    sc_signal<sc_uint<32>> key;     // store the key selected
    sc_signal<sc_uint<32>> delta;   // store the delta value
    sc_signal<sc_uint<64>> sum;     // sum variable
    sc_signal<sc_uint<32>> counter; // counter variable
    sc_uint<32> v0;                 // v0 temp variable
    sc_uint<32> v1;                 // v1 temp variable

    /**
     * FSM: the     
     */
    void fsm();

    /**
     * DATAPATH: operational sub-module
     */
    void datapath();

    // SystemC module constructor
    SC_CTOR(xtea_RTL) {
        SC_METHOD(fsm);
        sensitive << STATUS;
        sensitive << din_rdy;

        SC_METHOD(datapath);
        sensitive << clk.pos() << rst.pos();
    };
};
