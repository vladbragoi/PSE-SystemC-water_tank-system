//
// Created by vlad on 05/01/19.
//

#pragma once

#include <systemc.h>
#include <systemc-ams.h>
#include <tlm.h>
#include "tank.h"
#include "valve.h"
#include "controller.h"
#include "xtea.h"
#include "tank_iface.h"
#include "valve_iface.h"
#include "transactor_xtea.h"
#include "transactor_watertank.h"

#define PERIOD 10

class wt_system : public sc_module
{
  public:
    sc_signal<sc_logic> clk;

    void clk_gen();

    // AMS signals
    sca_tdf::sca_signal<double> aperture_threshold_ams;
    sca_tdf::sca_signal<double> water_level_ams;
    sca_tdf::sca_signal<double> valve_aperture_ams;
    sca_tdf::sca_signal<int> command_ams;

    sc_signal<double> aperture_threshold_rtl;
    sc_signal<double> water_level_rtl;
    // sc_signal<int> command_rtl;

    // RTL signals
    sc_signal<sc_uint<32>> word[2];
    sc_signal<sc_uint<32>> key[4];
    sc_signal<bool> din_rdy;
    sc_signal<bool> mode;
    sc_signal<bool> rst;
    sc_signal<sc_uint<32>> result[2];
    sc_signal<bool> dout_rdy;

    tank m_tank;
    valve m_valve;
    controller m_controller;
    xtea m_xtea;

    tank_iface m_tank_iface;
    valve_iface m_valve_iface;
    transactor_xtea m_xtea_transactor;
    transactor_watertank m_watertank_transactor;

    SC_HAS_PROCESS(wt_system);
    wt_system(sc_module_name name);
    // ~system();
};
