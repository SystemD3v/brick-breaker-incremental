#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "constants.h"
#include "audio_functions.h"

// Initialize mixer
void _audio_initializeMixer() {

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        SDL_Quit();  // Clean up SDL if SDL_mixer fails to initialize
        return;
    }

    // Allocation of channels
    Mix_AllocateChannels(MAX_AUDIO_CHANNELS);
}

// Load and play audio on specified channel
void _audio_loadAndPlay(char* file, int channel) {

    // Load sound
    Mix_Chunk* sound = Mix_LoadWAV(file);
    if (!sound) {
        printf("Failed to load sound: %s\n", Mix_GetError());
        return;
    }

    // Play on said channel
    Mix_PlayChannel(channel, sound, 0); // -1 means select the first free channel
}


// Load and play audio on specified channel
void _audio_loadAndPlayLoop(char* file, int channel, int loops) {

    // Load sound
    Mix_Chunk* sound = Mix_LoadWAV(file);
    if (!sound) {
        printf("Failed to load sound: %s\n", Mix_GetError());
        return;
    }

    // Play on said channel with specified loops
    Mix_PlayChannel(channel, sound, loops); // -1 means select the first free channel, loops = -1 for infinite looping
}

// Stop audio on a specific channel
void _audio_stopOnChannel(int channel) {
    if (Mix_Playing(channel)) {
        Mix_HaltChannel(channel); // Stop the audio on the specific channel
    }
}



// Perform the audio cleanup
void _audio_cleanup() {
    Mix_CloseAudio();
}
