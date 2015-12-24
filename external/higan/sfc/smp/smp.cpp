#include "smp.hpp"
#include "dsp.hpp"
#include "SoundModule.h"

#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 255);

#define SMP_CPP
namespace SuperFamicom {

SMP smp;

void SMP::step(unsigned clocks) {
    g_oSoundModule.AddSMPClock(clocks);
}

void SMP::enter() {
    op_step();
}

void SMP::power() {
  //targets not initialized/changed upon reset
  timer0.target = 0;
  timer1.target = 0;
  timer2.target = 0;
}

void SMP::reset() {

  regs.pc = 0xffc0;
  regs.a = 0x00;
  regs.x = 0x00;
  regs.y = 0x00;
  regs.s = 0xef;
  regs.p = 0x02;

  uint16 uiAddr = 0;
  do
  {
      g_oSoundModule.WriteRam(uiAddr, dis(gen));
  } while (++uiAddr);

  g_oSoundModule.WriteRam(0x00f4, 0x00);
  g_oSoundModule.WriteRam(0x00f5, 0x00);
  g_oSoundModule.WriteRam(0x00f6, 0x00);
  g_oSoundModule.WriteRam(0x00f7, 0x00);

  status.clock_counter = 0;
  status.dsp_counter = 0;
  status.timer_step = 3;

  //$00f0
  status.clock_speed = 0;
  status.timer_speed = 0;
  status.timers_enable = true;
  status.ram_disable = false;
  status.ram_writable = true;
  status.timers_disable = false;

  //$00f1
  status.iplrom_enable = true;

  //$00f2
  status.dsp_addr = 0x00;

  //$00f8,$00f9
  status.ram00f8 = 0x00;
  status.ram00f9 = 0x00;

  timer0.stage0_ticks = 0;
  timer1.stage0_ticks = 0;
  timer2.stage0_ticks = 0;

  timer0.stage1_ticks = 0;
  timer1.stage1_ticks = 0;
  timer2.stage1_ticks = 0;

  timer0.stage2_ticks = 0;
  timer1.stage2_ticks = 0;
  timer2.stage2_ticks = 0;

  timer0.stage3_ticks = 0;
  timer1.stage3_ticks = 0;
  timer2.stage3_ticks = 0;

  timer0.current_line = 0;
  timer1.current_line = 0;
  timer2.current_line = 0;

  timer0.enable = false;
  timer1.enable = false;
  timer2.enable = false;
}

void SMP::reload_state()
{
    uint8 aAddrs[] = { 0xF1, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF, 0xF4, 0xF5, 0xF6, 0xF7 , 0xF8, 0xF9};

    for (auto addr : aAddrs)
    {
        op_buswrite(addr, g_oSoundModule.ReadRam(addr));
    }
}

SMP::SMP() {
  for(auto& byte : iplrom) byte = 0;
}

SMP::~SMP() {
}

}
