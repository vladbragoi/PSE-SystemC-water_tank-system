#include "system.h"

system::system(sc_module_name name) : sc_module(name),
                                      tank("tank"),
                                      valve("valve"),
                                      controller("controller"),
                                      xtea("xtea"),
                                      tank_iface("tank_interface"),
                                      valve_iface("valve_iface"),
                                      xtea_transactor("xtea_transactor"),
                                      watertank_transactor("watertank_transactor")
{
    // TRANSACTOR: RTL -> TLM
    watertank_transactor.water_level(water_level_rtl);
    controller.watertank_socket(watertank_transactor.target_socket);

    // CONTROLLER ports
    // controller.aperture_threshold(aperture_threshold_rtl);
    // controller.command(command_rtl);
    controller.xtea_socket(xtea_transactor.target_socket);

    // TRANSACTOR: XTEA
    xtea_transactor.clk(clk);
    xtea_transactor.rst(rst);
    xtea_transactor.word[0](word[0]);
    xtea_transactor.word[1](word[1]);
    xtea_transactor.key[0](key[0]);
    xtea_transactor.key[1](key[1]);
    xtea_transactor.key[2](key[2]);
    xtea_transactor.key[3](key[3]);
    xtea_transactor.din_rdy(din_rdy);
    xtea_transactor.mode(mode);

    // XTEA ports
    xtea.clk(clk);
    xtea.rst(rst);
    xtea.word0(word[0]);
    xtea.word1(word[1]);
    xtea.key0(key[0]);
    xtea.key1(key[1]);
    xtea.key2(key[2]);
    xtea.key3(key[3]);
    xtea.din_rdy(din_rdy);
    xtea.mode(mode);
    xtea.result0(result[0]);
    xtea.result1(result[1]);
    xtea.dout_rdy(dout_rdy);

    valve_iface.command(result[0]);
    valve_iface.ams_command(command_ams);
    valve_iface.ams_aperture_threshold(aperture_threshold_ams);

    // VALVE ports
    valve.command(command_ams);
    valve.aperture_threshold(aperture_threshold_ams);
    valve.aperture(valve_aperture_ams);

    // TANK ports
    tank.valve_aperture(valve_aperture_ams);
    tank.water_level(water_level_ams);

    // TANK iface: AMS -> RTL
    tank_iface.ams_water_level(water_level_ams);
    tank_iface.rtl_water_level(water_level_rtl);
}

void system::clk_gen()
{
    while (true)
    {
        clk.write(SC_LOGIC_1);
        wait(PERIOD / 2, SC_NS);
        clk.write(SC_LOGIC_0);
        wait(PERIOD / 2, SC_NS);
    }
}