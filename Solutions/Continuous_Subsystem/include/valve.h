//
// Created by vlad on 21/12/18.
//

#pragma once

#include <systemc-ams.h>
#include "define_AMS.h"

SCA_TDF_MODULE(valve)
{
  public:
    sca_tdf::sca_in<int> command;
    sca_tdf::sca_in<float> aperture_threshold;
    sca_tdf::sca_out<float> valve_aperture;

    void processing();

  private:
    sca_core::sca_time time_step;
};