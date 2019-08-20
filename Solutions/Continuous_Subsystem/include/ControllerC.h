//
// Created by vlad on 20/12/18.
//

#pragma once

#include <systemc-ams.h>
#include "commandC.h"

SCA_TDF_MODULE(ControllerC) {
public:
    sca_tdf::sca_in<double> water_level; // feedback control
    sca_tdf::sca_out<int> command;
    sca_tdf::sca_out<double> aperture_threshold;

    explicit SCA_CTOR(ControllerC) {
        threshold = 0.7;
        samples = 0;
    }

    void set_attributes() override;

    void processing() override;

private:
    double threshold;
    uint64_t samples;
    uint64_t samples_to_wait;
};