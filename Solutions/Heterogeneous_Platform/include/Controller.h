//
// Created by vlad on 05/01/19.
//

#pragma once

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include "iostruct.h"
#include "command.h"
#include "params.h"

#define INITIAL_THRSHOLD 0.7
#define INITIAL_W_LEVEL 0
#define WATER_HIGH_LEVEL 8.8
#define WATER_LOW_LEVEL 5

/**
 * This module performs water level monitoring:
 * - If the water level is between 5 and 8: encrypt and send the valve the command IDLE;
 * - If the water level is greater than 8.8: modify every 5 seconds the valve aperture threshold s.t.
 *      t = t ∗ 0.7 and send the valve the command CLOSE;
 * - If the water level is lower then 5: modify every 5 seconds the valve aperture threshold s.t.
 *      t = t ∗ 1.1 and send the valve the command OPEN.
 */
class Controller :
        public sc_module,
        public virtual tlm::tlm_bw_transport_if<> {
public:
    SC_HAS_PROCESS(Controller);

    explicit Controller(sc_module_name name);

    void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range) override {};

    tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t) override {
        return tlm::TLM_COMPLETED;
    };

    tlm::tlm_initiator_socket<> tank_socket;
    tlm::tlm_initiator_socket<> xtea_socket;

private:
    void run();

    uint32_t *xtea_encrypt(uint32_t first, uint32_t second); // encryption only

    double water_level;
    double threshold;
    tlm_utils::tlm_quantumkeeper q_keeper;
};
