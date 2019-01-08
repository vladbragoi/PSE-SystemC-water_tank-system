//
// Created by vlad on 05/01/19.
//

#include "controller.h"

controller::controller(sc_module_name name) : sc_module(name)
{
    watertank_socket(*this);
    xtea_socket(*this);

    threshold = 0.7;
    water_level = 0;

    SC_THREAD(run);

    q_keeper.set_global_quantum(sc_time(500, SC_NS));
    q_keeper.reset();
}

void controller::run()
{
    sc_time local_time;
    xtea_data xtea_packet;
    tank_data tank_packet;
    tlm::tlm_generic_payload payload;

    while (true)
    {
        local_time = q_keeper.get_local_time();

        payload.set_data_ptr((unsigned char *)&tank_packet);
        payload.set_address(0);
        payload.set_read();

        local_time = q_keeper.get_local_time();
        watertank_socket->b_transport(payload, local_time);

        q_keeper.set(local_time);
        if (q_keeper.need_sync())
        {
            // cout << "SYNCHRONIZING" << endl;
            q_keeper.sync();
        }

        if (payload.get_response_status() == tlm::TLM_OK_RESPONSE)
        {
            water_level = tank_packet.water_level;
        }
        xtea_packet.key[0] = key[0];
        xtea_packet.key[1] = key[1];
        xtea_packet.key[2] = key[2];
        xtea_packet.key[3] = key[3];
        if (water_level >= 5 && water_level <= 8.8)
        {
            xtea(IDLE, /*threshold,*/ xtea_packet.word[0], xtea_packet.word[1]);
        }
        else if (water_level > 8.8)
        {
            xtea(CLOSE, /*threshold,*/ xtea_packet.word[0], xtea_packet.word[1]);
            threshold *= 0.7;
        }
        else if (water_level < 5)
        {
            xtea(OPEN, /*threshold,*/ xtea_packet.word[0], xtea_packet.word[1]);
            threshold *= 1.1;
        }

        payload.set_data_ptr((unsigned char *)&xtea_packet);
        payload.set_address(0);
        payload.set_write();

        local_time = q_keeper.get_local_time();
        xtea_socket->b_transport(payload, local_time);
        if (payload.get_response_status() == tlm::TLM_OK_RESPONSE)
        {
            aperture_threshold.write(threshold);
        }

        q_keeper.set(local_time);
        if (q_keeper.need_sync())
        {
            // cout << "SYNCHRONIZING" << endl;
            q_keeper.sync();
        }
        wait(4, SC_SEC);
    }
}

void controller::xtea(uint32_t command, /*uint32_t v1,*/ sc_uint<32> &result0, sc_uint<32> &result1)
{
    uint64_t sum;
    uint32_t delta, v0, v1, temp;
    v0 = command;
    v1 = 0;
    sum = 0;

    delta = 0x9e3779b9;
    for (int i = 0; i < 32; i++)
    {
        if ((sum & 3) == 0)
            temp = key[0];
        else if ((sum & 3) == 1)
            temp = key[1];
        else if ((sum & 3) == 2)
            temp = key[2];
        else
            temp = key[3];

        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);

        sum += delta;

        if (((sum >> 11) & 3) == 0)
            temp = key[0];
        else if (((sum >> 11) & 3) == 1)
            temp = key[1];
        else if (((sum >> 11) & 3) == 2)
            temp = key[2];
        else
            temp = key[3];

        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
    }

    result0 = v0;
    result1 = v1;
}

void controller::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range) {}

tlm::tlm_sync_enum controller::nb_transport_bw(
    tlm::tlm_generic_payload &trans,
    tlm::tlm_phase &phase,
    sc_time &t)
{
    return tlm::TLM_COMPLETED;
}