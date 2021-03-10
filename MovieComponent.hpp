//
//  MovieComponent.h
//  Composite_Final_Project
//
//  Created by Alejandra A on 3/9/21.
//
//Movie:
//  Title, Actors, Rating, Director, Description
//	This is my interface for every Movie (Leaf)
// and MovieGenres (composite) we make


#ifndef MovieComponent_h
#define MovieComponent_h

#include <vector>
#include <string>
using namespace std;

class MovieComponent{
protected:
    string genre;
    string description;
public:
    virtual ~MovieComponent() = default;
    MovieComponent(): genre(""), description("") {};
    MovieComponent(string genre, string description) : genre(genre), description(description){};
    //Pure Virutal Functions
  
    //Add a new MovieComponent
    //virtual void add(MovieComponent newMovieComponent) = 0;           
   
    //Remove a mediaComponent
    //virtual void remove(MovieComponent newMovieComponent) = 0;
                        
    //Get component
    //virtual MovieComponent getComponent(int componentIndex) = 0;

    //Get a Movie name
    virtual string getMovieName() = 0;

    //Get cast
    virtual string getActorName() = 0;

    //Get rating
    virtual double getMovieRating() = 0;

    //Get director
    virtual string getDirector() = 0;

    //Get Description
    virtual string getDescription()= 0;

    //Display
    virtual void displayMovieInfo() = 0;
};

#endif /* MovieComponent_hpp */
