#include <Resources.h>
#include <Game.h>
#include <Logger.h>
#include <Util.h>

namespace penguin {

        std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;

        std::unordered_map<std::string, Mix_Music*> Resources::musicTable;

        std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

        SDL_Texture* Resources::GetImage(std::string file) {
            if (Resources::imageTable.find(file) == Resources::imageTable.end()) {
                Logger::Info("Loading image in path: " + file);

                auto g = Game::GetInstance();
                auto image = IMG_LoadTexture(g->GetRenderer(), file.c_str());
                
                if (image == nullptr) {
                    auto sdl_msg = IMG_GetError();
                    throw std::runtime_error(sdl_msg);
                }

                Resources::imageTable[file] = image;
            }

            return Resources::imageTable[file];
        }

        std::tuple<int, int> Resources::QueryImage (SDL_Texture* texture) {
            auto width = 0;
            auto height = 0;
            auto query = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

            if (query < 0) {
                auto sdl_msg = SDL_GetError();
                throw std::runtime_error(sdl_msg);
            }

            return std::make_tuple(width, height);
        }

        void Resources::ClearImages() {
            Logger::Info("Clearing images");

            for (auto &el : Resources::imageTable) {
                auto image = el.second;

                if (image != nullptr) {
                    SDL_DestroyTexture(image);
                    image = nullptr;
                }
            }

            Resources::imageTable.clear();
        }

        Mix_Music* Resources::GetMusic(std::string file) {
            if (Resources::musicTable.find(file) == Resources::musicTable.end()) {
                Logger::Info("Loading music in path: " + file);

                auto music = Mix_LoadMUS(file.c_str());

                if (music == nullptr) {
                    auto mix_msg = Mix_GetError();
                    throw std::runtime_error(mix_msg);
                }

                Resources::musicTable[file] = music;
            }

            return Resources::musicTable[file];
        }

        void Resources::ClearMusics() {
            Logger::Info("Clearing musics");

            for (auto &el : Resources::musicTable) {
                auto music = el.second;

                if (music != nullptr) {
                    Mix_FreeMusic(music);
                    music = nullptr;
                }
            }

            Resources::musicTable.clear();
        }

        Mix_Chunk* Resources::GetSound(std::string file) {
            if (Resources::soundTable.find(file) == Resources::soundTable.end()) {
                Logger::Info("Loading sound in path: " + file);

                auto sound = Mix_LoadWAV(file.c_str());

                if (sound == nullptr) {
                    auto mix_msg = Mix_GetError();
                    throw std::runtime_error(mix_msg);
                }

                Resources::soundTable[file] = sound;
            }

            return Resources::soundTable[file];
        }

        void Resources::ClearSounds() {
            Logger::Info("Clearing sounds");
            for (auto &el : Resources::soundTable) {
                auto sound = el.second;
                
                if (sound != nullptr) {
                    Mix_FreeChunk(sound);
                    sound = nullptr;
                }
            }

            Resources::soundTable.clear();
        }

}