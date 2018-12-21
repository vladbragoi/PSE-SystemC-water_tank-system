//
// Created by vlad on 20/12/18.
//

#pragma once

#include <systemc-ams.h>
#include "define_AMS.h"

SCA_TDF_MODULE(controller)
{
  public:
    sca_tdf::sca_in<float> water_level; // feedbck control
    sca_tdf::sca_out<int> command;
    sca_tdf::sca_out<float> aperture_threshold;

    void processing();

  private:
    sca_core::sca_time time_step;
};