
// ----------------------------
// projects/twobuttons/Twobuttons.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <list>
#include <limits>

#include "BearAndPoker.h"

// ------------
// bearandpoker_eval
// ------------

std::string bearandpoker_eval (std::vector<uint64_t>& bids)
{
  for (int i = 0; i < bids.size(); ++i)
  {
    // Divide the bid down by 2 or 3 until we can't divide it anymore
    bool finished = false;
    while (!finished) {
      if ((bids[i] % 2) == 0) {
	bids[i] = bids[i] / 2;
      } else if ((bids[i] % 3) == 0) {
	bids[i] = bids[i] / 3;
      } else {
	finished = true;
      }
    }

    // If all the bids are not the same then we fail
    if (bids[i] != bids[0]) {
      return "No";
    }
  }

  // Otherwise we succeed
  return "Yes";
}

// -------------
// bearandpoker_print
// -------------

void bearandpoker_print (std::ostream& w, const std::string& answer)
{
  w << answer << std::endl;
}

// -------------
// bearandpoker_solve
// -------------

void bearandpoker_solve (std::istream& r, std::ostream& w) 
{
  std::string s;

  // Get the number of bears
  int num_bears = 0;
  if (std::getline(r, s)) {
    std::istringstream sin(s);
    sin >> num_bears;
  }

  // Get the initial bids
  std::vector<uint64_t> bids;
  if (std::getline(r, s)) {
    std::istringstream sin(s);
    for (int i = 0; i < num_bears; ++i) {
      int bid = 0;
      sin >> bid;
      bids.emplace_back(bid);
    }
  }

  // Determine the answer
  std::string answer = bearandpoker_eval(bids);

  // Print the result
  bearandpoker_print(w, answer);
}
