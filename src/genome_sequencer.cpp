#include "genome_sequencer.hpp"

/**
 * @brief remove the overlapping characters from the second sequence
 */
std::string remove_overlap(const std::string &lhs, const std::string &rhs) {
  for (auto it = std::begin(lhs); it != std::end(lhs); ++it) {
    if (std::equal(it, std::end(lhs), std::begin(rhs))) {

      return rhs.substr(std::end(lhs) - it, rhs.size() - (std::end(lhs) - it));
    }
  }

  return rhs;
}

std::string reverse(const std::string &str) { return std::string{std::rbegin(str), std::rend(str)}; }

/**
 * @brief concatenate two sequences removing the overlapping characters
 */
std::string squash(const std::string &lhs, const std::string &rhs) { return lhs + remove_overlap(lhs, rhs); }

/**
 * @brief reverse and squash the remaining sequences without touching the first one to find the shortest genome that could have produced the sequences
*/
std::string find_shortest_genome(const std::string &first_sequence, const std::vector<std::string> &remaining_sequences) {
  const auto &second_sequence = remaining_sequences[0];
  auto third_sequence_and_after = std::vector<std::string>{std::begin(remaining_sequences) + 1, std::end(remaining_sequences)};

  if (third_sequence_and_after.size() > 0) {
    auto original_order_result = squash(first_sequence, find_shortest_genome(second_sequence, third_sequence_and_after));
    auto reversed_order_result = squash(first_sequence, find_shortest_genome(reverse(second_sequence), third_sequence_and_after));
    return original_order_result.size() <= reversed_order_result.size() ? original_order_result : reversed_order_result;
  } else {
    auto original_order_result = squash(first_sequence, second_sequence);
    auto reversed_order_result = squash(first_sequence, reverse(second_sequence));
    return original_order_result.size() <= reversed_order_result.size() ? original_order_result : reversed_order_result;
  }
}

/**
 * @brief reverse and squash sequences to find the shortest genome that could have produced the sequences
*/
std::string find_shortest_genome(const std::vector<std::string> &input) {
  if (input.size() == 1) {
    return input[0];
  }

  const auto &first_sequence = input[0];
  auto remaining_sequences = std::vector<std::string>{std::begin(input) + 1, std::end(input)};

  auto original_order_result = find_shortest_genome(first_sequence, remaining_sequences);
  auto reversed_order_result = find_shortest_genome(reverse(first_sequence), remaining_sequences);
  return original_order_result.size() <= reversed_order_result.size() ? original_order_result : reversed_order_result;
}
