#pragma once

#include <Logger.h>
#include <SDL_Include.h>
#include <Util.h>

#include <unordered_map>
#include <memory>
#include <string>
#include <tuple>

class Resources {
    public:

        static std::shared_ptr<SDL_Texture> GetImage(std::string);

        static std::tuple<int, int> QueryImage(std::shared_ptr<SDL_Texture>);

        static void ClearImages();

        static Mix_Music* GetMusic(std::string);

        static void ClearMusics();

        static Mix_Chunk* GetSound(std::string);

        static void ClearSounds();

    private:

        static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;

        static std::unordered_map<std::string, Mix_Music*> musicTable;

        static std::unordered_map<std::string, Mix_Chunk*> soundTable;

};