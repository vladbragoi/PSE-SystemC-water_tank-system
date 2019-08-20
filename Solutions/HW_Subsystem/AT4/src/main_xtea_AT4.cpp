//
// Created by vlad on 19/12/18.
//

#include "xtea_AT4_testbench.h"
#include "xtea_AT4.h"

<<<<<<< HEAD
class xtea_top : public sc_module
{

  private:
    xtea_AT4 m_target;
    xtea_AT4_testbench m_initiator;

  public:
    xtea_top(sc_module_name name) : sc_module(name),
                                    m_target("target"),
                                    m_initiator("initiator")
    {
=======
class xtea_top : public sc_module {
private:
    xtea_AT4 m_target;
    xtea_AT4_testbench m_initiator;

public:
    explicit xtea_top(sc_module_name name) : sc_module(name), m_target("target"), m_initiator("initiator") {
>>>>>>> PSE-univr-project/master
        m_initiator.initiator_socket(m_target.target_socket);
    }
};

<<<<<<< HEAD
int main(int argc, char *argv[])
{
=======
int sc_main(int argc, char *argv[]) {
>>>>>>> PSE-univr-project/master
    xtea_top top("top");
    sc_start();

    return 0;
}