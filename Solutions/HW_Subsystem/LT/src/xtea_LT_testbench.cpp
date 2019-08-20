//
// Created by vlad on 19/12/18.
//

#include "xtea_LT_testbench.h"

<<<<<<< HEAD
void xtea_LT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{
}

tlm::tlm_sync_enum xtea_LT_testbench::nb_transport_bw(
    tlm::tlm_generic_payload &trans,
    tlm::tlm_phase &phase,
    sc_time &t)
{
    return tlm::TLM_COMPLETED;
}

void xtea_LT_testbench::run()
{
=======
void xtea_LT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range) {
}

tlm::tlm_sync_enum xtea_LT_testbench::nb_transport_bw(
        tlm::tlm_generic_payload &trans,
        tlm::tlm_phase &phase,
        sc_time &t) {
    return tlm::TLM_COMPLETED;
}

void xtea_LT_testbench::run() {
>>>>>>> PSE-univr-project/master

    sc_time local_time = q_keeper.get_local_time();

    iostruct xtea_packet;
    tlm::tlm_generic_payload payload;

    xtea_packet.word0 = 0x12345678;
    xtea_packet.word1 = 0x9abcdeff;
    xtea_packet.key0 = 0x6a1d78c8;
    xtea_packet.key1 = 0x8c86d67f;
    xtea_packet.key2 = 0x2a65bfbe;
    xtea_packet.key3 = 0xb4bd6e46;
    xtea_packet.mode = false;

<<<<<<< HEAD
    payload.set_data_ptr((unsigned char *)&xtea_packet);
=======
    payload.set_data_ptr((unsigned char *) &xtea_packet);
>>>>>>> PSE-univr-project/master
    payload.set_address(0);
    payload.set_write();

    local_time = q_keeper.get_local_time();

    initiator_socket->b_transport(payload, local_time);

    printf("First invocation:\n");
    cout << "\t- the encryption of " << hex << xtea_packet.word0 << " and "
         << hex << xtea_packet.word1 << endl;
    cout << "\t- with key\n"
         << hex << xtea_packet.key0
         << hex << xtea_packet.key1
         << hex << xtea_packet.key2
         << hex << xtea_packet.key3 << endl;

<<<<<<< HEAD
    if (payload.get_response_status() == tlm::TLM_OK_RESPONSE)
    {
        cout << "is: " << hex << xtea_packet.result0 << ", " << hex << xtea_packet.result1 << endl;
        if ((xtea_packet.result0 != 0x99bbb92b) || (xtea_packet.result1 != 0x3ebd1644))
        {
=======
    if (payload.get_response_status() == tlm::TLM_OK_RESPONSE) {
        cout << "is: " << hex << xtea_packet.result0 << ", " << hex << xtea_packet.result1 << endl;
        if ((xtea_packet.result0 != 0x99bbb92b) || (xtea_packet.result1 != 0x3ebd1644)) {
>>>>>>> PSE-univr-project/master
            printf("Wrong result!\n");
        }
    }

    // cout << "Time: " << sc_time_stamp() << " + " << local_time << endl;
    q_keeper.set(local_time);
<<<<<<< HEAD
    if (q_keeper.need_sync())
    {
=======
    if (q_keeper.need_sync()) {
>>>>>>> PSE-univr-project/master
        // cout << "SYNCHRONIZING" << endl;
        q_keeper.sync();
    }

    xtea_packet.word0 = xtea_packet.result0;
    xtea_packet.word1 = xtea_packet.result1;
    xtea_packet.key0 = 0x6a1d78c8;
    xtea_packet.key1 = 0x8c86d67f;
    xtea_packet.key2 = 0x2a65bfbe;
    xtea_packet.key3 = 0xb4bd6e46;
    xtea_packet.mode = true;

<<<<<<< HEAD
    payload.set_data_ptr((unsigned char *)&xtea_packet);
=======
    payload.set_data_ptr((unsigned char *) &xtea_packet);
>>>>>>> PSE-univr-project/master
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

<<<<<<< HEAD
    if (payload.get_response_status() == tlm::TLM_OK_RESPONSE)
    {
        cout << "is: " << hex << xtea_packet.result0 << ", " << hex << xtea_packet.result1 << endl;
        if ((xtea_packet.result0 != 0x12345678) || (xtea_packet.result1 != 0x9abcdeff))
        {
=======
    if (payload.get_response_status() == tlm::TLM_OK_RESPONSE) {
        cout << "is: " << hex << xtea_packet.result0 << ", " << hex << xtea_packet.result1 << endl;
        if ((xtea_packet.result0 != 0x12345678) || (xtea_packet.result1 != 0x9abcdeff)) {
>>>>>>> PSE-univr-project/master
            printf("Wrong result!\n");
        }
    }

    // cout << "Time: " << sc_time_stamp() << " + " << local_time << endl;
    q_keeper.set(local_time);
<<<<<<< HEAD
    if (q_keeper.need_sync())
    {
=======
    if (q_keeper.need_sync()) {
>>>>>>> PSE-univr-project/master
        // cout << "SYNCHRONIZING" << endl;
        q_keeper.sync();
    }

    printf("\nDone!!\n");

    sc_stop();
}

<<<<<<< HEAD
xtea_LT_testbench::xtea_LT_testbench(sc_module_name name) : sc_module(name)
{
=======
xtea_LT_testbench::xtea_LT_testbench(sc_module_name name) : sc_module(name) {
>>>>>>> PSE-univr-project/master
    initiator_socket(*this);

    SC_THREAD(run);

<<<<<<< HEAD
    q_keeper.set_global_quantum(sc_time(500, SC_NS));
=======
    tlm_utils::tlm_quantumkeeper::set_global_quantum(sc_time(500, SC_NS));
>>>>>>> PSE-univr-project/master
    q_keeper.reset();
}