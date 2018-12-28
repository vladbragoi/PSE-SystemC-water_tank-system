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

void controller::processing()
{
    float level = water_level.read();

    if (level >= 5 && level <= 8.8)
    {
        aperture_threshold.set_timestep(0, SC_SEC);
        command.write(IDLE);
    }
    else if (level > 8.8)
    {
        aperture_threshold.set_timestep(5, SC_SEC);
        threshold *= 0.7;
        command.write(CLOSE);
    }
    else if (level < 5)
    {
        aperture_threshold.set_timestep(5, SC_SEC);
        threshold *= 1.1;
        command.write(OPEN);
    }

    aperture_threshold.write(threshold);
}