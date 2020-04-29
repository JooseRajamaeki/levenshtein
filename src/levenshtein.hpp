//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0.If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEVENSHTEIN_HPP
#define LEVENSHTEIN_HPP

#include <string>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

int levenshtein_distance(const std::string& string1, const std::string& string2);
std::vector<int> find_closest(const std::vector<std::string>& words, const std::vector<std::string>& vocabulary);

std::vector<std::string> load_words(const std::string& filename);
void write_closest_to_file(const std::string filename, const std::vector<std::string>& words, const std::vector<std::string>& vocabulary);

#endif
