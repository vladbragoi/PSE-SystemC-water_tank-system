//
// Created by vlad on 21/12/18.
//

#pragma once

#include <systemc-ams.h>
#include "command.h"

SCA_TDF_MODULE(valve)
{
  public:
    sca_tdf::sca_in<int> command;
    sca_tdf::sca_in<double> aperture_threshold;
    sca_tdf::sca_out<double> aperture;

    // valve(sc_core::sc_module_name);
    // ~valve();

    SCA_CTOR(valve)
    {
        aperture.write(0.7);
        valve_aperture = 0;
    }

    void processing() override;

  private:
    double valve_aperture;
};