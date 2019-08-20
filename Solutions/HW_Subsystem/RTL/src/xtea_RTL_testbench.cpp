//
// Created by vlad on 21/11/18.
//

#include "xtea_RTL_testbench.h"

<<<<<<< HEAD
void xtea_RTL_testbench::run()
{
    sc_uint<32> res0, res1;

    mode.write(0);
=======
void xtea_RTL_testbench::run() {
    sc_uint<32> res0, res1;

    mode.write(false);
>>>>>>> PSE-univr-project/master
    word0.write(0x12345678);
    word1.write(0x9abcdeff);
    key0.write(0x6a1d78c8);
    key1.write(0x8c86d67f);
    key2.write(0x2a65bfbe);
    key3.write(0xb4bd6e46);
<<<<<<< HEAD
    rst.write(0);
=======
    rst.write(false);
>>>>>>> PSE-univr-project/master

    wait();

    din_rdy.write(true);

    wait();

    din_rdy.write(false);

    while (dout_rdy.read() != 1)
        wait();
    res0 = result0.read();
    res1 = result1.read();

    printf("First invocation:\n");
    cout << "\t- the encryption of " << hex << word0.read() << " and " << hex << word1.read() << endl;
    cout << "\t- with key\n"
         << hex << key0.read() << hex << key1.read() << hex << key2.read() << hex << key3.read() << endl;
    cout << "is: " << hex << res0 << ", " << hex << res1 << endl;
    if ((res0 != 0x99bbb92b) || (res1 != 0x3ebd1644))
        printf("Wrong result!\n");

<<<<<<< HEAD
    mode.write(1);
=======
    mode.write(true);
>>>>>>> PSE-univr-project/master
    word0.write(res0);
    word1.write(res1);
    key0.write(0x6a1d78c8);
    key1.write(0x8c86d67f);
    key2.write(0x2a65bfbe);
    key3.write(0xb4bd6e46);
    rst.write(false);
    din_rdy.write(true);

    wait();

    din_rdy.write(false);
    while (dout_rdy.read() != 1)
        wait();
    res0 = result0.read();
    res1 = result1.read();

    printf("\nSecond invocation:\n");
    cout << "\t- the decryption of " << hex << word0.read() << " and " << hex << word1.read() << endl;
    cout << "\t- with key\n"
         << hex << key0.read() << hex << key1.read() << hex << key2.read() << hex << key3.read() << endl;
    cout << "is: " << hex << res0 << ", " << hex << res1 << endl;
    if ((res0 != 0x12345678) || (res1 != 0x9abcdeff))
        printf("Wrong result!\n");

    printf("\nDone!!\n");

    sc_stop();
}

<<<<<<< HEAD
void xtea_RTL_testbench::clk_gen()
{
    while (true)
    {
=======
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void xtea_RTL_testbench::clk_gen() {
    while (true) {
>>>>>>> PSE-univr-project/master
        clk.write(sc_dt::SC_LOGIC_1);
        wait(PERIOD / 2, sc_core::SC_NS);
        clk.write(sc_dt::SC_LOGIC_0);
        wait(PERIOD / 2, sc_core::SC_NS);
    }
}
<<<<<<< HEAD
=======

#pragma clang diagnostic pop
>>>>>>> PSE-univr-project/master
