#ifndef Movie_h
#define Movie_h

#include "MovieComponent.h"

class Movie : public MovieComponent
{
protected:
    string description;
    vector<string> cast;
    double rating;
    string director;
    
public:
    Movie():MovieComponent(){};
    Movie(string title, vector<string> genres) : MovieComponent( genres, title) {};
    
    Movie(string newTitle, vector<string> newCast, double newRating, string newDirector,string newDescription, string newGenre){
        description = newDescription;
        cast = newCast;
        rating = newRating;
        director = newDirector;
    }
    
    
    string getTitle(){ return title; }
    vector<string> getCast() { return cast; }
    double getRating(){ return rating; }
    string getDirector(){ return director; }
    string getDescription(){ return description; }
    vector<string> getGenres(){ return genre;}
    
 
    void setTitle(string newTitle){
        title = newTitle;
    }
    void setCast(vector<string> newCast){
        cast = newCast;
    }
    void setRating(double newRating){
        rating = newRating;
    }
    void setDirector(string newDirector){
        director = newDirector;
    }
    void setDescription(string newDescription){
        description = newDescription;
    }
   void setGenres(vector<string> newGenres){
        genre = newGenres;
    }
    
    void displayMovieInfo(){
        
        cout << getTitle() << " produced by " << getDirector() << ", with a rating of: " << getRating() << "." << endl;
        cout << "Decription of " << getTitle() << ": " << getDescription() << endl;
        cout << "Actors: ";
        for(int i = 0; i < cast.size(); i++){
            cout << cast.at(i) << ", ";
        }
        cout << endl;
    }
    
};

#endif /* Movie_h */
