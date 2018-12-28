//
// Created by vlad on 20/12/18.
//

#pragma once

#include <systemc-ams.h>
#include "command.h"

SCA_TDF_MODULE(controller)
{
  public:
    sca_tdf::sca_in<double> water_level; // feedbck control
    sca_tdf::sca_out<int> command;
    sca_tdf::sca_out<double> aperture_threshold;

    // controller(sc_core::sc_module_name);
    // ~controller();

    SCA_CTOR(controller)
    {
        threshold = 0.7;
        aperture_threshold.write(threshold);
    }

    void processing() override;

  private:
    double threshold;
    sca_core::sca_time time_step;
};