#include "Wt_system.h"

Wt_system::Wt_system(sc_module_name name) : sc_module(name),
                                            m_tank("Tank"),
                                            m_valve("valve"),
                                            m_controller("controller"),
                                            m_xtea("xtea"),
                                            m_tank_iface("tank_iface"),
                                            m_valve_iface("valve_iface"),
                                            m_xtea_transactor("xtea_transactor"),
                                            m_tank_transactor("watertank_transactor") {
    SC_THREAD(clk_gen);

    // TRANSACTOR: RTL -> TLM
    m_tank_transactor.water_level(water_level_rtl);

    m_controller.tank_socket(m_tank_transactor.target_socket);
    m_controller.xtea_socket(m_xtea_transactor.target_socket);

    // TRANSACTOR: XTEA
    m_xtea_transactor.clk(clk);
    m_xtea_transactor.rst(rst);
    m_xtea_transactor.mode(mode);
    m_xtea_transactor.word[0](word[0]);
    m_xtea_transactor.word[1](word[1]);
    m_xtea_transactor.key[0](key[0]);
    m_xtea_transactor.key[1](key[1]);
    m_xtea_transactor.key[2](key[2]);
    m_xtea_transactor.key[3](key[3]);
    m_xtea_transactor.din_rdy(din_rdy);
    m_xtea_transactor.dout_rdy(dout_rdy);

    // XTEA ports binding
    m_xtea.clk(clk);
    m_xtea.rst(rst);
    m_xtea.word0(word[0]);
    m_xtea.word1(word[1]);
    m_xtea.key0(key[0]);
    m_xtea.key1(key[1]);
    m_xtea.key2(key[2]);
    m_xtea.key3(key[3]);
    m_xtea.din_rdy(din_rdy);
    m_xtea.mode(mode);
    m_xtea.result0(result[0]);
    m_xtea.result1(result[1]);
    m_xtea.dout_rdy(dout_rdy);

    m_valve_iface.val0(result[0]);
    m_valve_iface.val1(result[1]);
    m_valve_iface.ams_command(command_ams);
    m_valve_iface.ams_aperture_threshold(aperture_threshold_ams);

    // VALVE ports binding
    m_valve.command(command_ams);
    m_valve.aperture_threshold(aperture_threshold_ams);
    m_valve.aperture(valve_aperture_ams);

    // TANK ports binding
    m_tank.valve_aperture(valve_aperture_ams);
    m_tank.water_level(water_level_ams);

    // TANK iface: AMS -> RTL
    m_tank_iface.ams_water_level(water_level_ams);
    m_tank_iface.rtl_water_level(water_level_rtl);

}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void Wt_system::clk_gen() {
    while (true) {
        clk.write(SC_LOGIC_1);
        wait(PERIOD / 2, SC_US);
        clk.write(SC_LOGIC_0);
        wait(PERIOD / 2, SC_US);
    }
}

#pragma clang diagnostic pop