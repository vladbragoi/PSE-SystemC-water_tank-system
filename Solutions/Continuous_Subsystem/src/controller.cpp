//
// Created by vlad on 21/12/18.
//

#include "controller.h"

void controller::set_attributes()
{
    water_level.set_timestep(5, SC_MS);
    water_level.set_delay(1);
    samples_to_wait = 1000;
}

void controller::processing()
{
    double level = water_level.read();

    if (level >= 5 && level <= 8.8)
    {
        command.write(IDLE);
        samples = 0;
    }
    else if (level > 8.8 && samples == samples_to_wait)
    {
        threshold *= 0.7;
        command.write(CLOSE);
        samples = 0;
    }
    else if (level < 5 && samples == samples_to_wait)
    {
        threshold *= 1.1;
        command.write(OPEN);
        samples = 0;
    }

    aperture_threshold.write(threshold);
    samples++;
}