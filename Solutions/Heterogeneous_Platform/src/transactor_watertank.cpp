//
// Created by vlad on 4/01/19.
//

#include "transactor_watertank.h"

transactor_watertank::transactor_watertank(sc_module_name name) : sc_module(name),
                                                                  target_socket("target_socket"),
                                                                  pending_transaction(NULL)
{
    target_socket(*this);
}

void transactor_watertank::b_transport(tlm::tlm_generic_payload &trans, sc_time &t)
{
    data = *((tank_data *)trans.get_data_ptr());
    data.water_level = water_level.read();
    trans.set_data_ptr((unsigned char *)&data);
}

tlm::tlm_sync_enum transactor_watertank::nb_transport_fw(
    tlm::tlm_generic_payload &trans,
    tlm::tlm_phase &phase,
    sc_time &t)
{
    return tlm::TLM_UPDATED;
}

void transactor_watertank::end_of_elaboration() {}

bool transactor_watertank::get_direct_mem_ptr(tlm::tlm_generic_payload &trans,
                                              tlm::tlm_dmi &dmi_data)
{
    return false;
}

unsigned int transactor_watertank::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}