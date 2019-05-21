//
// Created by vlad on 4/01/19.
//

#include "Transactor_tank.h"

Transactor_tank::Transactor_tank(sc_module_name name) : sc_module(name),
                                                        target_socket("target_socket") {
    target_socket(*this);
}

void Transactor_tank::b_transport(tlm::tlm_generic_payload &trans, sc_time &t) {
    data = *((tank_data *) trans.get_data_ptr());
    data.water_level = water_level.read();
    *((tank_data *) trans.get_data_ptr()) = data;
}