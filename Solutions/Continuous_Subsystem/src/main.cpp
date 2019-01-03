//
// Created by vlad on 28/12/18.
//

#include "valve.h"
#include "tank.h"
#include "controller.h"

int sc_main(int argc, char **argv)
{
    sca_tdf::sca_signal<double> water_level;
    sca_tdf::sca_signal<int> command;
    sca_tdf::sca_signal<double> threshold;
    sca_tdf::sca_signal<double> valve_aperture;

    valve valve("valve");
    tank tank("tank");
    controller controller("controller");

    valve.command(command);
    valve.aperture_threshold(threshold);
    valve.aperture(valve_aperture);

    tank.valve_aperture(valve_aperture);
    tank.water_level(water_level);

    controller.water_level(water_level);
    controller.command(command);
    controller.aperture_threshold(threshold);

    sca_trace_file *file = sca_create_vcd_trace_file("water");
    sca_trace(file, water_level, "water_level");
    sca_trace(file, threshold, "aperture_threshold");
    sca_trace(file, valve_aperture, "valve_aperture");
    sca_trace(file, command, "command");

    sc_start(3000, SC_SEC);
    sca_close_vcd_trace_file(file);
}