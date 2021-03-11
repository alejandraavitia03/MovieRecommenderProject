#ifndef MovieGenres_h
#define MovieGenres_h

#include "MovieComponent.h"
#include <iterator>

class MovieGenres : public MovieComponent{
private:
   
    vector<Movie*> movieList;
    vector<MovieGenres*> genreList;
    
public:
    MovieGenres() : MovieComponent() {};
    MovieGenres(vector<string> genres, string title) : MovieComponent(genres, title) {};
    
    string getTitle(){ return this->title; }
    vector<string>getGenres(){ return this->genre; }
    
    
    
    void addMovie(Movie* newMovie){
        this->movieList.push_back(newMovie);
    }
    void addGenre(MovieGenres *newGenre){
        this->genreList.push_back(newGenre);
    }
   
};
#endif /* MovieGenres_h */


