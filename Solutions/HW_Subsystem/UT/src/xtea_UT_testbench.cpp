//
// Created by vlad on 18/12/18.
//

#include "xtea_UT_testbench.h"

void xtea_UT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range) {
}

tlm::tlm_sync_enum xtea_UT_testbench::nb_transport_bw(
        tlm::tlm_generic_payload &trans,
        tlm::tlm_phase &phase,
        sc_time &t) {
    return tlm::TLM_COMPLETED;
}

void xtea_UT_testbench::run() {

    sc_time local_time;

    iostruct xtea_packet;
    tlm::tlm_generic_payload payload;

    xtea_packet.word0 = 0x12345678;
    xtea_packet.word1 = 0x9abcdeff;
    xtea_packet.key0 = 0x6a1d78c8;
    xtea_packet.key1 = 0x8c86d67f;
    xtea_packet.key2 = 0x2a65bfbe;
    xtea_packet.key3 = 0xb4bd6e46;
    xtea_packet.mode = false;

    payload.set_data_ptr((unsigned char *) &xtea_packet);
    payload.set_address(0);
    payload.set_write();

    initiator_socket->b_transport(payload, local_time);

    printf("First invocation:\n");
    cout << "\t- the encryption of " << hex << xtea_packet.word0 << " and "
         << hex << xtea_packet.word1 << endl;
    cout << "\t- with key\n"
         << hex << xtea_packet.key0
         << hex << xtea_packet.key1
         << hex << xtea_packet.key2
         << hex << xtea_packet.key3 << endl;

    if (payload.get_response_status() == tlm::TLM_OK_RESPONSE) {
        cout << "is: " << hex << xtea_packet.result0 << ", " << hex << xtea_packet.result1 << endl;
        if ((xtea_packet.result0 != 0x99bbb92b) || (xtea_packet.result1 != 0x3ebd1644)) {
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

    payload.set_data_ptr((unsigned char *) &xtea_packet);
    payload.set_address(0);
    payload.set_write();

    initiator_socket->b_transport(payload, local_time);

    printf("\nSecond invocation:\n");
    cout << "\t- the decryption of " << hex << xtea_packet.word0 << " and "
         << hex << xtea_packet.word1 << endl;
    cout << "\t- with key\n"
         << hex << xtea_packet.key0
         << hex << xtea_packet.key1
         << hex << xtea_packet.key2
         << hex << xtea_packet.key3 << endl;

    if (payload.get_response_status() == tlm::TLM_OK_RESPONSE) {
        cout << "is: " << hex << xtea_packet.result0 << ", " << hex << xtea_packet.result1 << endl;
        if ((xtea_packet.result0 != 0x12345678) || (xtea_packet.result1 != 0x9abcdeff)) {
            printf("Wrong result!\n");
        }
    }

    printf("\nDone!!\n");

    sc_stop();
}

xtea_UT_testbench::xtea_UT_testbench(sc_module_name name) : sc_module(name) {
    initiator_socket(*this);

    SC_THREAD(run);
}