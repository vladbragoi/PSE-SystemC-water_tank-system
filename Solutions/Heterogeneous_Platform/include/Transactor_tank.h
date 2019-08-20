//
// Created by vlad on 4/01/19.
//

#pragma once

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include "iostruct.h"

class Transactor_tank : public sc_module,
                        public virtual tlm::tlm_fw_transport_if<> {
public:
    SC_HAS_PROCESS(Transactor_tank);

    explicit Transactor_tank(sc_module_name name);

    void end_of_elaboration() override {};

    void b_transport(tlm::tlm_generic_payload &trans, sc_time &t) override;

    unsigned int transport_dbg(tlm::tlm_generic_payload &trans) override { return 0; };

    bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data) override { return false; };

    tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t) override {
        return tlm::TLM_UPDATED;
    };

    sc_in<double> water_level;
    tank_data data;
    tlm::tlm_target_socket<> target_socket;
};