#pragma once

#include <cstdio>
#include <unordered_map>
#include <utility>

namespace limadou {

const int N_PIXELS_X = 1024;
const int N_PIXELS_Y = 512;
const double PX_SIZE_X = 0.002924; // cm
const double PX_SIZE_Y = 0.002688; // cm

const int N_CHIPS_X = 5;
const int N_CHIPS_Y = 2;
const double CHIP_GAP_X = 0.0150; // cm
const double CHIP_GAP_Y = 0.0150; // cm

unsigned CHIP_IDS[N_CHIPS_X][N_CHIPS_Y] = {
    {0, 5}, {1, 6}, {2, 7}, {3, 8}, {4, 9}};
std::unordered_map<unsigned, std::pair<int, int>> CHIP_IDS_MAP = {
    {0, {0, 0}}, {5, {0, 1}}, {1, {1, 0}}, {6, {1, 1}}, {2, {2, 0}},
    {7, {2, 1}}, {3, {3, 0}}, {8, {3, 1}}, {4, {4, 0}}, {9, {4, 1}}};

const unsigned N_MODULES = 3;
double MODULE_POS_Z[3] = {0., 0.85, 1.7}; // cm
unsigned MODULE_IDS[3] = {0, 1, 2};
std::unordered_map<unsigned, unsigned> MODULE_IDS_MAP = {
    {0, 0}, {1, 1}, {2, 2}};

double SIZE_Z = 0.05; // cm

} // namespace limadou
