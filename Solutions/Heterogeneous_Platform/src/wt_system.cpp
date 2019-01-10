#include "wt_system.h"

wt_system::wt_system(sc_module_name name) : sc_module(name),
                                            t("t"),
                                            v("v"),
                                            c("c"),
                                            x("x"),
                                            t_iface("t_iface"),
                                            v_iface("v_iface"),
                                            xtea_trans("xtea_trans"),
                                            watertank_trans("watertank_trans")
{
    result[1] = 0;

    // TRANSACTOR: RTL -> TLM
    watertank_trans.water_level(water_level_rtl);
    c.watertank_socket(watertank_trans.target_socket);

    // CONTROLLER ports
    // controller.aperture_threshold(aperture_threshold_rtl);
    // controller.command(command_rtl);
    c.xtea_socket(xtea_trans.target_socket);

    // TRANSACTOR: XTEA
    xtea_trans.clk(clk);
    // xtea_transactor.rst(rst);
    xtea_trans.word[0](word[0]);
    xtea_trans.word[1](word[1]);
    xtea_trans.key[0](key[0]);
    xtea_trans.key[1](key[1]);
    xtea_trans.key[2](key[2]);
    xtea_trans.key[3](key[3]);
    xtea_trans.din_rdy(din_rdy);

    // XTEA ports
    x.clk(clk);
    x.rst(rst);
    x.word0(word[0]);
    x.word1(word[1]);
    x.key0(key[0]);
    x.key1(key[1]);
    x.key2(key[2]);
    x.key3(key[3]);
    x.din_rdy(din_rdy);
    x.mode(mode);
    x.result0(result[0]);
    x.result1(result[1]);
    x.dout_rdy(dout_rdy);

    v_iface.command(result[0]);
    v_iface.ams_command(command_ams);
    v_iface.ams_aperture_threshold(aperture_threshold_ams);

    // VALVE ports
    v.command(command_ams);
    v.aperture_threshold(aperture_threshold_ams);
    v.aperture(valve_aperture_ams);

    // TANK ports
    t.valve_aperture(valve_aperture_ams);
    t.water_level(water_level_ams);

    // TANK iface: AMS -> RTL
    t_iface.ams_water_level(water_level_ams);
    t_iface.rtl_water_level(water_level_rtl);
}

void wt_system::clk_gen()
{
    while (true)
    {
        clk.write(SC_LOGIC_1);
        wait(PERIOD / 2, SC_NS);
        clk.write(SC_LOGIC_0);
        wait(PERIOD / 2, SC_NS);
    }
}