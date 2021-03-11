
#ifndef Movie_h
#define Movie_h

#include "MovieComponent.h"

class Movie : public MovieComponent
{
private:
    string title;
    vector<string> cast;
    double rating;
    string director;
    
public:
    
    Movie(string newTitle, vector<string> newCast, double newRating, string newDirector){
        title = newTitle;
        cast = newCast;
        rating = newRating;
        director = newDirector;
    }
    
    
    string getTitle(){ return title; }
    vector<string> getCast() { return cast; }
    double getRating(){ return rating; }
    string getDirector(){ return director; }

    
    
    void displayInfo(){
        
        cout << "Movie Title: " << setw(8) << getTitle() << endl;
        cout << "Directed by: " << setw(8) << getDirector() <<  endl;
        cout << "Rating of  : " << setw(8) << getRating() << endl;
        cout << "Actors     : " << setw(8);
        for(int i = 0; i < cast.size(); i++){
            cout << cast.at(i) << ", ";
        }
        cout << endl;
    }
    
};

#endif /* Movie_h */
