#include <systemc.h>
#include <tlm.h>
#include "xtea_LT_testbench.h"
#include "xtea_RTL_TLM_transactor.h"
#include "xtea_RTL.h"

#define PERIOD 10

SC_MODULE(main_RTL)
{
    sc_signal<sc_logic> clk;

    void clk_gen()
    {
        while (true)
        {
            clk.write(SC_LOGIC_1);
            wait(PERIOD / 2, SC_NS);
            clk.write(SC_LOGIC_0);
            wait(PERIOD / 2, SC_NS);
        }
    }

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

    xtea_LT_testbench xtea_tb;
    xtea_RTL_TLM_transactor xtea_transactor;
    xtea_RTL xtea;

    SC_CTOR(main_RTL) : xtea_tb("xtea_tb"),
                        xtea_transactor("xtea_transactor"),
                        xtea("xtea")
    {
        SC_THREAD(clk_gen);

        // TLM testbench <-> Transactor binding (TLM interface)
        xtea_tb.initiator_socket(xtea_transactor.target_socket);

        // RTL design <-> Transactor binding (RTL interfaces)
        xtea.clk(clk);
        xtea.rst(rst);
        xtea.word0(word0);
        xtea.word1(word1);
        xtea.key0(key0);
        xtea.key1(key1);
        xtea.key2(key2);
        xtea.key3(key3);
        xtea.mode(mode);
        xtea.din_rdy(din_rdy);
        xtea.result0(result0);
        xtea.result1(result1);
        xtea.dout_rdy(dout_rdy);

        xtea_transactor.clk(clk);
        xtea_transactor.rst(rst);
        xtea_transactor.word0(word0);
        xtea_transactor.word1(word1);
        xtea_transactor.key0(key0);
        xtea_transactor.key1(key1);
        xtea_transactor.key2(key2);
        xtea_transactor.key3(key3);
        xtea_transactor.mode(mode);
        xtea_transactor.din_rdy(din_rdy);
        xtea_transactor.result0(result0);
        xtea_transactor.result1(result1);
        xtea_transactor.dout_rdy(dout_rdy);
    }
};

int sc_main(int argc, char *argv[])
{
    main_RTL *topl;

    topl = new main_RTL("topl");

    // TRACE FILE
    sc_trace_file *fp = sc_create_vcd_trace_file("wave");
    sc_trace(fp, topl->clk, "clk");
    sc_trace(fp, topl->rst, "rst");
    sc_trace(fp, topl->word0, "word0");
    sc_trace(fp, topl->word1, "word1");
    sc_trace(fp, topl->din_rdy, "din_rdy");
    sc_trace(fp, topl->result0, "result0");
    sc_trace(fp, topl->result1, "result1");
    sc_trace(fp, topl->dout_rdy, "dout_rdy");
    sc_trace(fp, topl->mode, "mode");

    // how to trace internal signals of a module:
    sc_trace(fp, topl->xtea.STATUS, "STATUS");
    sc_trace(fp, topl->xtea.counter, "counter");
    sc_trace(fp, topl->xtea.sum, "sum");
    sc_trace(fp, topl->xtea.delta, "delta");
    sc_trace(fp, topl->xtea.v0, "v0");
    sc_trace(fp, topl->xtea.v1, "v1");
    sc_trace(fp, topl->xtea.key, "key");
    sc_trace(fp, topl->xtea.sum, "sum");

    sc_start();

    sc_close_vcd_trace_file(fp);

    sc_start();

    return 0;
}