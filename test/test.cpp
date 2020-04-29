//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0.If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>
#include <stdio.h>
#include <iostream>
#include <chrono> 

#include "levenshtein.hpp"

int main(void) {

	std::string string1 = "Sitten";
	std::string string2 = "Kitten";

	int dist = levenshtein_distance(string1, string2);
	assert(dist == 1);


	string1 = "Sitting";
	string2 = "Kitten";

	dist = levenshtein_distance(string1, string2);
	assert(dist == 3);

	dist = levenshtein_distance(string2, string1);
	assert(dist == 3);


	string1 = "saturday";
	string2 = "sunday";

	dist = levenshtein_distance(string1, string2);
	assert(dist == 3);


	std::vector<std::string> vocabulary = load_words("test_vocabulary.txt");
	std::vector<std::string> word_list = load_words("test_words.txt");
	std::string output_file = "outputs.txt";

	auto start = std::chrono::high_resolution_clock::now();

	int iterations = 100;
	for (int i = 0; i < iterations; i++)
	{
		write_closest_to_file(output_file, word_list, vocabulary);
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << (float)duration.count() / (float)iterations << std::endl;

	// Performance test

	string1 = "jkdjalsdnfjklasnvjasntkj.fnsviulzdsngkjnsgnasdklnfjlsdvniursngiuasnvzfbkjgdsfnljfna";
	string2 = "klfnnfgnjkdfklsdlkjfsdjklzdsngkjnsgnasdklnfjsdnjknjdrknkvkueyuvn843niov9032r2";

	std::cout << "String lengths" << std::endl;
	std::cout << string1.size() << " " << string2.size() << std::endl;

	iterations = 100;

	start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < iterations; i++)
	{
		dist = levenshtein_distance(string1, string2);
	}

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << (float)duration.count() / (float)iterations << std::endl;



	return 0;

}