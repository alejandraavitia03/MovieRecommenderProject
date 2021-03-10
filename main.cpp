#include <iostream>
#include "MovieComponent.h"
#include "MovieGenres.h"
#include "Movie.h"
#include "MoviePlayer.h"


int main(int argc, const char * argv[]) {

    MovieComponent romanceMovies = new MovieGenres("Romance", "Love movies");
    
    std::cout << "Hello, World!\n";
    return 0;
}
