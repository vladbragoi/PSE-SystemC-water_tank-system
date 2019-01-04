#include <xtea_RTL_testbench.h>
#include "xtea_RTL.h"

int sc_main(int argc, char *argv[])
{

    sc_signal<sc_logic> clk;

    sc_signal<sc_uint<32>> word0;
    sc_signal<sc_uint<32>> word1;
    sc_signal<sc_uint<32>> key0;
    sc_signal<sc_uint<32>> key1;
    sc_signal<sc_uint<32>> key2;
    sc_signal<sc_uint<32>> key3;
    sc_signal<bool> din_rdy;
    sc_signal<bool> mode;
    sc_signal<bool> rst;

    sc_signal<sc_uint<32>> result0;
    sc_signal<sc_uint<32>> result1;
    sc_signal<bool> dout_rdy;

    // XTEA
    xtea_RTL xtea("xtea");

    xtea.clk(clk);
    xtea.mode(mode);
    xtea.rst(rst);
    xtea.din_rdy(din_rdy);
    xtea.word0(word0);
    xtea.word1(word1);
    xtea.key0(key0);
    xtea.key1(key1);
    xtea.key2(key2);
    xtea.key3(key3);
    xtea.result0(result0);
    xtea.result1(result1);
    xtea.dout_rdy(dout_rdy);

    // TESTBENCH
    xtea_RTL_testbench xtea_tb("xtea_tb");

    xtea_tb.clk(clk);
    xtea_tb.mode(mode);
    xtea_tb.rst(rst);
    xtea_tb.word0(word0);
    xtea_tb.word1(word1);
    xtea_tb.key0(key0);
    xtea_tb.key1(key1);
    xtea_tb.key2(key2);
    xtea_tb.key3(key3);
    xtea_tb.din_rdy(din_rdy);
    xtea_tb.result0(result0);
    xtea_tb.result1(result1);
    xtea_tb.dout_rdy(dout_rdy);

    // TRACE FILE
    sc_trace_file *fp = sc_create_vcd_trace_file("wave");
    sc_trace(fp, clk, "clk");
    sc_trace(fp, rst, "rst");
    sc_trace(fp, word0, "word0");
    sc_trace(fp, word1, "word1");
    sc_trace(fp, din_rdy, "din_rdy");
    sc_trace(fp, result0, "result0");
    sc_trace(fp, result1, "result1");
    sc_trace(fp, dout_rdy, "dout_rdy");
    sc_trace(fp, mode, "mode");

    // how to trace internal signals of a module:
    sc_trace(fp, xtea.STATUS, "STATUS");
    sc_trace(fp, xtea.counter, "counter");
    sc_trace(fp, xtea.sum, "sum");
    sc_trace(fp, xtea.delta, "delta");
    sc_trace(fp, xtea.v0, "v0");
    sc_trace(fp, xtea.v1, "v1");
    sc_trace(fp, xtea.key, "key");
    sc_trace(fp, xtea.sum, "sum");

    sc_start();

    sc_close_vcd_trace_file(fp);

    return 0;
}