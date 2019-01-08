//
// Created by vlad on 4/01/19.
//

#pragma once

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include "iostruct.h"

class transactor_watertank : public sc_module,
                             public virtual tlm::tlm_fw_transport_if<>
{
  public:
    tank_data data;
    tlm::tlm_target_socket<> target_socket;
    tlm::tlm_generic_payload *pending_transaction;
    sc_time timing_annotation;

    virtual void b_transport(tlm::tlm_generic_payload &trans, sc_time &t);
    virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans,
                                    tlm::tlm_dmi &dmi_data);
    virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans,
                                               tlm::tlm_phase &phase,
                                               sc_time &t);
    virtual unsigned int transport_dbg(tlm::tlm_generic_payload &trans);

    void end_of_elaboration();

    SC_HAS_PROCESS(transactor_watertank);
    transactor_watertank(sc_module_name name);

    sc_in<double> water_level;
};