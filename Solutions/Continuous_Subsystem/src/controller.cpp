//
// Created by vlad on 21/12/18.
//

#include "controller.h"

// controller::controller(sc_core::sc_module_name) : water_level("water_level"),
//                                                   command("command"),
//                                                   aperture_threshold("aperture_threshold")
// {
//     threshold = 0.7;
//     aperture_threshold.write(threshold);
// }

// controller::~controller() {}

void controller::set_attributes()
{
    set_timestep(5, SC_MS);
    water_level.set_delay(1);
    wait = 1000;
}

void controller::processing()
{
    double level = water_level.read();

    if (level >= 5 && level <= 8.8)
    {
        command.write(IDLE);
        samples = 0;
    }
    else if (level > 8.8 && samples == wait)
    {
        threshold *= 0.7;
        command.write(CLOSE);
        samples = 0;
    }
    else if (level < 5 && samples == wait)
    {
        threshold *= 1.1;
        command.write(OPEN);
        samples = 0;
    }

    aperture_threshold.write(threshold);
    samples++;
}