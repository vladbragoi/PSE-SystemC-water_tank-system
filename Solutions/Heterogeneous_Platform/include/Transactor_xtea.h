//
// Created by vlad on 4/01/19.
//

#pragma once

#include <systemc.h>
#include <tlm.h>
#include "iostruct.h"
#include "params.h"

class Transactor_xtea :
        public sc_module,
        public virtual tlm::tlm_fw_transport_if<> {
public:
    SC_HAS_PROCESS(Transactor_xtea);

    explicit Transactor_xtea(sc_module_name name);

    void b_transport(tlm::tlm_generic_payload &trans, sc_time &t) override;

    void writeprocess();

    void end_of_elaboration() override;

    void reset();

    tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_base_protocol_types::tlm_payload_type &trans,
                                       tlm::tlm_base_protocol_types::tlm_phase_type &phase,
                                       sc_core::sc_time &t) override {
        return tlm::TLM_COMPLETED;
    }

    bool get_direct_mem_ptr(tlm::tlm_base_protocol_types::tlm_payload_type &trans, tlm::tlm_dmi &dmi_data) override {
        return false;
    }

    unsigned int transport_dbg(tlm::tlm_base_protocol_types::tlm_payload_type &trans) override {
        return 0;
    }

    // EXTERNAL PORTS
    sc_in<sc_logic> clk;
    sc_in<bool> dout_rdy;
    sc_out<sc_uint<32>> word[2];
    sc_out<sc_uint<32>> key[4];
    sc_out<bool> din_rdy;
    sc_out<bool> rst;
    sc_out<bool> mode;

    // INTERNAL VARIABLES
    xtea_data data;
    tlm::tlm_target_socket<> target_socket;
    sc_event begin_write,
            end_write;
};