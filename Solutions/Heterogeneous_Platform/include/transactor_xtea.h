//
// Created by vlad on 4/01/19.
//

#pragma once

#include <systemc.h>
#include <tlm.h>
#include "iostruct.h"

class transactor_xtea : public sc_module,
                        public virtual tlm::tlm_fw_transport_if<>
{
  public:
    //TLM
    xtea_data data;
    tlm::tlm_target_socket<> target_socket;
    tlm::tlm_generic_payload *pending_transaction;
    sc_time timing_annotation;
    sc_event begin_write, end_write, begin_read, end_read;

    //TLM interfaces
    virtual void b_transport(tlm::tlm_generic_payload &trans, sc_time &t);
    virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans,
                                    tlm::tlm_dmi &dmi_data) override;
    virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans,
                                               tlm::tlm_phase &phase,
                                               sc_time &t) override;
    virtual unsigned int transport_dbg(tlm::tlm_generic_payload &trans) override;

    //RTL ports
    // sc_in<sc_uint<32>> result[2];
    // sc_in<bool> dout_rdy;

    sc_in<sc_logic> clk;
    sc_out<sc_uint<32>> word[2];
    sc_out<sc_uint<32>> key[4];
    sc_out<bool> din_rdy;
    sc_out<bool> mode;
    sc_out<bool> rst;

    void writeprocess();
    void readprocess();

    void end_of_elaboration();
    void reset();

    SC_HAS_PROCESS(transactor_xtea);
    transactor_xtea(sc_module_name name);
};