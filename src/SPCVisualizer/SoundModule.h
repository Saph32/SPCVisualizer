#pragma once

#include "BaseTypes.h"
#include "GTypes.h"

#include <fstream>
#include <string>
#include <mutex>
#include <deque>

class SoundModule final {
  public:

      struct VisState
      {
          std::deque<int16> sampsL;
          std::deque<int16> sampsR;

          int16 keyOn[8] = {0};

          G::EnvMode envMode[8] = {G::EnvModeRelease};
      };

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

    VisState& RefVis() { return m_visState; }
    VisState GetVis();

  private:
    uint8 m_aRam[64 * 1024] = {};

    int m_dspClocks = 0;
    int m_smpClocks = 0;

    // std::ofstream waveFile;

    // int fileSize = 0;

    int16* m_pStream      = nullptr;
    int    m_iSamplesLeft = 0;

    VisState m_visState = {};
    std::mutex m_mutex;
};

extern SoundModule g_oSoundModule;