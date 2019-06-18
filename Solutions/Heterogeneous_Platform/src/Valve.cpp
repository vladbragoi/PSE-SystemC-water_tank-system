//
// Created by vlad on 21/12/18.
//

#include "Valve.h"

void Valve::set_attributes() {
    set_timestep(5, SC_MS); // 4 MS
}

void Valve::processing() {
    bool skip = false;
    double delta = 0.25 * get_timestep().to_seconds();
    switch (command.read()) {
        case IDLE:
            break;
        case OPEN:
            if (valve_aperture >= aperture_threshold.read()) {
                valve_aperture = aperture_threshold.read();
            } else {
                valve_aperture += delta;
            }
            break;
        case CLOSE:
            if (valve_aperture < 0) {
                valve_aperture = aperture_threshold.read();
                aperture.write(0);
                skip = true;
            } else {
                valve_aperture -= delta;
            }
            break;
        default:
            break;
    }

    if (!skip) {
        aperture.write(valve_aperture);
    }
}