//
// Created by vlad on 18/12/18.
//

#pragma once

#include <systemc.h>
#include <tlm.h>
#include "define_UT.h"

class xtea_UT : public sc_module,
<<<<<<< HEAD
                public virtual tlm::tlm_fw_transport_if<>
{

  public:
    tlm::tlm_target_socket<> target_socket;

    virtual void b_transport(tlm::tlm_generic_payload &trans, sc_time &t);
    virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data);
    virtual unsigned int transport_dbg(tlm::tlm_generic_payload &trans);
    virtual tlm::tlm_sync_enum nb_transport_fw(
        tlm::tlm_generic_payload &trans,
        tlm::tlm_phase &phase,
        sc_time &t);
=======
                public virtual tlm::tlm_fw_transport_if<> {

public:
    SC_HAS_PROCESS(xtea_UT);

    explicit xtea_UT(sc_module_name name);

    void b_transport(tlm::tlm_generic_payload &trans, sc_time &t) override;

    bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data) override;

    unsigned int transport_dbg(tlm::tlm_generic_payload &trans) override;

    tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t) override;

    void xtea(uint32_t word0, uint32_t word1, bool mode, uint32_t key0, uint32_t key1, uint32_t key2, uint32_t key3);

    void end_of_elaboration() override;

    void reset();
>>>>>>> PSE-univr-project/master

    iostruct data;
    sc_uint<32> res0;
    sc_uint<32> res1;
    tlm::tlm_generic_payload *pending_transaction;
<<<<<<< HEAD

    void xtea(uint32_t word0, uint32_t word1, bool mode,
              uint32_t key0, uint32_t key1, uint32_t key2, uint32_t key3);
    void end_of_elaboration();
    void reset();

    SC_HAS_PROCESS(xtea_UT);
    xtea_UT(sc_module_name name);
=======
    tlm::tlm_target_socket<> target_socket;

>>>>>>> PSE-univr-project/master
};