//
// Created by vlad on 14/11/18.
//

#include "xtea_RTL.h"

#define N_CYCLES 64

void xtea_RTL::fsm() {
    NEXT_STATUS = STATUS;

    switch (STATUS) {
        case RESET:
            // cout << "DEBUG: FSM RESET" << endl;
            NEXT_STATUS = ST_READ;
            break;
        case ST_READ:
            // cout << "DEBUG: FSM ST_READ" << endl;
            if (din_rdy.read() == 1) {
                if (mode.read() == 0)
                    NEXT_STATUS = ST_M0;
                else
                    NEXT_STATUS = ST_M1;
            }
            // else NEXT_STATUS = ST_READ;
            break;
        case ST_M0:
            // cout << "DEBUG: FSM ST_M0" << endl;
            if (counter.read() < N_CYCLES)
                NEXT_STATUS = ST_K;
            else
                NEXT_STATUS = ST_WRITE;
            break;
        case ST_M1:
            // cout << "DEBUG: FSM ST_M1" << endl;
            if (counter.read() < N_CYCLES)
                NEXT_STATUS = ST_K;
            else
                NEXT_STATUS = ST_WRITE;
            break;
        case ST_K:
            // cout << "DEBUG: FSM ST_K" << endl;
            NEXT_STATUS = ST_CALC;
            break;
        case ST_CALC:
            // cout << "DEBUG: FSM ST_CALC" << endl;
            NEXT_STATUS = ST_SUM;
            break;
        case ST_SUM:
            // cout << "DEBUG: FSM ST_SUM" << endl;
            if (mode.read() == 0)
                NEXT_STATUS = ST_M0;
            else
                NEXT_STATUS = ST_M1;
            break;
        case ST_WRITE:
            // cout << "DEBUG: FSM ST_WRITE" << endl;
            NEXT_STATUS = RESET;
            break;
        default:
            break;
    }
}

void xtea_RTL::datapath() {
    if (rst.read() != 0) {
        STATUS = RESET;
    } else if (clk.read() == 1) {
        STATUS = NEXT_STATUS;

        switch (STATUS) {
            case RESET:
                // cout << "DEGUB: DP RESET" << endl;
                result0.write(0);
                result1.write(0);
                dout_rdy.write(false);
                break;
            case ST_READ:
                // cout << "DEGUB: DP ST_READ" << endl;
                result0.write(0);
                result1.write(0);
                v0 = word0.read();
                v1 = word1.read();
                dout_rdy.write(false);
                counter.write(0);
                delta.write(0x9e3779b9);
                k.write(0);

                if (mode.read() == 0)
                    sum.write(0);
                else
                    sum.write(delta.read() * 32);

                break;
            case ST_M0:
                // cout << "DEBUG: DP ST_M0" << endl;
                if ((counter.read() % 2) == 0) { // even cycle
                    k.write(sum.read() & 3);
                } else {
                    k.write((sum.read() >> 11) & 3); // odd cycle
                };
                break;
            case ST_M1:
                // cout << "DEBUG: DP ST_M1" << endl;
                if ((counter.read() % 2) == 0) { // even cycle
                    k.write((sum.read() >> 11) & 3);
                } else {
                    k.write(sum.read() & 3); // odd cycle
                };
                break;
            case ST_K:
                // cout << "DEBUG: DP ST_K" << endl;
                switch (k.read()) {
                    case 0:
                        key.write(key0.read());
                        break;
                    case 1:
                        key.write(key1.read());
                        break;
                    case 2:
                        key.write(key2.read());
                        break;
                    case 3:
                        key.write(key3.read());
                        break;
                    default:
                        break;
                }
                break;
            case ST_CALC:
                // cout << "DEBUG: DP ST_CALC" << endl;
                if (mode.read() == 0) { // encipher mode
                    if ((counter.read() % 2) == 0) {
                        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum.read() + key.read());
                    } else {
                        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum.read() + key.read());
                    }
                } else { // decipher mode
                    if (counter.read() % 2 == 0) {
                        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum.read() + key.read());
                    } else {
                        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum.read() + key.read());
                    }
                };
                break;
            case ST_SUM:
                // cout << "DEBUG: DP ST_SUM" << endl;
                if ((counter.read() % 2) == 0) {
                    if (mode.read() == 0)
                        sum.write(sum.read() + delta.read());
                    else
                        sum.write(sum.read() - delta.read());
                };
                counter.write(counter.read() + 1);
                break;
            case ST_WRITE:
                // cout << "DEBUG: DP ST_WRITE" << endl;
                result0.write(v0);
                result1.write(v1);
                dout_rdy.write(true);
                break;
            default:
                break;
        }
    }
}