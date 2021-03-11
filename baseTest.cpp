//
//  baseTest.cpp
//  Composite_Final_Project
//
//  Created by Alejandra A on 3/11/21.
//
#include "gtest/gtest.h"
#include "Movie.h"
#include "MovieGenres.hpp"
#include "MovieComponent.hpp"

using namespace std;

TEST(BaseClassTests, TestMovieConstructor){
    string tempTitle = "Bee Movie";
  vector<string> castTemp = {"Jerry Seinfeld", "Renee Zellweger"};
    double tempReating = 8.0;
    string tempDirector = "Simon J. Smith";
  Movie* temp = new Movie(title_temp, castTemp, tempRating, tempDirector);
  EXPECT_TRUE(temp->getTitle() == tempTitle);
  EXPECT_TRUE(temp->getCast() == castTemp);
    EXPECT_TRUE(temp->getRating() == tempRating);
    EXPECT_TRUE(temp->getDirector() == tempDirector);

}
TEST(BaseClassTests, TestMovieSetTitle){
  Movie* temp = new Movie();
  temp->setTitle("the Bees movie");
  EXPECT_TRUE(temp->getTitle() == "the Bees movie");
}
