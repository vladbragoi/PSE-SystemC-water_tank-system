#include "wt_system.h"

int sc_main(int argc, char *argv[])
{
    wt_system *sys;

    sys = new wt_system("watertank_system");

    // TRACE FILE
    sc_trace_file *fp = sc_create_vcd_trace_file("wave");
    sca_trace_file *fp_ams = sca_create_vcd_trace_file("water");
    sc_trace(fp, sys->clk, "clk");
    sc_trace(fp, sys->rst, "rst");
    sc_trace(fp, sys->word[0], "word0");
    sc_trace(fp, sys->word[1], "word1");
    sc_trace(fp, sys->din_rdy, "din_rdy");
    sc_trace(fp, sys->result[0], "result0");
    sc_trace(fp, sys->result[1], "result1");
    sc_trace(fp, sys->dout_rdy, "dout_rdy");
    sc_trace(fp, sys->mode, "mode");

    // trace internal signals
    sc_trace(fp, sys->x.STATUS, "STATUS");
    sc_trace(fp, sys->x.counter, "counter");
    sc_trace(fp, sys->x.sum, "sum");
    sc_trace(fp, sys->x.delta, "delta");
    sc_trace(fp, sys->x.v0, "v0");
    sc_trace(fp, sys->x.v1, "v1");
    sc_trace(fp, sys->x.key, "key");
    sc_trace(fp, sys->x.sum, "sum");

    sc_start();

    sc_close_vcd_trace_file(fp);
    sca_close_vcd_trace_file(fp_ams);

    sc_start();

    return 0;
}