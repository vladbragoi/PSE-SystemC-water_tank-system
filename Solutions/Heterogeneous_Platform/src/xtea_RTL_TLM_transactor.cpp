//
// Created by vlad on 4/01/19.
//

#include "xtea_RTL_TLM_transactor.h"

xtea_RTL_TLM_transactor::xtea_RTL_TLM_transactor(sc_module_name name) : sc_module(name),
                                                                        target_socket("target_socket")
{
    target_socket(*this);

    SC_THREAD(writeprocess);
    sensitive << clk.pos();

    SC_THREAD(readprocess);
    sensitive << clk.pos();
}

void xtea_RTL_TLM_transactor::b_transport(tlm::tlm_generic_payload &trans, sc_time &t)
{
    wait(0, SC_NS);
    tlm::tlm_command trans_command = trans.get_command();

    switch (trans_command)
    {
    case tlm::TLM_WRITE_COMMAND:
        data = *((iostruct *)trans.get_data_ptr());
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
        begin_write.notify();
        wait(end_write);
        break;

    case tlm::TLM_READ_COMMAND:
        data = *((iostruct *)trans.get_data_ptr());
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
        begin_read.notify();
        wait(end_read);
        *((iostruct *)trans.get_data_ptr()) = data;
        break;

    default:
        break;
    }
}

void xtea_RTL_TLM_transactor::writeprocess()
{
    while (true)
    {
        wait(begin_write);
        rst.write(false);
        word0.write(data.word0);
        word1.write(data.word1);
        key0.write(data.key0);
        key1.write(data.key1);
        key2.write(data.key2);
        key3.write(data.key3);
        mode.write(data.mode);

        din_rdy.write(true);
        end_write.notify();
        wait();
    }
}

void xtea_RTL_TLM_transactor::readprocess()
{
    while (true)
    {
        wait(begin_read);
        while (dout_rdy.read() != true)
        {
            wait();
        }

        data.result0 = result0;
        data.result1 = result1;

        end_read.notify();
    }
}

void xtea_RTL_TLM_transactor::end_of_elaboration()
{
    reset();
}

void xtea_RTL_TLM_transactor::reset()
{
    rst.write(true);
    din_rdy.write(0);
    word0.write(0);
    word1.write(0);
    key0.write(0);
    key1.write(0);
    key2.write(0);
    key3.write(0);
    // mode.write(0);
}

bool xtea_RTL_TLM_transactor::get_direct_mem_ptr(
    tlm::tlm_generic_payload &trans,
    tlm::tlm_dmi &dmi_data)
{
    return false;
}

tlm::tlm_sync_enum xtea_RTL_TLM_transactor::nb_transport_fw(
    tlm::tlm_generic_payload &trans,
    tlm::tlm_phase &phase,
    sc_time &t)
{
    return tlm::TLM_UPDATED;
}

unsigned int xtea_RTL_TLM_transactor::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}