//
// Created by vlad on 4/01/19.
//

#include "Transactor_xtea.h"


Transactor_xtea::Transactor_xtea(sc_module_name name) : sc_module(name),
                                                        target_socket("target_socket") {
    target_socket(*this);

    SC_THREAD(writeprocess);
    sensitive << clk.pos();
}

void Transactor_xtea::b_transport(tlm::tlm_generic_payload &trans, sc_time &t) {
    wait(0, SC_SEC);
    switch (trans.get_command()) {
        case tlm::TLM_READ_COMMAND:
            trans.set_response_status(tlm::TLM_OK_RESPONSE);
            break;
        case tlm::TLM_WRITE_COMMAND:
            data = *((xtea_data *) trans.get_data_ptr());
            begin_write.notify();
            wait(end_write);
            trans.set_response_status(tlm::TLM_OK_RESPONSE);
        case tlm::TLM_IGNORE_COMMAND:
            break;
    }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void Transactor_xtea::writeprocess() {
    while (true) {
        wait(begin_write);

        // Command decryption
        rst.write(true);
        wait();
        rst.write(false);
        word[0].write(data.command[0]);
        word[1].write(data.command[1]);
        key[0].write(KEY0);
        key[1].write(KEY1);
        key[2].write(KEY2);
        key[3].write(KEY3);
        mode.write(DECRYPT);
        din_rdy.write(true);

//        while(!dout_rdy.read()) {
//            wait();
//        }
        wait(5, SC_MS);

        // Threshold decryption
        rst.write(true);
        wait();
        rst.write(false);
        word[0].write(data.threshold[0]);
        word[1].write(data.threshold[1]);
        key[0].write(KEY0);
        key[1].write(KEY1);
        key[2].write(KEY2);
        key[3].write(KEY3);
        mode.write(DECRYPT);
        din_rdy.write(true);

        end_write.notify();
        wait();
    }
}

#pragma clang diagnostic pop

void Transactor_xtea::end_of_elaboration() { reset(); }

void Transactor_xtea::reset() {
    rst.write(true);
    din_rdy.write(false);
}