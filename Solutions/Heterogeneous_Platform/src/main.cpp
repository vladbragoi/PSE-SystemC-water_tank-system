#include "watertank.h"

int sc_main(int argc, char *argv[])
{
    watertank *wt;

    wt = new watertank("watertank");

    // TRACE FILE
    sc_trace_file *fp = sc_create_vcd_trace_file("wave");
    sca_trace_file *fp_ams = sca_create_vcd_trace_file("water");
    sc_trace(fp, wt->clk, "clk");
    sc_trace(fp, wt->rst, "rst");
    sc_trace(fp, wt->word[0], "word0");
    sc_trace(fp, wt->word[1], "word1");
    sc_trace(fp, wt->din_rdy, "din_rdy");
    sc_trace(fp, wt->result[0], "result0");
    sc_trace(fp, wt->result[1], "result1");
    sc_trace(fp, wt->dout_rdy, "dout_rdy");
    sc_trace(fp, wt->mode, "mode");

    // trace internal signals
    sc_trace(fp, wt->xtea.STATUS, "STATUS");
    sc_trace(fp, wt->xtea.counter, "counter");
    sc_trace(fp, wt->xtea.sum, "sum");
    sc_trace(fp, wt->xtea.delta, "delta");
    sc_trace(fp, wt->xtea.v0, "v0");
    sc_trace(fp, wt->xtea.v1, "v1");
    sc_trace(fp, wt->xtea.key, "key");
    sc_trace(fp, wt->xtea.sum, "sum");

    sc_start();

    sc_close_vcd_trace_file(fp);

    sc_start();

    return 0;
}