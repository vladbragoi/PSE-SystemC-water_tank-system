//
// Created by vlad on 21/12/18.
//

#include "valve.h"

// valve::valve(sc_core::sc_module_name) : aperture_threshold("aperture_threshold"),
//                                         command("command"),
//                                         aperture("valve_aperture")
// {
//     aperture.write(0.7);
//     valve_aperture = 0;
// }

// valve::~valve() {}

void valve::processing()
{
    switch (command.read())
    {
    case IDLE:
        break;
    case OPEN:
        if (valve_aperture > aperture_threshold.read())
        {
            valve_aperture = aperture_threshold.read();
        }
        else
        {
            valve_aperture = 0.25;
        }
        break;
    case CLOSE:
        valve_aperture = -0.25;
        break;
    }

    aperture.write(valve_aperture);
}