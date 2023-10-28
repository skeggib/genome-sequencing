#include "genome_sequencer.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <string>
#include <vector>

TEST_CASE("Sequences are concatenated") {
  // all sequences are concatenated in the result
  REQUIRE(find_shortest_genome({"AB", "CDE", "F"}) == "ABCDEF");
}

TEST_CASE("Overlap is squashed") {
  SECTION("one letter overlap") {
    REQUIRE(find_shortest_genome({"AB", "BC"}) == "ABC");
  }

  SECTION("multiple letters overlap") {
    REQUIRE(find_shortest_genome({"ABCDE", "CDEFGH"}) == "ABCDEFGH");
  }

  SECTION("entire sequence overlaps") {
    REQUIRE(find_shortest_genome({"ABCDE", "ABCDEFGH"}) == "ABCDEFGH");
    REQUIRE(find_shortest_genome({"ABCDE", "CDE"}) == "ABCDE");
  }

  SECTION("more than two sequences") {
    REQUIRE(find_shortest_genome({"ABCDE", "CDEFGH", "FGHIJKL"}) ==
            "ABCDEFGHIJKL");
  }
}

TEST_CASE("Sequence is flipped when it allows overlap") {
  SECTION("One letter overlap") {
    REQUIRE(find_shortest_genome({"AB", "CB"}) == "ABC");
  }
}

TEST_CASE("A longer flip is choosen if it makes the genome shorter") {
  REQUIRE(find_shortest_genome({"ABC", "GFEDCB", "FEDCBA"}) == "ABCGFEDCBA");
}

TEST_CASE("Isograd test cases") {
  // clang-format off
  std::vector<std::pair<std::vector<std::string>, std::string>> examples = {
    {{"ACGTT", "AGCTTG", "TAC"}, {"ACGTTCGATAC"}},
    {{"AATGTCATCGCAAA", "AATCCGGCGGATG", "TGTTCGA"}, {"AATGTCATCGCAAATCCGGCGGATGTTCGA"}},
    {{"CGCAAGGTTAAAGTTTC", "AGGACTTT", "AACTGCATAG"}, {"CGCAAGGTTAAAGTTTCAGGATACGTCAA"}},
    {{"GTCA", "CAGGGA", "CTTCAGG"}, {"GTCAGGGACTTC"}}
    // {{"CGACGTAAATAGG", "AGGGACACA", "CATACGATT", "ATGCTCTT", "TACTACATG", "ATGATGACTT", "CGTATT"}, {"CGACGTAAATAGGGACACATACGATTCTCGTACATCATGATGACTTATGC"}},
    // {{"GTTCTTCGGT", "GGTTAGTATA", "TAACGTCATTC", "ACCCTTACTCT", "CCAACGT", "GTTAGTGGGGGG", "GGGC"}, {"GTTCTTCGGTTAGTATAACGTCATTCTCATTCCCAACGTTAGTGGGGGGC"}},
    // {{"GATCG", "TATGC", "AGTCT", "ATGCTCAG", "TGAC"}, {"GATCGTATCTGATGCTCAGT"}},
    // {{"CAAGGTCCACTA", "CTGCCGCAAAGAAGC", "AGCTGCTTAGTG", "GCTAGGTAGC", "TAGCACGTCCGCTGCGC", "TGCGCGCTCATGAG", "TAAACGTAGGA", "CTATGCTAAAC", "GGAGTCGACACAGC", "GATGCGACAC"}, {"ATCACCTGGAACTGCCGCAAAGAAGCTGCTTAGTGCTAGGTAGCACGTCCGCTGCGCGCTCATGAGGATGCAAATCGTATCGGAGTCGACACAGCGTAG"}},
    // {{"AAAATATTCCGACCA", "AGTTTTTA", "TAAGACCATATTCCACA", "GAGCATACGAGATAAGAC", "TGTGGACCGAGAGCAT", "AGACGAGTGTGGA", "AGCAGAAGCACTAAG", "TAAGCAACACCACCA", "AACTTGCACTGACCA", "GTTCAAGT"}, {"ACCAGCCTTATAAAATTTTTGACACCTTATACCAGAATAGAGCATACGAGAGCCAGGTGTGAGCAGAAGCACTAAGCAACACCACCAGTCACGTTCAAGT"}},
    // {{"AGTCT", "ATGCTCAG", "TGAC", "GATCG", "TATGC", "AGTCT", "ATGCTCAG", "TGAC"}, {"TCTGATGCTCAGTGATCGTATCTGATGCTCAGT"}}
  };
  // clang-format on

  auto index = GENERATE(0, 1, 2, 3/*, 4, 5, 6, 7, 8, 9*/);
  auto example = examples[index];
  auto input = example.first;
  auto output = example.second;

  REQUIRE(find_shortest_genome(input) == output);
}

//                   ATGCTCAG TGAC
// GCTAG CGTAT TCTGA GACTCGTA CAGT
// GATCGTATCTGACTCGTATGAC
// GATCGTATCTGATGCTCAGT