#include "valve_iface.h"

void valve_iface::processing()
{
    ams_aperture_threshold.write(aperture_threshold.read());
    ams_command.write(command.read());
}