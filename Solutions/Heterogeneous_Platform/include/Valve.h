//
// Created by vlad on 21/12/18.
//

#pragma once

#include <systemc-ams.h>
#include "command.h"

/**
 * This module performs the valve aperture, that is a function of time and command s.t.:
 * - If the command is IDLE: d(a)/dt = 0;
 * - If the command is OPEN: d(a)/dt = 0.25;
 * - If the command is CLOSE: d(a)/dt = −0.25
 */
SCA_TDF_MODULE(Valve) {
public:
    explicit SCA_CTOR(Valve) {
        valve_aperture = 0;
    }

    void set_attributes() override;

    void processing() override;

    sca_tdf::sca_in<int> command;
    sca_tdf::sca_in<double> aperture_threshold;
    sca_tdf::sca_out<double> aperture;
private:
    double valve_aperture;
};