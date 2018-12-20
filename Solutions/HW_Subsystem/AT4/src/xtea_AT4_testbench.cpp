//
// Created by vlad on 19/12/18.
//

#include "xtea_AT4_testbench.h"

void xtea_AT4_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
}

tlm::tlm_sync_enum xtea_AT4_testbench::nb_transport_bw(
    tlm::tlm_generic_payload &trans,
    tlm::tlm_phase &phase,
    sc_time &t)
{

    if (!response_pending)
    {
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    if (phase != tlm::BEGIN_RESP)
    { // phase should be BEGIN_RESP
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    available_response.notify();
    phase = tlm::END_RESP;

    return tlm::TLM_COMPLETED;
}

void xtea_AT4_testbench::run()
{

    tlm::tlm_generic_payload payload;
    tlm::tlm_sync_enum result;
    tlm::tlm_phase phase;
    iostruct xtea_packet;
    sc_time local_time = SC_ZERO_TIME;

    xtea_packet.word0 = 0x12345678;
    xtea_packet.word1 = 0x9abcdeff;
    xtea_packet.key0 = 0x6a1d78c8;
    xtea_packet.key1 = 0x8c86d67f;
    xtea_packet.key2 = 0x2a65bfbe;
    xtea_packet.key3 = 0xb4bd6e46;
    xtea_packet.mode = false;

    // Sending data to target
    phase = tlm::BEGIN_REQ;
    payload.set_address(0);
    payload.set_data_ptr((unsigned char *)&xtea_packet);
    payload.set_write();

    result = initiator_socket->nb_transport_fw(payload, phase, local_time);

    if (result == tlm::TLM_COMPLETED)
    {
        // Something gone wrong!
        printf("Transaction error: forcing simulation stop.\n");
        sc_stop();
    }

    if (phase != tlm::END_REQ)
    {
        printf("Unexcepted protocop phase: forcing simulation stop.\n");
        sc_stop();
    }

    // Waiting for acknowledge
    response_pending = true;
    wait(available_response);
    response_pending = false;

    if (payload.get_response_status() == tlm::TLM_OK_RESPONSE)
    {
        printf("First invocation:\n");
        cout << "\t- the encryption of " << hex << xtea_packet.word0 << " and "
             << hex << xtea_packet.word1 << endl;
        cout << "\t- with key\n"
             << hex << xtea_packet.key0
             << hex << xtea_packet.key1
             << hex << xtea_packet.key2
             << hex << xtea_packet.key3 << endl;
        cout << "is: " << hex << xtea_packet.result0 << ", " << hex << xtea_packet.result1 << endl;
        if ((xtea_packet.result0 != 0x99bbb92b) || (xtea_packet.result1 != 0x3ebd1644))
        {
            printf("Wrong result!\n");
        }
    }

    xtea_packet.word0 = xtea_packet.result0;
    xtea_packet.word1 = xtea_packet.result1;
    xtea_packet.key0 = 0x6a1d78c8;
    xtea_packet.key1 = 0x8c86d67f;
    xtea_packet.key2 = 0x2a65bfbe;
    xtea_packet.key3 = 0xb4bd6e46;
    xtea_packet.mode = true;

    phase = tlm::BEGIN_REQ;
    payload.set_write();

    result = initiator_socket->nb_transport_fw(payload, phase, local_time);

    if (result == tlm::TLM_COMPLETED)
    {
        // Something gone wrong!
        printf("Transaction error: forcing simulation stop.\n");
        sc_stop();
    }

    if (phase != tlm::END_REQ)
    {
        printf("Unexcepted protocop phase: forcing simulation stop.\n");
        sc_stop();
    }

    response_pending = true;
    wait(available_response);
    response_pending = false;

    if (payload.get_response_status() == tlm::TLM_OK_RESPONSE)
    {
        printf("\nSecond invocation:\n");
        cout << "\t- the decryption of " << hex << xtea_packet.word0 << " and "
             << hex << xtea_packet.word1 << endl;
        cout << "\t- with key\n"
             << hex << xtea_packet.key0
             << hex << xtea_packet.key1
             << hex << xtea_packet.key2
             << hex << xtea_packet.key3 << endl;
        cout << "is: " << hex << xtea_packet.result0 << ", " << hex << xtea_packet.result1 << endl;
        if ((xtea_packet.result0 != 0x12345678) || (xtea_packet.result1 != 0x9abcdeff))
        {
            printf("Wrong result!\n");
        }
    }

    printf("\nDone!!\n");

    sc_stop();
}

xtea_AT4_testbench::xtea_AT4_testbench(sc_module_name name) : sc_module(name),
                                                              response_pending(false)
{
    initiator_socket(*this);

    SC_THREAD(run);
}