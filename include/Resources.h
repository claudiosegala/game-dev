#pragma once

#include <SDL_Include.h>
#include <unordered_map>
#include <string>
#include <tuple>

class Resources {
    public:

    static SDL_Texture* GetImage(std::string);

    static std::tuple<int, int> QueryImage(SDL_Texture*);

    static void ClearImages();

    static Mix_Music* GetMusic(std::string);

    static void ClearMusics();

    static Mix_Chunk* GetSound(std::string);

    static void ClearSounds();

    private:

    static std::unordered_map<std::string, SDL_Texture*> imageTable;

    static std::unordered_map<std::string, Mix_Music*> musicTable;

    static std::unordered_map<std::string, Mix_Chunk*> soundTable;

};