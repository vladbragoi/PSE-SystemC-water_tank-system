//
// Created by vlad on 19/12/18.
//

#include "xtea_AT4.h"

xtea_AT4::xtea_AT4(sc_module_name name) : sc_module(name),
                                          target_socket("target_socket"),
                                          pending_transaction(NULL)
{
    target_socket(*this);
    SC_THREAD(ioprocess);
}

void xtea_AT4::b_transport(tlm::tlm_generic_payload &trans, sc_time &t) {}

void xtea_AT4::xtea()
{
    uint32_t i, delta, v0, v1, temp;
    uint64_t sum;
    v0 = data.word0;
    v1 = data.word1;
    data.result0 = 0;
    data.result1 = 0;
    sum = 0;

    if (data.mode == 0)
    {
        // encipher
        delta = 0x9e3779b9;
        for (i = 0; i < 32; i++)
        {
            switch (sum & 3)
            {
            case 0:
                temp = data.key0;
                break;
            case 1:
                temp = data.key1;
                break;
            case 2:
                temp = data.key2;
                break;
            case 3:
                temp = data.key3;
                break;
            default:
                printf("Something wrong!\n");
                temp = 0;
                break;
            }

            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);

            sum += delta;

            switch ((sum >> 11) & 3)
            {
            case 0:
                temp = data.key0;
                break;
            case 1:
                temp = data.key1;
                break;
            case 2:
                temp = data.key2;
                break;
            case 3:
                temp = data.key3;
                break;
            default:
                printf("Something wrong!\n");
                temp = 0;
                break;
            }

            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
        }
    }

    else if (data.mode == 1)
    {
        // decipher
        delta = 0x9e3779b9;
        sum = delta * 32;
        for (i = 0; i < 32; i++)
        {
            switch ((sum >> 11) & 3)
            {
            case 0:
                temp = data.key0;
                break;
            case 1:
                temp = data.key1;
                break;
            case 2:
                temp = data.key2;
                break;
            case 3:
                temp = data.key3;
                break;
            default:
                printf("Something wrong!\n");
                temp = 0;
                break;
            }

            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);

            sum -= delta;

            switch (sum & 3)
            {
            case 0:
                temp = data.key0;
                break;
            case 1:
                temp = data.key1;
                break;
            case 2:
                temp = data.key2;
                break;
            case 3:
                temp = data.key3;
                break;
            default:
                printf("Something wrong!\n");
                temp = 0;
                break;
            }

            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);
        }
    }

    data.result0 = v0;
    data.result1 = v1;
}

bool xtea_AT4::get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data)
{
    return false;
}

tlm::tlm_sync_enum xtea_AT4::nb_transport_fw(
    tlm::tlm_generic_payload &trans,
    tlm::tlm_phase &phase,
    sc_time &t)
{

    if (pending_transaction != NULL)
    { // Another transaction is pending
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    if (phase != tlm::BEGIN_REQ)
    { // Phase must be BEGIN_REQ
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    pending_transaction = &trans;
    data = *((iostruct *)trans.get_data_ptr());

    phase = tlm::END_REQ;
    io_event.notify();

    return tlm::TLM_UPDATED;
}

unsigned int xtea_AT4::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}

void xtea_AT4::ioprocess()
{
    sc_time timing_annotation;

    while (true)
    {
        wait(io_event);

        wait(100, SC_NS);

        if (pending_transaction->is_write())
        {
            xtea();
        }

        pending_transaction->set_response_status(tlm::TLM_OK_RESPONSE);
        *((iostruct *)pending_transaction->get_data_ptr()) = data;
        tlm::tlm_phase phase = tlm::BEGIN_RESP;

        target_socket->nb_transport_bw(*pending_transaction, phase, timing_annotation);

        pending_transaction = NULL;
    }
}

void xtea_AT4::end_of_elaboration() {}

void xtea_AT4::reset() {}