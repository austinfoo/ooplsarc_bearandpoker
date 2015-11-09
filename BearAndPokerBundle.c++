
#ifndef BearAndPoker_h
#define BearAndPoker_h

// --------
// includes
// --------

#include <iostream>
#include <string>
#include <vector>

// ------------
// bearandpoker_eval
// ------------

std::string bearandpoker_eval (const std::vector<uint32_t>&  bids);

// -------------
// bearandpoker_print
// -------------

void bearandpoker_print (std::ostream& w, const std::string& answer);

// -------------
// bearandpoker_solve
// -------------

void bearandpoker_solve (std::istream& r, std::ostream& w);

#endif

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



// ------------
// bearandpoker_eval
// ------------

std::string bearandpoker_eval (const std::vector<uint32_t>& bids)
{
  uint32_t common = 0;

  for (int i = 0; i < bids.size(); ++i)
  {
    uint32_t bid = bids[i];

    // Divide the bid down by 2 or 3 until we can't divide it anymore
    bool finished = false;
    while (!finished) {
      if ((bid % 2) == 0) {
	bid = bid / 2;
      } else if ((bid % 3) == 0) {
	bid = bid / 3;
      } else {
	finished = true;
      }
    }

    // If all the bids are not the same then we fail
    if (i == 0) {
      common = bid;
    } else if (bid != common) {
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
  std::vector<uint32_t> bids (num_bears);
  if (std::getline(r, s)) {
    std::istringstream sin(s);
    for (int i = 0; i < num_bears; ++i) {
      int bid = 0;
      sin >> bid;
      bids[i] = bid;
    }
  }

  // Determine the answer
  std::string answer = bearandpoker_eval(bids);

  // Print the result
  bearandpoker_print(w, answer);
}

#include <iostream>



// ----
// main
// ----

int main () {
    using namespace std;
    bearandpoker_solve(cin, cout);
    return 0;
}
