
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
