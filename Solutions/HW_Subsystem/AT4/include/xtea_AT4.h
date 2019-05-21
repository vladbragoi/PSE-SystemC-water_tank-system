//
// Created by vlad on 19/12/18.
//

#pragma once

#include <systemc.h>
#include <tlm.h>
#include "define_AT4.h"

class xtea_AT4 : public sc_module,
                 public virtual tlm::tlm_fw_transport_if<> {

public:
    tlm::tlm_target_socket<> target_socket;

    void b_transport(tlm::tlm_generic_payload &trans, sc_time &t) override;

    bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data) override;

    unsigned int transport_dbg(tlm::tlm_generic_payload &trans) override;

    tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t) override;

    iostruct data;
    sc_event io_event;
    tlm::tlm_generic_payload *pending_transaction;

    void ioprocess();

    void xtea();

    void end_of_elaboration() override;

    void reset();

    SC_HAS_PROCESS(xtea_AT4);

    explicit xtea_AT4(sc_module_name name);
};