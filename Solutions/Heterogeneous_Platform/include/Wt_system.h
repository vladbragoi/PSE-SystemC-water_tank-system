//
// Created by vlad on 05/01/19.
//

#pragma once

#include <systemc.h>
#include <systemc-ams.h>
#include <tlm.h>
#include "Tank.h"
#include "Valve.h"
#include "Controller.h"
#include "Xtea.h"
#include "Tank_iface.h"
#include "Valve_iface.h"
#include "Transactor_xtea.h"
#include "Transactor_tank.h"

#define PERIOD 8

class Wt_system : public sc_module {
public:
    SC_HAS_PROCESS(Wt_system);

    explicit Wt_system(sc_module_name name);

    void clk_gen();

    sc_signal<sc_logic> clk;

    // AMS signals
    sca_tdf::sca_signal<double> aperture_threshold_ams;
    sca_tdf::sca_signal<double> water_level_ams;
    sca_tdf::sca_signal<double> valve_aperture_ams;
    sca_tdf::sca_signal<int> command_ams;

    // RTL signals
    sc_signal<sc_uint<32>> word[2];
    sc_signal<sc_uint<32>> key[4];
    sc_signal<bool> din_rdy;
    sc_signal<bool> mode;
    sc_signal<bool> rst;
    sc_signal<sc_uint<32>> result[2];
    sc_signal<bool> dout_rdy;
    sc_signal<double> water_level;

    // MODULES
    Tank m_tank;
    Valve m_valve;
    Controller m_controller;
    Xtea m_xtea;

    Tank_iface m_tank_iface;
    Valve_iface m_valve_iface;
    Transactor_xtea m_xtea_transactor;
    Transactor_tank m_tank_transactor;
};
