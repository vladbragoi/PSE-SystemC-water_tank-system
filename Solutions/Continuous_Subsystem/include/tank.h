//
// Created by vlad on 21/12/18.
//

#pragma once

#include <systemc-ams.h>
#include "command.h"

SC_MODULE(tank)
{
  public:
    sca_tdf::sca_in<double> valve_aperture; // feedback control
    sca_tdf::sca_out<double> water_level;

    tank(sc_core::sc_module_name);

    sca_lsf::sca_tdf::sca_source input_converter;
    sca_lsf::sca_tdf::sca_sink output_converter;

    sca_lsf::sca_sub sub;
    sca_lsf::sca_integ water_integrator;
    sca_lsf::sca_gain valve_gain;
    sca_lsf::sca_gain water_gain;

  private:
    sca_lsf::sca_signal x, x_derivative, a, sig1, sig2, sig3;
};