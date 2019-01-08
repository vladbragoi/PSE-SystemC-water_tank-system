//
// Created by vlad on 05/01/19.
//

#pragma once

#include <systemc-ams.h>

SCA_TDF_MODULE(tank_iface)
{
  public:
    sca_tdf::sca_in<double> ams_water_level;
    sca_tdf::sca_de::sca_out<double> rtl_water_level;

    SCA_CTOR(tank_iface) {}

    void set_attributes();
    void processing() override;
};