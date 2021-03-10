#ifndef MovieGenres_h
#define MovieGenres_h

#include "MovieComponent.h"
#include <iterator>

class MovieGenres : public MovieComponent{
private:
   
    vector<*MovieComponent> MovieComponents;
    
    string genreName;
    string genreDescription;
public:
    MovieGenres(string newGenreName, string newGenreDescription){
        genreName = newGenreName;
        genreDescription = newGenreDescription;
    }
     string getGenreName(){ return genreName; }
    string getGenreDescription(){ return genreDescription; }
    
    void add(MovieComponent newMovieComponent){
        MovieComponents.push(newMovieComponent);
    }
    
    void remove(MovieComponent newMovieComponent){
        vector<MovieComponent>iterator iter = MovieComponents.bgein();
        while(iter != MovieComponents.end()){
            if(*iter == newMovieComponent)
                iter = MovieComponents.erase(iter);
            else
                iter++;
        }
    }
    
    MovieComponent getComponent(int componentIndex){
        return (MovieComponent)MovieComponents.get(componentIndex);
    }
    
    void displayMovieInfo(){
        cout << getMovieName() << " produced by " << getDirector << ", with a rating of: " << getMovieRating() << "." << endl;
        cout << "Decription of " << getMovieName() << ": " << getDescription() << endl;
        cout << "Actors: ";
        for(int i = 0; i < cast.size(); i++){
            cout << cast.at(i) << ", ";
        }
        cout << endl;
        
        
        Iterator movieIterator = MovieComponents.iterator();
        
        while(movieIterator.hasNext()){
            MovieComponent movieInfo = (MovieComponent)movieIterator.next();
            movieInfo.displayMovieInfo();
        }
    }
}

#endif /* MovieGenres_h */
