//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0.If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "levenshtein.hpp"

int levenshtein_distance(const std::string& string1, const std::string& string2)
{
	const int len1 = string1.length();
	const int len2 = string2.length();

	std::vector<int> tmp(len2 + 1, 0);
	std::vector<std::vector<int>> distance(len1 + 1, tmp);

	for (int i = 1; i <= len1; i++)
	{
		distance[i][0] = i;
	}

	for (int j = 1; j <= len2; j++)
	{
		distance[0][j] = j;
	}

	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{


			int substitution_cost = 0;
			if (string1[i-1] != string2[j-1])
			{
				substitution_cost = 1;
			}

			int min_cost = distance[i - 1][j] + 1;
			min_cost = std::min(min_cost, distance[i][j - 1] + 1);
			min_cost = std::min(min_cost, distance[i - 1][j - 1] + substitution_cost);

			distance[i][j] = min_cost;

		}
	}
	
	return distance[len1][len2];
}

std::vector<int> find_closest(const std::vector<std::string>& words, const std::vector<std::string>& vocabulary)
{
	std::vector<int> idx_vocabulary(words.size(),-1);

	std::map<std::string, int> already_processed;

	const int words_len = words.size();
	const int vocabulary_len = vocabulary.size();

	#pragma omp parallel for
	for (int i = 0; i < words_len; i++)
	{
		int dist_closest = INT_MAX;
		int idx_closest = -1;

		#pragma omp critical
		{
			if (already_processed.count(words[i])) {
				idx_closest = already_processed[words[i]];
			}
		}

		if (idx_closest < 0)
		{
			for (int j = 0; j < vocabulary_len; j++)
			{
				int dist = levenshtein_distance(words[i], vocabulary[j]);
				if (dist < dist_closest)
				{
					dist_closest = dist;
					idx_closest = j;
				}
			}
		}

		#pragma omp critical
		{
			already_processed[words[i]] = idx_closest;
		}

		idx_vocabulary[i] = idx_closest;
	}

	return idx_vocabulary;
}

std::vector<std::string> load_words(const std::string & filename)
{

	std::vector<std::string> lines;

	std::string line;
	std::ifstream input_file(filename);
	for (std::string line; std::getline(input_file, line); )
	{
		lines.push_back(line);
	}

	return lines;
}

void write_closest_to_file(const std::string filename, const std::vector<std::string>& words, const std::vector<std::string>& vocabulary)
{

	std::vector<int> vocabulary_idxs = find_closest(words, vocabulary);

	std::ofstream output_file;
	output_file.open(filename);
	for (unsigned int i = 0; i < words.size(); i++)
	{
		output_file << words[i] << " " << vocabulary[vocabulary_idxs[i]] << std::endl;
	}
	output_file.close();
}
