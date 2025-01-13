#pragma once

#include <string>

struct PigData {
    char symbol;    // Single character representing this position
    std::string longname;   // Longer description of this position
    double probability;     // Probability of this position being rolled
};