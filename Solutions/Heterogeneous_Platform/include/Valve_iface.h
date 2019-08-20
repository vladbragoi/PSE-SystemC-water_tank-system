//
// Created by vlad on 07/01/19.
//

#pragma once

#include <systemc-ams.h>

SCA_TDF_MODULE(Valve_iface) {
public:
    explicit SCA_CTOR(Valve_iface) {}

    void processing() override;

    sca_tdf::sca_de::sca_in<sc_uint<32>> val0;
    sca_tdf::sca_de::sca_in<sc_uint<32>> val1;

    sca_tdf::sca_out<double> ams_aperture_threshold;
    sca_tdf::sca_out<int> ams_command;

private:

    /**
     * Simple uit (2 of 32 bit) to double (64 bit) conversion
     * @param u1 first uint of length 32 bit
     * @param u2 second uint of length 32 bit
     * @return a double, resulting the composition of the 2 uints
     */
    double uint_to_double(uint32_t u1, uint32_t u2);
};