//
// Created by vlad on 19/12/18.
//

#include "xtea_AT4.h"

xtea_AT4::xtea_AT4(sc_module_name name) : sc_module(name),
                                          target_socket("target_socket"),
<<<<<<< HEAD
                                          pending_transaction(NULL)
{
=======
                                          pending_transaction(nullptr) {
>>>>>>> PSE-univr-project/master
    target_socket(*this);
    SC_THREAD(ioprocess);
}

void xtea_AT4::b_transport(tlm::tlm_generic_payload &trans, sc_time &t) {}

<<<<<<< HEAD
void xtea_AT4::xtea()
{
    uint32_t i, delta, v0, v1, temp;
    uint64_t sum;
    v0 = data.word0;
    v1 = data.word1;
=======
void xtea_AT4::xtea() {
    uint32_t i, delta, v0, v1, temp;
    uint64_t sum;
    v0 = data.word0.to_uint();
    v1 = data.word1.to_uint();
>>>>>>> PSE-univr-project/master
    data.result0 = 0;
    data.result1 = 0;
    sum = 0;

<<<<<<< HEAD
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
=======
    if (data.mode == 0) {
        // encipher
        delta = 0x9e3779b9;
        for (i = 0; i < 32; i++) {
            switch (sum & 3) {
                case 0:
                    temp = data.key0.to_uint();
                    break;
                case 1:
                    temp = data.key1.to_uint();
                    break;
                case 2:
                    temp = data.key2.to_uint();
                    break;
                case 3:
                    temp = data.key3.to_uint();
                    break;
                default:
                    printf("Something wrong!\n");
                    temp = 0;
                    break;
>>>>>>> PSE-univr-project/master
            }

            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);

            sum += delta;

<<<<<<< HEAD
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
=======
            switch ((sum >> 11) & 3) {
                case 0:
                    temp = data.key0.to_uint();
                    break;
                case 1:
                    temp = data.key1.to_uint();
                    break;
                case 2:
                    temp = data.key2.to_uint();
                    break;
                case 3:
                    temp = data.key3.to_uint();
                    break;
                default:
                    printf("Something wrong!\n");
                    temp = 0;
                    break;
>>>>>>> PSE-univr-project/master
            }

            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
        }
<<<<<<< HEAD
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
=======
    } else if (data.mode == 1) {
        // decipher
        delta = 0x9e3779b9;
        sum = delta * 32;
        for (i = 0; i < 32; i++) {
            switch ((sum >> 11) & 3) {
                case 0:
                    temp = data.key0.to_uint();
                    break;
                case 1:
                    temp = data.key1.to_uint();
                    break;
                case 2:
                    temp = data.key2.to_uint();
                    break;
                case 3:
                    temp = data.key3.to_uint();
                    break;
                default:
                    printf("Something wrong!\n");
                    temp = 0;
                    break;
>>>>>>> PSE-univr-project/master
            }

            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);

            sum -= delta;

<<<<<<< HEAD
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
=======
            switch (sum & 3) {
                case 0:
                    temp = data.key0.to_uint();
                    break;
                case 1:
                    temp = data.key1.to_uint();
                    break;
                case 2:
                    temp = data.key2.to_uint();
                    break;
                case 3:
                    temp = data.key3.to_uint();
                    break;
                default:
                    printf("Something wrong!\n");
                    temp = 0;
                    break;
>>>>>>> PSE-univr-project/master
            }

            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);
        }
    }

    data.result0 = v0;
    data.result1 = v1;
}

<<<<<<< HEAD
bool xtea_AT4::get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data)
{
=======
bool xtea_AT4::get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data) {
>>>>>>> PSE-univr-project/master
    return false;
}

tlm::tlm_sync_enum xtea_AT4::nb_transport_fw(
<<<<<<< HEAD
    tlm::tlm_generic_payload &trans,
    tlm::tlm_phase &phase,
    sc_time &t)
{

    if (pending_transaction != NULL)
    { // Another transaction is pending
=======
        tlm::tlm_generic_payload &trans,
        tlm::tlm_phase &phase,
        sc_time &t) {

    if (pending_transaction != nullptr) { // Another transaction is pending
>>>>>>> PSE-univr-project/master
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

<<<<<<< HEAD
    if (phase != tlm::BEGIN_REQ)
    { // Phase must be BEGIN_REQ
=======
    if (phase != tlm::BEGIN_REQ) { // Phase must be BEGIN_REQ
>>>>>>> PSE-univr-project/master
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    pending_transaction = &trans;
<<<<<<< HEAD
    data = *((iostruct *)trans.get_data_ptr());
=======
    data = *((iostruct *) trans.get_data_ptr());
>>>>>>> PSE-univr-project/master

    phase = tlm::END_REQ;
    io_event.notify();

    return tlm::TLM_UPDATED;
}

<<<<<<< HEAD
unsigned int xtea_AT4::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}

void xtea_AT4::ioprocess()
{
    sc_time timing_annotation;

    while (true)
    {
=======
#pragma clang diagnostic push

#pragma clang diagnostic ignored "-Wmissing-noreturn"
void xtea_AT4::ioprocess() {
    sc_time timing_annotation;

    while (true) {
>>>>>>> PSE-univr-project/master
        wait(io_event);

        wait(100, SC_NS);

<<<<<<< HEAD
        if (pending_transaction->is_write())
        {
=======
        if (pending_transaction->is_write()) {
>>>>>>> PSE-univr-project/master
            xtea();
        }

        pending_transaction->set_response_status(tlm::TLM_OK_RESPONSE);
<<<<<<< HEAD
        *((iostruct *)pending_transaction->get_data_ptr()) = data;
=======
        *((iostruct *) pending_transaction->get_data_ptr()) = data;
>>>>>>> PSE-univr-project/master
        tlm::tlm_phase phase = tlm::BEGIN_RESP;

        target_socket->nb_transport_bw(*pending_transaction, phase, timing_annotation);

<<<<<<< HEAD
        pending_transaction = NULL;
    }
}

=======
        pending_transaction = nullptr;
    }
}

#pragma clang diagnostic pop

unsigned int xtea_AT4::transport_dbg(tlm::tlm_generic_payload &trans) { return 0; }

>>>>>>> PSE-univr-project/master
void xtea_AT4::end_of_elaboration() {}

void xtea_AT4::reset() {}