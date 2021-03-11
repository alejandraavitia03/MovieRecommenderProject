
#ifndef MovieComponent_h
#define MovieComponent_h

#include <vector>
#include <iomanip>
#include <string>
using namespace std;
//Movie:
//  Title, Actors, Rating, Director, Description
//This is my interface for every Movie (Leaf)
// and MovieGenres (composite) we make
class MovieComponent{

public:
    //Add a new MovieComponent
    virtual void addComponent(MovieComponent const &newMovieComponent) = 0;
    
    //Remove a MovieComponent
    virtual void removeMovieComponent(MovieComponent const &newMovieComponent) = 0;
    
    //Get component can't get to work
    //virtual MovieComponent const &getComponent(int componentIndex) = 0;

    virtual string getMovieTitle()= 0; //Will allow to get the Movie title
    virtual string getGenreNames() = 0; //Will allow to get the genre names
    virtual void displayInfo() = 0; //This will print specefic to the Movie or Genre
};

#endif /* MovieComponent_h */

