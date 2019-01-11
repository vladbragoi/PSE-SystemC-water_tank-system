//
// Created by vlad on 05/01/19.
//

#include "tank_iface.h"

// tank_iface::tank_iface(sc_module_name name) : ams_water_level("ams_water_level"),
//                                               rtl_water_level("rtl_water_level") {}

void tank_iface::processing()
{
    rtl_water_level.write(ams_water_level.read());
}