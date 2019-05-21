//
// Created by vlad on 07/01/19.
//

#include "Valve_iface.h"


void Valve_iface::processing() {
    // We force val1 to be 0 when sending a command. If val1 is not 0, it means that we are receiving the threshold
    if (val1.read() == 0) {
        ams_command.write(val0.read());
    } else {
        ams_aperture_threshold.write(
                uint_to_double(static_cast<uint32_t>(val0.read()), static_cast<uint32_t>(val1.read())));
    }
}

double Valve_iface::uint_to_double(uint32_t u1, uint32_t u2) {
    uint64_t tmp = static_cast<uint64_t>(u1) + (static_cast<uint64_t>(u2) << 32);
    uint64_t *ptr = &tmp;
    auto *ptr2 = (double *) ptr;
    return *ptr2;
}