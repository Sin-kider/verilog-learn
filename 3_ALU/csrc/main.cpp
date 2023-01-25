#include "iostream"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"

VerilatedContext* contextp = NULL;
VerilatedVcdC* tfp = NULL;

static Vtop* top;

void step_and_dump_wave()
{
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}

void sim_init()
{
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    top = new Vtop;
    contextp->traceEverOn(true);
    top->trace(tfp, 3);
    tfp->open("./wave.vcd");
}

void sim_exit()
{
    step_and_dump_wave();
    tfp->close();
}

void print_4bin(unsigned char binnum)
{
    for (unsigned char i = 0; i < 4; i++)
    {
        std::cout << (!(!(binnum & (0b1000 >> i))));
    }
}

int two2sign(unsigned char twonum)
{
    int signnum = 0;
    if (!(twonum & 0b00001000))
    {
        for (int i = 0; i < 3; i++)
        {
            signnum += (!(!(twonum & (1 << i)))) * (1 << i);
        }
    }
    else
    {
        if ((twonum & 0x0F) == 0b1000)
        {
            return -8;
        }
        for (int i = 0; i < 3; i++)
        {
            signnum -= (!(!(~(twonum - 1) & (1 << i)))) * (1 << i);
        }
    }
    return signnum;
}

unsigned char sign2two(int signnum) 
{

    unsigned char twonum = 0b1000;
    if (signnum >= 0)
    {
        twonum = signnum;
        return twonum;
    }
    else
    {
        twonum = (signnum & 0b00000111) | 0b00001000;
        return twonum;
    }
}

int main()
{
    sim_init();
//
    top->a      = sign2two(-1);
    top->b      = sign2two(-3);
    top->cin    = sign2two(0);
    step_and_dump_wave();
    std::cout << "a = " << two2sign(int(top->a)) << " "; print_4bin(top->a); std::cout << std::endl;
    std::cout << "b = " << two2sign(int(top->b)) << " "; print_4bin(top->b); std::cout << std::endl;
    std::cout << "cin = " << two2sign(int(top->cin)) << " "; print_4bin(top->cin); std::cout << std::endl;
    std::cout << "sum = " << two2sign(int(top->sum)) << " "; print_4bin(top->sum); std::cout << std::endl;
    // std::cout << "cout = " << two2sign(int(top->cout)) << " "; print_4bin(top->cout); std::cout << std::endl;
    std::cout << std::endl;
//
    sim_exit();
}
