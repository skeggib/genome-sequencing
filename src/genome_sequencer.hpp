#pragma once

#include <string>
#include <vector>

/**
 * @brief find the shortest dna genome mathing the provided dna sequences
 *
 * when sequencing dna, the first step is to cut it into smaller parts before
 * passing them to the sequencer. each sequence can overlap its neighbor and can
 * be flipped. for example, the genome ACGTTCGACAT could be sequenced as [ACGTT,
 * GTTCGA, TAC], notice that ACGTT and GTTCGA overlap (GTT) and CAT has been
 * flipped into TAC. this function takes the dna sequences produced by the
 * sequencer and finds the shortest genome that could have produces them.
 */
std::string find_shortest_genome(const std::vector<std::string> &input);
