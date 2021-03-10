//  MoviePlayer.h
//  //  Composite_Final_Project
//  //
//  //  Created by Alejandra A on 2/28/21.
//  //



#ifndef MoviePlayer_h
#define MoviePlayer_h

#include "MovieComponent.hpp"

class MoviePlayer{
    MovieComponent movieList;
    
    MoviePlayer(MovieComponent newMovieList){
        movieList = newMovieList;
    }
    // This will call the display function from out interface on every movie or moviegrenre stored in our movielist
    void getMovieList(){
        movieList.displayMovieInfo();
    }
}

#endif /* MoviePlayer_h */

