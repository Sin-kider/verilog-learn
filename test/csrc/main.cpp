#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"

#ifdef NVBOARD
#include "nvboard.h"

static TOP_NAME dut;

void nvboard_bind_all_pins(Vtop* top);

static void single_cycle() {
  dut.a = 0; dut.eval();
  dut.a = 1; dut.eval();
}


int main() {
  nvboard_bind_all_pins(&dut);
  nvboard_init();

  while(1) {
    nvboard_update();
    single_cycle();
  }
}
#else 


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

int main() 
{
    sim_init();

    top->s=0;   top->a=0;   top->b=0;   step_and_dump_wave();
                            top->b=1;   step_and_dump_wave();
                top->a=1;   top->b=0;   step_and_dump_wave();
                            top->b=1;   step_and_dump_wave();
    top->s=1;   top->a=0;   top->b=0;   step_and_dump_wave();
                            top->b=1;   step_and_dump_wave();
                top->a=1;   top->b=0;   step_and_dump_wave();
                            top->b=1;   step_and_dump_wave();

    sim_exit();
}
#endif
