//
// Created by vlad on 14/11/18.
//

#include "Xtea.h"

#define N_CYCLES 64

void Xtea::fsm() {
    NEXT_STATUS = STATUS;

    switch (STATUS) {
        case RESET:
            NEXT_STATUS = ST_READ;
            break;
        case ST_READ:
            if (din_rdy.read() == 1) {
                if (mode.read() == 0) {
                    NEXT_STATUS = ST_M0;
                } else {
                    NEXT_STATUS = ST_M1;
                }
            } else NEXT_STATUS = ST_READ;
            break;
        case ST_M0:
            if (counter.read() < N_CYCLES)
                NEXT_STATUS = ST_K;
            else
                NEXT_STATUS = ST_WRITE;
            break;
        case ST_M1:
            if (counter.read() < N_CYCLES)
                NEXT_STATUS = ST_K;
            else
                NEXT_STATUS = ST_WRITE;
            break;
        case ST_K:
            NEXT_STATUS = ST_CALC;
            break;
        case ST_CALC:
            NEXT_STATUS = ST_SUM;
            break;
        case ST_SUM:
            if (mode.read() == 0)
                NEXT_STATUS = ST_M0;
            else
                NEXT_STATUS = ST_M1;
            break;
        case ST_WRITE:
//            NEXT_STATUS = RESET;
            break;
        default:
            break;
    }
}

void Xtea::datapath() {
    if (rst.read() != 0) {
        STATUS = RESET;
    } else if (clk.read() == 1) {
        STATUS = NEXT_STATUS;

        switch (STATUS) {
            case RESET:
                result0.write(0);
                result1.write(0);
                dout_rdy.write(false);
                counter = 0;
                delta = DELTA;
                k = 0;
                break;
            case ST_READ:
                v0 = word0.read();
                v1 = word1.read();
                if (mode.read() == 0)
                    sum.write(0);
                else
                    sum.write(delta.read() * 32);

                break;
            case ST_M0:
                if ((counter.read() % 2) == 0) {        // even cycle
                    k.write(sum.read() & 3);
                } else {
                    k.write((sum.read() >> 11) & 3);    // odd cycle
                };
                break;
            case ST_M1:
                if ((counter.read() % 2) == 0) {        // even cycle
                    k.write((sum.read() >> 11) & 3);
                } else {
                    k.write(sum.read() & 3);            // odd cycle
                };
                break;
            case ST_K:
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
                if (mode.read() == 0) {     // ENCRYPTION MODE
                    if ((counter.read() % 2) == 0) {
                        v0.write(v0.read() +
                                 ((((v1.read() << 4) ^ (v1.read() >> 5)) + v1.read()) ^ (sum.read() + key.read())));
                    } else {
                        v1.write(v1.read() +
                                 ((((v0.read() << 4) ^ (v0.read() >> 5)) + v0.read()) ^ (sum.read() + key.read())));
                    }
                } else {                      // DECRYPTION MODE
                    if (counter.read() % 2 == 0) {
                        v1.write(v1.read() -
                                 ((((v0.read() << 4) ^ (v0.read() >> 5)) + v0.read()) ^ (sum.read() + key.read())));
                    } else {
                        v0.write(v0.read() -
                                 ((((v1.read() << 4) ^ (v1.read() >> 5)) + v1.read()) ^ (sum.read() + key.read())));
                    }
                };
                break;
            case ST_SUM:
                if ((counter.read() % 2) == 0) {
                    if (mode.read() == 0)
                        sum.write(sum.read() + delta.read());
                    else
                        sum.write(sum.read() - delta.read());
                };
                counter.write(counter.read() + 1);

                break;
            case ST_WRITE:
                result0.write(v0.read());
                result1.write(v1.read());
                dout_rdy.write(true);
                break;
            default:
                break;
        }
    }
}