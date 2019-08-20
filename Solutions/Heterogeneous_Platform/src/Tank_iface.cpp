//
// Created by vlad on 05/01/19.
//

#include "Tank_iface.h"


void Tank_iface::processing() {
    rtl_water_level.write(ams_water_level.read());
}
