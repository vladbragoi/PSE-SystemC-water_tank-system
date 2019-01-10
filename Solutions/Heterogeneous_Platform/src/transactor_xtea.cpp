//
// Created by vlad on 4/01/19.
//

#include "transactor_xtea.h"

transactor_xtea::transactor_xtea(sc_module_name name) : sc_module(name),
                                                        target_socket("target_socket")
{
    target_socket(*this);

    SC_THREAD(writeprocess);
    sensitive << clk.pos();
}

void transactor_xtea::b_transport(tlm::tlm_generic_payload &trans, sc_time &t)
{
    wait(0, SC_NS);

    data = *((xtea_data *)trans.get_data_ptr());
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    begin_write.notify();
    wait(end_write);
}

void transactor_xtea::writeprocess()
{
    while (true)
    {
        wait(begin_write);
        rst.write(false);
        word[0].write(data.word[0]);
        word[1].write(data.word[1]);
        key[0].write(data.key[0]);
        key[1].write(data.key[1]);
        key[2].write(data.key[2]);
        key[3].write(data.key[3]);
        mode.write(true);
        din_rdy.write(true);
        end_write.notify();
        wait();
    }
}

void transactor_xtea::end_of_elaboration()
{
    reset();
}

void transactor_xtea::reset()
{
    rst.write(true);
    din_rdy.write(0);
    word[0].write(0);
    word[1].write(0);
    key[0].write(0);
    key[1].write(0);
    key[2].write(0);
    key[3].write(0);
}

bool transactor_xtea::get_direct_mem_ptr(
    tlm::tlm_generic_payload &trans,
    tlm::tlm_dmi &dmi_data)
{
    return false;
}

tlm::tlm_sync_enum transactor_xtea::nb_transport_fw(
    tlm::tlm_generic_payload &trans,
    tlm::tlm_phase &phase,
    sc_time &t)
{
    return tlm::TLM_UPDATED;
}

unsigned int transactor_xtea::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}