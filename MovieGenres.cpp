
#ifndef MovieGenres_h
#define MovieGenres_h

#include "MovieComponent.h"
#include "Movie.h"
#include <iterator>
#include <algorithm>
#include <list>
class MovieGenres : public MovieComponent{
private:
   
    vector<MovieComponent> movieComponents;
    
    string genreName;
    
public:
    MovieGenres(string newGenreName){
        genreName = newGenreName;
    }
    
    string getGenreName(){ return genreName; }
    
    void addComponent(MovieComponent const &newMovieComponent){
        movieComponents.push_back(newMovieComponent);
    }
    
    void removeMovieComponent(MovieComponent const &newMovieComponent){
        vector<MovieComponent>::iterator it;
        it = find(movieComponents.begin(), movieComponents.end(),newMovieComponent);
        if(it != movieComponents.end()){
            movieComponents.erase(it);
        }
    }
    /*Not working
    MovieComponent const &getComponent(int componentIndex){
        return (MovieComponent)movieComponents.at(componentIndex);
    }*/
    
    void displayInfo(){
        cout << "Genre Name: " << setw(8) << getGenreName();
        //We want to cycle throulg and print any Movies or SubGenres to this Genre vector
        for(int i  = 0; movieComponents.size(); i++){
            movieComponents[i].displayInfo();
        }
    }
    
    
};
#endif /* MovieGenres_h */
