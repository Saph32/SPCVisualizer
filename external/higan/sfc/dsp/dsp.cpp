#include "dsp.hpp"
#include "smp.hpp"
#include "SoundModule.h"

#include <cstring>

#define DSP_CPP
namespace SuperFamicom {

    DSP dsp;

#define REG(n) state.regs[r_##n]
#define VREG(n) state.regs[v.vidx + v_##n]

#include "gaussian.cpp"
#include "envelope.cpp"
#include "brr.cpp"
#include "echo.cpp"

    /* timing */

    void DSP::enter() {

        switch (cur_step)
        {

        case 0:
            voice_5(voice[0]);
            voice_2(voice[1]);
            break;

        case 1:
            voice_6(voice[0]);
            voice_3(voice[1]);
            break;

        case 2:
            voice_7(voice[0]);
            voice_4(voice[1]);
            voice_1(voice[3]);
            break;

        case 3:
            voice_8(voice[0]);
            voice_5(voice[1]);
            voice_2(voice[2]);
            break;

        case 4:
            voice_9(voice[0]);
            voice_6(voice[1]);
            voice_3(voice[2]);
            break;

        case 5:
            voice_7(voice[1]);
            voice_4(voice[2]);
            voice_1(voice[4]);
            break;

        case 6:
            voice_8(voice[1]);
            voice_5(voice[2]);
            voice_2(voice[3]);
            break;

        case 7:
            voice_9(voice[1]);
            voice_6(voice[2]);
            voice_3(voice[3]);
            break;

        case 8:
            voice_7(voice[2]);
            voice_4(voice[3]);
            voice_1(voice[5]);
            break;

        case 9:
            voice_8(voice[2]);
            voice_5(voice[3]);
            voice_2(voice[4]);
            break;

        case 10:
            voice_9(voice[2]);
            voice_6(voice[3]);
            voice_3(voice[4]);
            break;

        case 11:
            voice_7(voice[3]);
            voice_4(voice[4]);
            voice_1(voice[6]);
            break;

        case 12:
            voice_8(voice[3]);
            voice_5(voice[4]);
            voice_2(voice[5]);
            break;

        case 13:
            voice_9(voice[3]);
            voice_6(voice[4]);
            voice_3(voice[5]);
            break;

        case 14:
            voice_7(voice[4]);
            voice_4(voice[5]);
            voice_1(voice[7]);
            break;

        case 15:
            voice_8(voice[4]);
            voice_5(voice[5]);
            voice_2(voice[6]);
            break;

        case 16:
            voice_9(voice[4]);
            voice_6(voice[5]);
            voice_3(voice[6]);
            break;

        case 17:
            voice_1(voice[0]);
            voice_7(voice[5]);
            voice_4(voice[6]);
            break;

        case 18:
            voice_8(voice[5]);
            voice_5(voice[6]);
            voice_2(voice[7]);
            break;

        case 19:
            voice_9(voice[5]);
            voice_6(voice[6]);
            voice_3(voice[7]);
            break;

        case 20:
            voice_1(voice[1]);
            voice_7(voice[6]);
            voice_4(voice[7]);
            break;

        case 21:
            voice_8(voice[6]);
            voice_5(voice[7]);
            voice_2(voice[0]);
            break;

        case 22:
            voice_3a(voice[0]);
            voice_9(voice[6]);
            voice_6(voice[7]);
            echo_22();
            break;

        case 23:
            voice_7(voice[7]);
            echo_23();
            break;

        case 24:
            voice_8(voice[7]);
            echo_24();
            break;

        case 25:
            voice_3b(voice[0]);
            voice_9(voice[7]);
            echo_25();
            break;

        case 26:
            echo_26();
            break;

        case 27:
            misc_27();
            echo_27();
            break;

        case 28:
            misc_28();
            echo_28();
            break;

        case 29:
            misc_29();
            echo_29();
            break;

        case 30:
            misc_30();
            voice_3c(voice[0]);
            echo_30();
            break;

        case 31:
            voice_4(voice[0]);
            voice_1(voice[2]);
            break;
        }
        cur_step++;
        if (cur_step > 31)
        {
            cur_step = 0;
        }
        g_oSoundModule.AddDSPClock(3 * 8);
    }

    /* register interface for S-SMP $00f2,$00f3 */

    bool DSP::mute() {
        return state.regs[r_flg] & 0x40;
    }

    uint8 DSP::read(uint8 addr) {
        return state.regs[addr];
    }

    void DSP::write(uint8 addr, uint8 data) {
        state.regs[addr] = data;

        if ((addr & 0x0f) == v_envx) {
            state.envx_buf = data;
        }
        else if ((addr & 0x0f) == v_outx) {
            state.outx_buf = data;
        }
        else if (addr == r_kon) {
            state.new_kon = data;
        }
        else if (addr == r_endx) {
            //always cleared, regardless of data written
            state.endx_buf = 0;
            state.regs[r_endx] = 0;
        }
    }

    /* initialization */

    void DSP::power() {
        memset(&state.regs, 0, sizeof state.regs);
        state.echo_hist_pos = 0;
        state.every_other_sample = false;
        state.kon = 0;
        state.noise = 0;
        state.counter = 0;
        state.echo_offset = 0;
        state.echo_length = 0;
        state.new_kon = 0;
        state.endx_buf = 0;
        state.envx_buf = 0;
        state.outx_buf = 0;
        state.t_pmon = 0;
        state.t_non = 0;
        state.t_eon = 0;
        state.t_dir = 0;
        state.t_koff = 0;
        state.t_brr_next_addr = 0;
        state.t_adsr0 = 0;
        state.t_brr_header = 0;
        state.t_brr_byte = 0;
        state.t_srcn = 0;
        state.t_esa = 0;
        state.t_echo_disabled = 0;
        state.t_dir_addr = 0;
        state.t_pitch = 0;
        state.t_output = 0;
        state.t_looped = 0;
        state.t_echo_ptr = 0;
        state.t_main_out[0] = state.t_main_out[1] = 0;
        state.t_echo_out[0] = state.t_echo_out[1] = 0;
        state.t_echo_in[0] = state.t_echo_in[1] = 0;

        for (unsigned i = 0; i < 8; i++) {
            voice[i].buf_pos = 0;
            voice[i].interp_pos = 0;
            voice[i].brr_addr = 0;
            voice[i].brr_offset = 1;
            voice[i].vbit = 1 << i;
            voice[i].vidx = i * 0x10;
            voice[i].kon_delay = 0;
            voice[i].env_mode = env_release;
            voice[i].env = 0;
            voice[i].t_envx_out = 0;
            voice[i].hidden_env = 0;
        }
    }

    void DSP::reset() {
        REG(flg) = 0xe0;

        state.noise = 0x4000;
        state.echo_hist_pos = 0;
        state.every_other_sample = 1;
        state.echo_offset = 0;
        state.counter = 0;

        cur_step = 0;
    }

    void DSP::reload_state()
    {
        //for (int i = 0; i < 128; ++i)
        //{
        //    write(i, state.regs[i]);
        //}

        state.t_esa = REG(esa);
        state.t_echo_disabled = REG(flg);
        state.echo_length = (REG(edl) & 0x0f) << 11;
        state.t_pmon = REG(pmon) & ~1;
        state.t_non = REG(non);
        state.t_eon = REG(eon);
        state.t_dir = REG(dir);
        state.t_koff = REG(koff);
        state.endx_buf = REG(endx) | state.t_looped;
        for (auto& v : voice)
        {
            state.t_dir_addr = (state.t_dir << 8) + (state.t_srcn << 2);
            state.t_srcn = VREG(srcn);
        }
    }

#undef REG
#undef VREG

}