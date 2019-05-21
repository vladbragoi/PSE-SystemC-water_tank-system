//
// Created by vlad on 18/12/18.
//

#include "xtea_UT.h"

xtea_UT::xtea_UT(sc_module_name name) : sc_module(name),
                                        target_socket("target_socket"),
                                        pending_transaction(NULL) {
    target_socket(*this);
}

void xtea_UT::b_transport(tlm::tlm_generic_payload &trans, sc_time &t) {
    data = *((iostruct *) trans.get_data_ptr());
    if (trans.is_write()) {
        xtea(data.word0, data.word1, data.mode, data.key0, data.key1, data.key2, data.key3);

        trans.set_response_status(tlm::TLM_OK_RESPONSE);

        data.result0 = res0;
        data.result1 = res1;
        *((iostruct *) trans.get_data_ptr()) = data;
    } else if (trans.is_read()) {
        data.result0 = res0;
        data.result1 = res1;
        *((iostruct *) trans.get_data_ptr()) = data;
    }
}

void xtea_UT::xtea(uint32_t word0, uint32_t word1, bool mode,
                   uint32_t key0, uint32_t key1, uint32_t key2, uint32_t key3) {
    uint32_t i, delta, v0, v1, temp;
    uint64_t sum;
    v0 = word0;
    v1 = word1;
    res0 = 0;
    res1 = 0;
    sum = 0;

    if (mode == 0) {
        // encipher
        delta = 0x9e3779b9;
        for (i = 0; i < 32; i++) {
            switch (sum & 3) {
                case 0:
                    temp = key0;
                    break;
                case 1:
                    temp = key1;
                    break;
                case 2:
                    temp = key2;
                    break;
                case 3:
                    temp = key3;
                    break;
                default:
                    printf("Something wrong!\n");
                    temp = 0;
                    break;
            }

            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);

            sum += delta;

            switch ((sum >> 11) & 3) {
                case 0:
                    temp = key0;
                    break;
                case 1:
                    temp = key1;
                    break;
                case 2:
                    temp = key2;
                    break;
                case 3:
                    temp = key3;
                    break;
                default:
                    printf("Something wrong!\n");
                    temp = 0;
                    break;
            }

            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
        }
    } else if (mode == 1) {
        // decipher
        delta = 0x9e3779b9;
        sum = delta * 32;
        for (i = 0; i < 32; i++) {
            switch ((sum >> 11) & 3) {
                case 0:
                    temp = key0;
                    break;
                case 1:
                    temp = key1;
                    break;
                case 2:
                    temp = key2;
                    break;
                case 3:
                    temp = key3;
                    break;
                default:
                    printf("Something wrong!\n");
                    temp = 0;
                    break;
            }

            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);

            sum -= delta;

            switch (sum & 3) {
                case 0:
                    temp = key0;
                    break;
                case 1:
                    temp = key1;
                    break;
                case 2:
                    temp = key2;
                    break;
                case 3:
                    temp = key3;
                    break;
                default:
                    printf("Something wrong!\n");
                    temp = 0;
                    break;
            }

            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);
        }
    }

    res0 = v0;
    res1 = v1;
}

bool xtea_UT::get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data) {
    return false;
}

tlm::tlm_sync_enum xtea_UT::nb_transport_fw(
        tlm::tlm_generic_payload &trans,
        tlm::tlm_phase &phase,
        sc_time &t) {
    return tlm::TLM_COMPLETED;
}

unsigned int xtea_UT::transport_dbg(tlm::tlm_generic_payload &trans) {
    return 0;
}

void xtea_UT::end_of_elaboration() {}

void xtea_UT::reset() {}