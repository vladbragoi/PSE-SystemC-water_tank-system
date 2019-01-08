#include "tank_iface.h"

void tank_iface::processing()
{
    rtl_water_level.write(ams_water_level.read());
}