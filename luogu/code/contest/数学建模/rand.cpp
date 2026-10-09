//
// Created by k on 24-9-8.
//

#include "rand.h"

std::random_device rdv;
std::mt19937 mt{ rdv() };