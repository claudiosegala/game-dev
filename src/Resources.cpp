#include <SDL_Include.h>
#include <Resources.h>
#include <Game.h>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;

std::unordered_map<std::string, Mix_Music*> Resources::musicTable;

std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    if (Resources::imageTable.find(file) == Resources::imageTable.end()) {
        Logger::Info("Loading image in path: " + file);

        auto game = Game::GetInstance();
        auto renderer = game->GetRenderer();
        auto image = IMG_LoadTexture(renderer, file.c_str());
        
        if (image == nullptr) {
            auto sdl_msg = IMG_GetError();
            throw std::runtime_error(sdl_msg);
        }

        // TODO: why this works
        std::shared_ptr<SDL_Texture> image_ptr(image, [=](SDL_Texture* texture) { SDL_DestroyTexture(texture); });

        Resources::imageTable[file] = image_ptr;
    }

    return Resources::imageTable[file];
}

std::tuple<int, int> Resources::QueryImage (std::shared_ptr<SDL_Texture> texture) {
    auto width = 0;
    auto height = 0;
    auto query = SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);

    if (query < 0) {
        auto sdl_msg = SDL_GetError();
        throw std::runtime_error(sdl_msg);
    }

    return std::make_tuple(width, height);
}

// TODO: is this correct
void Resources::ClearImages() {
    Logger::Info("Pruning images");

    auto it = begin(Resources::imageTable);

    while (it != end(Resources::imageTable)) {
        if (it->second.unique()) {
            it = Resources::imageTable.erase(it);
        } else {
            ++it;
        }
    }
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