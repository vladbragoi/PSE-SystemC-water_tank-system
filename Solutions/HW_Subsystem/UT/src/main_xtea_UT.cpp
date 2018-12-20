//
// Created by vlad on 18/12/18.
//

#include "xtea_UT_testbench.h"
#include "xtea_UT.h"

class xtea_top : public sc_module
{

  private:
    xtea_UT m_target;
    xtea_UT_testbench m_initiator;

  public:
    xtea_top(sc_module_name name) : sc_module(name),
                                    m_target("target"),
                                    m_initiator("initiator")
    {
        m_initiator.initiator_socket(m_target.target_socket);
    }
};

int main(int argc, char *argv[])
{
    xtea_top top("top");
    sc_start();

    return 0;
}