//
// Created by vlad on 07/01/19.
//

#pragma once

#include <systemc-ams.h>

SCA_TDF_MODULE(valve_iface)
{
  public:
    sca_tdf::sca_de::sca_in<double> aperture_threshold;
    sca_tdf::sca_de::sca_in<sc_uint<32>> command;

    sca_tdf::sca_out<double> ams_aperture_threshold;
    sca_tdf::sca_out<int> ams_command;

    SCA_CTOR(valve_iface) {}

    // void set_attributes();
    void processing() override;
};