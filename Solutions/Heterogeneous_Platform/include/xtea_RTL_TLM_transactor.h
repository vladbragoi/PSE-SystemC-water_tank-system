//
// Created by vlad on 4/01/19.
//

#pragma once

#include <systemc.h>
#include <tlm.h>
#include "define_LT.h"

class xtea_RTL_TLM_transactor : public sc_module,
                                public virtual tlm::tlm_fw_transport_if<>
{

  public:
    //TLM
    iostruct data;
    tlm::tlm_target_socket<> target_socket;
    tlm::tlm_generic_payload *pending_transaction;
    sc_time timing_annotation;
    sc_event begin_write, end_write, begin_read, end_read;

    //TLM interfaces
    virtual void b_transport(tlm::tlm_generic_payload &trans, sc_time &t);
    virtual bool get_direct_mem_ptr(
        tlm::tlm_generic_payload &trans,
        tlm::tlm_dmi &dmi_data);
    virtual tlm::tlm_sync_enum nb_transport_fw(
        tlm::tlm_generic_payload &trans,
        tlm::tlm_phase &phase,
        sc_time &t);
    virtual unsigned int transport_dbg(tlm::tlm_generic_payload &trans);

    //RTL ports
    sc_in<sc_uint<32>> result0;
    sc_in<sc_uint<32>> result1;
    sc_in<bool> dout_rdy;

    sc_in<sc_logic> clk;
    sc_out<sc_uint<32>> word0;
    sc_out<sc_uint<32>> word1;
    sc_out<sc_uint<32>> key0;
    sc_out<sc_uint<32>> key1;
    sc_out<sc_uint<32>> key2;
    sc_out<sc_uint<32>> key3;
    sc_out<bool> din_rdy;
    sc_out<bool> mode;
    sc_out<bool> rst;

    void writeprocess();
    void readprocess();

    //mandatory for TLM
    void sync();
    void end_of_elaboration();
    void reset();

    SC_HAS_PROCESS(xtea_RTL_TLM_transactor);
    xtea_RTL_TLM_transactor(sc_module_name name_);
};