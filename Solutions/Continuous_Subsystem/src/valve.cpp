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

void valve::set_attributes()
{
    set_timestep(5, SC_MS);
}

void valve::processing()
{
    double delta = 0.25 * get_timestep().to_seconds();
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
            valve_aperture += delta;
        }
        break;
    case CLOSE:
        if (valve_aperture > 0)
        {
            valve_aperture -= delta;
        }
        else
        {
            valve_aperture = 0;
        }
        break;
    }

    aperture.write(valve_aperture);
}