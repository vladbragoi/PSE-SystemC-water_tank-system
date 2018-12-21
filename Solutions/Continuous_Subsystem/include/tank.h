//
// Created by vlad on 21/12/18.
//

#pragma once

#include <systemc-ams.h>
#include "define_AMS.h"

SC_MODULE(tank)
{
  public:
    sca_tdf::sca_in<float> valve_aperture; // feedbck control
    sca_tdf::sca_out<float> water_level;

    void processing();

    sca_lsf::sca_tdf::sca_source input;
    sca_lsf::sca_tdf::sca_sink output;

  private:
    sca_core::sca_time time_step;
};