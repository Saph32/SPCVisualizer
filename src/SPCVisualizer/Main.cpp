#include "SoundModule.h"

#include <iostream>

#include "SDL.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#include "Visualizer.h"
#include "DGfx.h"

using namespace std;

SoundModule g_oSoundModule = {};

void SdlAudioCb(void* pUser, uint8* stream, int len) {
    g_oSoundModule.GenerateSamples(reinterpret_cast<int16*>(stream), len / 4);
}

int main(int argc, char* argv[]) {
    DGfx dGfx;

    if (!dGfx.Init()) {
        return 1;
    }

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        return 2;
    }

    SDL_AudioSpec spec = {};

    spec.channels = 2;
    spec.format   = AUDIO_S16LSB;
    spec.freq     = 32000;
    spec.samples  = 1024;
    spec.callback = &SdlAudioCb;

    if (SDL_OpenAudio(&spec, NULL) < 0) {
        return 1;
    }

    g_oSoundModule.Init();

    if (argc == 2) {
        g_oSoundModule.LoadSPCFile(argv[1]);
    } else {
        // g_oSoundModule.LoadSPCFile("D:\\emu\\spc\\chrono trigger\\102 Chrono Trigger (Looped).spc");
        g_oSoundModule.LoadSPCFile(R"(D:\emu\spc\chrono trigger\314 Last Battle.spc)");
    }

    // g_oSoundModule.Run(500000000);

    SDL_PauseAudio(0);

    Visualizer vis(dGfx);

    cin.get();

    SDL_CloseAudio();

    return 0;
}