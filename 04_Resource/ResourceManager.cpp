#include "ResourceManager.h"
#include "../DxPlus/DxPlus.h"
#include "ResourceKeys.h"

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

void ResourceManager::LoadAll()
{
    LoadSprite(ResourceKeys::Sprite_TitleBG, L"TitleBG.png");
    LoadSprite(ResourceKeys::Sprite_GameOverBG, L"GameOverBG.png");
    LoadSprite(ResourceKeys::Sprite_GameClearBG, L"GameClearBG.png");
    LoadSprite(ResourceKeys::Sprite_TutorialPurpose, L"Tutorial_Purpose.png");
    LoadSprite(ResourceKeys::Sprite_TutorialTurret, L"Tutorial_Turret.png");
    LoadSprite(ResourceKeys::Sprite_Coin, L"Coin.png");
    LoadSprite(ResourceKeys::Sprite_TurretReleasePrice, L"TurretPrice.png");
    LoadSprite(ResourceKeys::Sprite_TurretUpgradePrice, L"TurretUpgrade.png");
    LoadFont(ResourceKeys::Font_ManufacturingConsent, L"./Data/Fonts/Manufacturing_Consent/ManufacturingConsent-Regular.ttf");
    LoadModel(ResourceKeys::Model_Stage, L"Stage.mv1");
    LoadModel(ResourceKeys::Model_Pistol, L"Pistol.mv1");
    LoadModel(ResourceKeys::Model_Rifle, L"Rifle.mv1");
    LoadModel(ResourceKeys::Model_Shotgun, L"Shotgun.mv1");
    LoadModel(ResourceKeys::Model_Turret, L"Turret.mv1");
    LoadModel(ResourceKeys::Model_BrokenTurret, L"BrokenTurret.mv1");
    LoadModel(ResourceKeys::Model_NotArrowTurret, L"NotArrowTurret.mv1");
    LoadModel(ResourceKeys::Model_Arrow, L"Arrow.mv1");
}

void ResourceManager::UnloadAll()
{
    UnloadGrids();
    UnloadFonts();
    UnloadModels();
    UnloadSprites();
}

// ===============================[  GRIDS  ]===================================

[[nodiscard]] const DxPlus::Sprite::SpriteBase* ResourceManager::GridAt(const std::wstring& key, int x, int y) const
{
    auto it = grids.find(key);
    if (it == grids.end()) return nullptr;
    const auto& g = it->second;
    if (x < 0 || x >= g.num.x || y < 0 || y >= g.num.y) return nullptr;
    int idx = y * g.num.x + x;
    return &g.frames[idx];
}

void ResourceManager::UnloadGrids()
{
    for (auto& kv : grids) {
        for (auto& f : kv.second.frames) {
            int gid = f.GetID();
            if (gid >= 0) DxPlus::Sprite::Delete(gid);
        }
    }
    grids.clear();
}

int ResourceManager::GetMusic(const std::wstring& key) const
{
    auto it = musics.find(key);
    return (it != musics.end()) ? it->second : -1;
}

int ResourceManager::GetSound(const std::wstring& key) const
{
    auto it = sounds.find(key);
    return (it != sounds.end()) ? it->second : -1;
}

int ResourceManager::GetModel(const std::wstring& key) const
{
    auto it = models.find(key);
    return (it != models.end()) ? it->second : -1;
}

int ResourceManager::GetSprite(const std::wstring& key) const
{
    auto it = sprites.find(key);
    return (it != sprites.end()) ? it->second : -1;
    return 0;
}

int ResourceManager::LoadMusic(const std::wstring& key, const std::wstring& path)
{
    int music = DxLib::LoadSoundMem(path.c_str());
    if (music == -1) DxPlus::Utils::FatalError((L"Failed to load music " + path).c_str());
    musics[key] = music;
    return music;
}


int ResourceManager::LoadSound(const std::wstring& key, const std::wstring& path)
{
    int sound = DxLib::LoadSoundMem(path.c_str());
    if (sound == -1) DxPlus::Utils::FatalError((L"Failed to load music " + path).c_str());
    sounds[key] = sound;
    return sound;
}

int ResourceManager::LoadModel(const std::wstring& key, const std::wstring& path)
{
    // 二重ロード防止（キャッシュ）
    if (auto it = models.find(key); it != models.end())
        return it->second;

    int h = DxLib::MV1LoadModel((L"./Data/Models/"+ path).c_str());
    if (h == -1) DxPlus::Utils::FatalError((L"Failed to load model " + path).c_str());

    models[key] = h;
    return h;
}

int ResourceManager::LoadSprite(const std::wstring& key, const std::wstring& path)
{
    if (auto it = sprites.find(key); it != sprites.end())
    return it->second;

    int s = DxPlus::Sprite::Load((L"./Data/Images/" + path).c_str());
    if (s == -1) DxPlus::Utils::FatalError((L"Failed to load model " + path).c_str());

    sprites[key] = s;
    return s;
}

void ResourceManager::UnloadMusics()
{
    for (auto& m : musics)
    {
        if (m.second >= 0) DxLib::DeleteSoundMem(m.second);
    }
    musics.clear();
}

void ResourceManager::UnloadSounds()
{
    for (auto& s : sounds)
    {
        if (s.second >= 0) DxLib::DeleteSoundMem(s.second);
    }
    sounds.clear();
}

void ResourceManager::UnloadModels()
{
    for (auto& m : models)
    {
        if (m.second >= 0) DxLib::MV1DeleteModel(m.second);
    }
    models.clear();
}

void ResourceManager::UnloadSprites()
{
    for (auto& s : sprites)
    {
        if (s.second >= 0) DxLib::DeleteGraph(s.second);
    }
}

// ===============================[  FONTS  ]===================================

int ResourceManager::GetFont(const std::wstring& fontName) const
{
    auto it = fonts.find(fontName);
    if (it == fonts.end())
    {
        DxPlus::Utils::FatalError((L"Font not found: " + fontName).c_str());
    }
    return it->second.handle;
}

int ResourceManager::LoadFont(const std::wstring& fontName, const std::wstring& path)
{
    if (AddFontResourceExW(path.c_str(), FR_PRIVATE, 0) == 0)
    {
        DxPlus::Utils::FatalError((std::wstring(L"Failed to add font: ") + path).c_str());
    }

    int handle = DxPlus::Text::InitializeFont(fontName.c_str(), 40, 2);
    if (handle == -1)
    {
        DxPlus::Utils::FatalError((std::wstring(L"Failed to init font: ") + fontName).c_str());
    }

    fonts[fontName] = { handle, path };

    return handle;
}

void ResourceManager::UnloadFont(const std::wstring& fontName)
{
    auto it = fonts.find(fontName);
    if (it == fonts.end()) return;

    auto& info = it->second;

    if (info.handle != -1)
    {
        DxPlus::Text::DeleteFont(info.handle);
        info.handle = -1;
    }

    if (!info.path.empty())
    {
        RemoveFontResourceExW(info.path.c_str(), FR_PRIVATE, 0);
    }

    fonts.erase(it);
}

void ResourceManager::UnloadFonts()
{
    std::vector<std::wstring> keys;
    keys.reserve(fonts.size());
    for (const auto& pair : fonts)// kv:key-value
    {
        keys.push_back(pair.first);
    }

    for (const auto& name : keys)
    {
        UnloadFont(name);
    }
}
