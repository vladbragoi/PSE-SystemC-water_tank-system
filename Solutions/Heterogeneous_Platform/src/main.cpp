<<<<<<< HEAD
#include "wt_system.h"

int sc_main(int argc, char *argv[])
{
    wt_system *sys;

    sys = new wt_system("watertank_system");

    // TRACE FILE
    sc_trace_file *fp = sc_create_vcd_trace_file("wave");
    sca_trace_file *fp_ams = sca_create_vcd_trace_file("water");
=======
#include "Wt_system.h"


int sc_main(int argc, char *argv[]) {
    Wt_system *sys;

    sys = new Wt_system("watertank_system");

    sc_trace_file *fp = sc_create_vcd_trace_file("wave");
    sca_trace_file *fp_ams = sca_create_vcd_trace_file("water");

    // XTEA
>>>>>>> PSE-univr-project/master
    sc_trace(fp, sys->clk, "clk");
    sc_trace(fp, sys->rst, "rst");
    sc_trace(fp, sys->word[0], "word0");
    sc_trace(fp, sys->word[1], "word1");
    sc_trace(fp, sys->din_rdy, "din_rdy");
<<<<<<< HEAD
    sc_trace(fp, sys->result[0], "result0");
    sc_trace(fp, sys->result[1], "result1");
=======
    sc_trace(fp, sys->result[0], "result[0]");
    sc_trace(fp, sys->result[1], "result[1]");
>>>>>>> PSE-univr-project/master
    sc_trace(fp, sys->dout_rdy, "dout_rdy");
    sc_trace(fp, sys->mode, "mode");

    // trace internal signals
    sc_trace(fp, sys->m_xtea.STATUS, "STATUS");
    sc_trace(fp, sys->m_xtea.counter, "counter");
    sc_trace(fp, sys->m_xtea.sum, "sum");
    sc_trace(fp, sys->m_xtea.delta, "delta");
    sc_trace(fp, sys->m_xtea.v0, "v0");
    sc_trace(fp, sys->m_xtea.v1, "v1");
    sc_trace(fp, sys->m_xtea.key, "key");
    sc_trace(fp, sys->m_xtea.sum, "sum");

<<<<<<< HEAD
    sc_start();

    sc_close_vcd_trace_file(fp);
    sca_close_vcd_trace_file(fp_ams);

    sc_start();

=======
    // AMS
    sca_trace(fp_ams, sys->water_level_ams, "water_level");
    sca_trace(fp_ams, sys->aperture_threshold_ams, "aperture_threshold");
    sca_trace(fp_ams, sys->command_ams, "command");
    sca_trace(fp_ams, sys->valve_aperture_ams, "valve_aperture");

    sc_start();
    sc_close_vcd_trace_file(fp);
    sca_close_vcd_trace_file(fp_ams);

>>>>>>> PSE-univr-project/master
    return 0;
}