#include "SoundModule.h"

#include "SPCFile.h"
#include "dsp.hpp"
#include "smp.hpp"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <memory>

using namespace std;
using namespace SuperFamicom;

bool bGo = false;

uint8 SoundModule::ReadRam(uint16 uiAddr) {
    // if (bGo)
    //    printf("R%04X:%02X\n", uiAddr, m_aRam[uiAddr]);
    return m_aRam[uiAddr];
}

void SoundModule::WriteRam(uint16 uiAddr, uint8 uiData) {
    // if (bGo)
    //    printf("W%04X:%02X\n", uiAddr, uiData);
    m_aRam[uiAddr] = uiData;
}

void SoundModule::PushSample(int16 iLeft, int16 iRight) {
    // auto l = (uint16)(iLeft);
    // waveFile.write((const char*)(&l), 2);
    // auto r = (uint16)(iRight);
    // waveFile.write((const char*)(&r), 2);

    if (m_iSamplesLeft <= 0) {
        return;
    }

    *m_pStream = iLeft;
    ++m_pStream;
    *m_pStream = iRight;
    ++m_pStream;

    m_iSamplesLeft--;

    if (m_visState.sampsL.size() >= 1024) {
        m_visState.sampsL.pop_front();
    }

    if (m_visState.sampsR.size() >= 1024) {
        m_visState.sampsR.pop_front();
    }

    m_visState.sampsL.push_back(iLeft);
    m_visState.sampsR.push_back(iRight);

    for (auto& rKeyOn : m_visState.keyOn)
    {
        if (rKeyOn > 0)
        {
            rKeyOn--;
        }
    }
}

uint8 SoundModule::ReadDspReg(uint8 uiAddr) {
    return dsp.read(uiAddr);
}

void SoundModule::WriteDspReg(uint8 uiAddr, uint8 uiData) {
    dsp.write(uiAddr, uiData);
}

void SoundModule::Init() {
    smp.power();
    dsp.power();
    smp.reset();
    dsp.reset();

    // waveFile = ofstream("e:\\temp\\spc.pcm", ios::out | ios::binary);
}

int SoundModule::Run(int clocks) {
    bGo               = true;
    int clocks_to_run = clocks;

    while (clocks_to_run > 0) {
        while (m_smpClocks <= 0) {
            smp.enter();
        }
        clocks_to_run -= m_smpClocks;
        m_dspClocks -= m_smpClocks;
        m_smpClocks = 0;

        while (m_dspClocks <= 0) {
            dsp.enter();
        }
        clocks_to_run -= m_dspClocks;
        m_smpClocks -= m_dspClocks;
        m_dspClocks = 0;
    }

    return clocks_to_run;
}

void SoundModule::GenerateSamples(int16* pStream, int nbSamples) {
    lock_guard<mutex> lock(m_mutex);

    m_pStream      = pStream;
    m_iSamplesLeft = nbSamples;

    while (m_iSamplesLeft > 0) {
        while (m_smpClocks <= 0) {
            smp.enter();
        }
        m_dspClocks -= m_smpClocks;
        m_smpClocks = 0;

        while (m_dspClocks <= 0) {
            dsp.enter();
        }
        m_smpClocks -= m_dspClocks;
        m_dspClocks = 0;
    }
}

bool SoundModule::LoadSPCFile(std::string fileName) {
    ifstream file(fileName, ios::in | ios::binary);

    if (!file) {
        return false;
    }

    auto pSPC = unique_ptr<SPCFile>(new SPCFile());

    memset(pSPC.get(), 0, sizeof(SPCFile));

    file.read((char*)(pSPC.get()), sizeof(SPCFile));

    if (!file) {
        return false;
    }

    smp.regs.a    = pSPC->a;
    smp.regs.x    = pSPC->x;
    smp.regs.y    = pSPC->y;
    smp.regs.p    = pSPC->psw;
    smp.regs.s    = pSPC->sp;
    smp.regs.pc.l = pSPC->pc[0];
    smp.regs.pc.h = pSPC->pc[1];

    for (int i = 0; i < 65536; ++i) {
        m_aRam[i] = pSPC->ram[i];
    }

    for (int i = 0; i < 128; ++i) {
        dsp.write(i, pSPC->dspRegs[i]);
    }

    dsp.reload_state();
    smp.reload_state();

    return true;
}

SoundModule::VisState SoundModule::GetVis() {
    lock_guard<mutex> lock(m_mutex);

    return m_visState;
}
