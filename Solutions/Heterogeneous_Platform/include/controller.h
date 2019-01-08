//
// Created by vlad on 05/01/19.
//

#pragma once

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include "iostruct.h"
#include "command.h"

class controller : public sc_module,
                   public virtual tlm::tlm_bw_transport_if<>
{
  public:
    SC_HAS_PROCESS(controller);
    controller(sc_module_name name);

    virtual void invalidate_direct_mem_ptr(uint64 start_range,
                                           uint64 end_range) override;
    virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &trans,
                                               tlm::tlm_phase &phase,
                                               sc_time &t) override;

    tlm::tlm_initiator_socket<> watertank_socket;
    tlm::tlm_initiator_socket<> xtea_socket;

    sc_out<double> aperture_threshold;
    sc_out<int> command;

  private:
    void run();
    void xtea(uint32_t v0, /*uint32_t v1,*/ sc_uint<32> &result0, sc_uint<32> &result1); // encryption only

    const sc_uint<32> key[4] = {0x6a1d78c8, 0x8c86d67f, 0x2a65bfbe, 0xb4bd6e46};
    double water_level;
    double threshold;
    tlm_utils::tlm_quantumkeeper q_keeper;
};
