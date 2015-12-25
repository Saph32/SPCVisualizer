#pragma once

#include "BaseTypes.h"

#include <fstream>
#include <string>

class SoundModule {
  public:
    SoundModule() = default;

    uint8 ReadRam(uint16 uiAddr);
    void WriteRam(uint16 uiAddr, uint8 uiData);

    void PushSample(int16 iLeft, int16 iRight);

    uint8 ReadDspReg(uint8 uiAddr);
    void WriteDspReg(uint8 uiAddr, uint8 uiData);

    void AddDSPClock(int clocks) { m_dspClocks += clocks; }
    void AddSMPClock(int clocks) { m_smpClocks += clocks; }

    void Init();
    int Run(int clocks);
    void GenerateSamples(int16* pStream, int nbSamples);

    bool LoadSPCFile(std::string fileName);

  private:
    uint8 m_aRam[64 * 1024] = {};

    int m_dspClocks = 0;
    int m_smpClocks = 0;

    // std::ofstream waveFile;

    // int fileSize = 0;

    int16* m_pStream      = nullptr;
    int    m_iSamplesLeft = 0;
};

extern SoundModule g_oSoundModule;