//
// Created by vlad on 05/01/19.
//

#include "Controller.h"

Controller::Controller(sc_module_name name) : sc_module(name) {
    tank_socket(*this);
    xtea_socket(*this);
    threshold = INITIAL_THRSHOLD;
    water_level = INITIAL_W_LEVEL;

    SC_THREAD(run);

    tlm_utils::tlm_quantumkeeper::set_global_quantum(sc_time(500, SC_NS));
    q_keeper.reset();
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void Controller::run() {
    tlm::tlm_generic_payload payload;
    sc_time local_time;
    xtea_data xtea_packet;
    tank_data tank_packet;
    uint32_t *result = nullptr;
    uint64_t *p = nullptr;
    double *ptr = nullptr;

    while (true) {
        wait(4, SC_SEC);

        // Receiving water level
        payload.set_data_ptr((unsigned char *) &tank_packet);
        payload.set_address(0);
        payload.set_read();

        local_time = q_keeper.get_local_time();
        tank_socket->b_transport(payload, local_time);

        q_keeper.set(local_time);
        if (q_keeper.need_sync()) {
            q_keeper.sync();
        }

        if (payload.get_response_status() == tlm::TLM_OK_RESPONSE) {
            water_level = tank_packet.water_level;
        }

        // ---------- COMMAND ENCRYPTION ----------
        if (water_level >= WATER_LOW_LEVEL && water_level <= WATER_HIGH_LEVEL) {
            result = xtea_encrypt(IDLE, 0);
        } else if (water_level > WATER_HIGH_LEVEL) {
            result = xtea_encrypt(CLOSE, 0);
            threshold *= 0.7;
        } else if (water_level < WATER_LOW_LEVEL) {
            result = xtea_encrypt(OPEN, 0);
            threshold *= 1.1;
        }
        xtea_packet.command[0] = result[0];
        xtea_packet.command[1] = result[1];


        // ---------- THRESHOLD ENCRYPTION ----------
        // double to uint64_t conversion (because xtea wants 2 variables of type uint32_t)
        ptr = &threshold;
        p = (uint64_t *) ptr;
        uint64_t tmp = *p;

        result = xtea_encrypt(static_cast<uint32_t>(tmp), static_cast<uint32_t>(tmp >> 32));
        xtea_packet.threshold[0] = result[0];
        xtea_packet.threshold[1] = result[1];

        // Sending command and threshold payload
        payload.set_data_ptr((unsigned char *) &xtea_packet);
        payload.set_address(0);
        payload.set_write();

        local_time = q_keeper.get_local_time();
        xtea_socket->b_transport(payload, local_time);

        // Synchronizing
        q_keeper.set(local_time);
        if (q_keeper.need_sync()) {
            q_keeper.sync();
        }
    }
}

#pragma clang diagnostic pop

uint32_t *Controller::xtea_encrypt(uint32_t first, uint32_t second) {
    uint64_t sum;
    uint32_t delta, v0, v1, temp;
    auto *result = new uint32_t[2];
    v0 = first;
    v1 = second;

    sum = 0;

    delta = DELTA;
    for (int i = 0; i < 32; i++) {
        if ((sum & 3) == 0)
            temp = KEY0;
        else if ((sum & 3) == 1)
            temp = KEY1;
        else if ((sum & 3) == 2)
            temp = KEY2;
        else
            temp = KEY3;

        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);

        sum += delta;

        if (((sum >> 11) & 3) == 0)
            temp = KEY0;
        else if (((sum >> 11) & 3) == 1)
            temp = KEY1;
        else if (((sum >> 11) & 3) == 2)
            temp = KEY2;
        else
            temp = KEY3;

        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
    }

    result[0] = v0;
    result[1] = v1;
    return result;
}
