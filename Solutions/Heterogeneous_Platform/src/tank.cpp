//
// Created by vlad on 21/12/18.
//

#include "tank.h"

tank::tank(sc_core::sc_module_name name) : sc_module(name),
                                           valve_aperture("valve_aperture"),
                                           water_level("water_level"),
                                           input_converter("input"),
                                           output_converter("output"),
                                           sub("sub"),
                                           water_integrator("water_integrator"),
                                           valve_gain("valve_gain", 0.6),
                                           water_gain("water_gain", 0.003),
                                           x_derivative("x_derivative"),
                                           a("a"),
                                           sig1("sig1"),
                                           sig2("sig2")
{
    input_converter.inp(valve_aperture);
    input_converter.y(a);

    // 0.6 * a
    valve_gain.x(a);
    valve_gain.y(sig1);

    // x' = (0.6 * a) - (0.003 * x)
    sub.x1(sig1);
    sub.x2(sig2);
    sub.y(x_derivative);

    // x = integral(x')
    water_integrator.x(x_derivative);
    water_integrator.y(x);

    // 0.003 * x
    water_gain.x(x);
    water_gain.y(sig2);

    output_converter.x(x);
    output_converter.outp(water_level);
}