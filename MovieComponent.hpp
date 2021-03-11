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
    vector<string> genre;
    string title;

public:
    
    MovieComponent(): genre(), title("") {};
    MovieComponent(vector<string> genre, string title) : genre(genre), title(title){};
    //Add a new MovieComponent

    //virtual void add(MovieComponent newMovieComponent) = 0;           
   
    //Remove a mediaComponent
    //virtual void remove(MovieComponent newMovieComponent) = 0;
                        
    //Get component
    //virtual MovieComponent getComponent(int componentIndex) = 0;
    virtual string getTitle()= 0;
    virtual void setTitle(string newTitle) = 0;
 
    virtual void displayMovieInfo() = 0;
};

#endif /* MovieComponent_h */

