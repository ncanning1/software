#pragma once

#include <vector>
#include "texture.h"
#include "audio.h"

void archiveReader(std::vector<Texture> &texture, std::vector<int> &getFiles, Overhead &overhead);

void archiveReader(std::vector<Audio> &audio, std::vector<int> &getFiles, Overhead &overhead, std::vector<bool> &isChunk);