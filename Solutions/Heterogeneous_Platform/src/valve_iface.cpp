//
// Created by vlad on 07/01/19.
//

#include "valve_iface.h"

// valve_iface::valve_iface(sc_module_name name) : aperture_threshold("aperture_threshold"),
//                                                 command("command"),
//                                                 ams_aperture_threshold("ams_aperture_threshold"),
//                                                 ams_command("ams_command") {}

void valve_iface::processing()
{
    ams_aperture_threshold.write(aperture_threshold.read());
    ams_command.write(command.read());
}