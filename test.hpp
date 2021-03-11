#ifndef __TEST_HPP
#define __TEST_HPP

#include "gtest/gtest.h"
#include "action.h"
#include <sstream>
#include <iostream>

static ostringstream os;
static MovieDB movie;

TEST(DISPLAY_ENTRY, CONTAINS_ALL){
  getline("movie11.txt", "Peter Scolari", '\t');
  getline("movie11.txt", "Robert Zemeckis", '\t');
  getline("movie11.txt", "Eddie Deezen", '\t');
  getline("movie11.txt", "The Polar Express", '\t');
  getline("movie11.txt", "Tom Hanks", '\t');
  getline("movie11.txt", "PG", '\t');
  getline("movie11.txt", "2004", '\t');
  getline("movie11.txt", "6.6", '\t');
  getline("movie11.txt", "Adventure|Animation|Family|Fantasy", '\n');
}

#endif
