//
// Created by vlad on 21/12/18.
//

#pragma once

#include <systemc-ams.h>
#include "commandC.h"

SCA_TDF_MODULE(ValveC) {
public:
    sca_tdf::sca_in<int> command;
    sca_tdf::sca_in<double> aperture_threshold;
    sca_tdf::sca_out<double> aperture;

    explicit SCA_CTOR(ValveC) {
        valve_aperture = 0;
    }

    void set_attributes() override;

    void processing() override;

private:
    double valve_aperture;
};