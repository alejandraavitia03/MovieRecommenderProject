// ConsoleMovieRecommnder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <functional>
#include  "Strategy.h"
using namespace std;
enum Options
{
	EXIT,
	DISPLAY_DB,
	CHANGE_SORT_METHOD,
	ADD_MOVIE,
	ADD_GENRE,
	DELETE_MOVIE,
	DELETE_GENRE,
	RECOMMEND_BY_TOP_ACTOR,
	RECOMMEND_BY_DIRECTOR,
	RECOMMEND_BY_GENRE,
	RECOMMEND_BY_ALL_ACTORS,
	DISPLAY_ACTOR,

};
int menu(int* choice)
{

	cout << DISPLAY_DB << ". view movie database\n";
	cout << CHANGE_SORT_METHOD << ". change sort method\n";
	cout << ADD_MOVIE << ". Add movie to list\n";
	cout << ADD_GENRE << ". Add genre to list\n";
	cout << DELETE_MOVIE << ". Remove movie from list\n";
	cout << DELETE_GENRE << ". Remove genre from list\n";
	cout << RECOMMEND_BY_TOP_ACTOR << ". Recommend by top billed actors\n";
	cout << RECOMMEND_BY_DIRECTOR << ". recommend by director\n";
	cout << RECOMMEND_BY_GENRE << ". recommend by genre\n";
	cout << RECOMMEND_BY_ALL_ACTORS << ". recommend by all actors\n";
	cout << DISPLAY_ACTOR << ". recommend by movies actor played in\n";
	cout << EXIT << " EXIT\n";
	cout << "input choice number: ";
	cin >> *choice;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	return *choice;

}


class MovieDB
{

public:
	MovieDB(ifstream& file) 
	{
		if (!file.is_open())
		{
			std::cout << "ERROR: File Open" << '\n';
		}

		string moviename;
		string actor1;
		string actor2;
		string actor3;
		string genre;
		string description;
		string director;
		string year;
		string rating;
		string score;
		while (file.good())
		{
			getline(file, director, '\t');
			getline(file, actor1, '\t');
			getline(file, actor2, '\t');
			getline(file, moviename, '\t');
			getline(file, actor3, '\t');
			getline(file, rating, '\t');
			getline(file, year, '\t');
			getline(file, score, '\t');
			getline(file, genre, '\n');
			Entry e;
			e.title = moviename;
			e.director = director;
			e.actor1 = actor1;
			e.actor2 = actor2;
			e.actor3 = actor3;
			e.rating = rating;
			e.year = atoi(year.c_str());
			e.score = atoi(score.c_str());

			//add all the genres to the entry
			std::istringstream iss(genre);
			std::string token;
			while (std::getline(iss, token, '|'))
			{
				e.genre.insert(token);
			}
			//add the full entry to each database
			//Each genre for a given movie has an entry for the movie
			for (auto g : e.genre)
			{
				GenreDB[g].push_back(e);
			}
			TitleDB[moviename] = e;
			if (actor1.compare(""))
			{
				ActorDB[actor1].push_back(e);
			}
			if (actor2.compare(""))
			{
				ActorDB[actor2].push_back(e);
			}
			if (actor3.compare(""))
			{
				ActorDB[actor3].push_back(e);
			}
			DirectorDB[director].push_back(e);
		}

	}
	void DisplayEntry(Entry entry)
	{
		std::cout << "Name: " << entry.title << '\n';
		std::cout << "director: " << entry.director << '\n';
		std::cout << "actors: " << entry.actor1 << ", " << entry.actor2 << ", " << entry.actor3 << '\n';
		std::cout << "rating: " << entry.rating << '\n';
		std::cout << "year: " << entry.year << '\n';
		std::cout << "score: " << entry.score << '\n';
		std::cout << "genre: ";
		for (auto g : entry.genre)
		{
			std::cout << g << "|";
		}
		std::cout << "\n";
		std::cout << "-------------------" << '\n';
	}

	void DisplayDB()
	{
		for (auto movie : TitleDB)
		{
			string moviename = movie.first;
			Entry entry = movie.second;
			DisplayEntry(entry);
		}
	}
	//displays all the films in a genre using given sort function
	void DisplayGenre(std::string genre, std::function<bool(Entry, Entry)> sortFunc) 
	{
		std::vector<Entry> MoviesInGenre = GenreDB[genre];
		std::sort(MoviesInGenre.begin(), MoviesInGenre.end(), sortFunc);
		for (auto entry : MoviesInGenre) 
		{
			DisplayEntry(entry);
		}
	}
	//displays all the movies with an actor using given sort function
	void DisplayActor(std::string actor, std::function<bool(Entry, Entry)> sortFunc) 
	{
		std::vector<Entry> MoviesWithActor = ActorDB[actor];
		std::sort(MoviesWithActor.begin(), MoviesWithActor.end(), sortFunc);
		for (auto entry : MoviesWithActor) 
		{
			DisplayEntry(entry);
		}
	}
	//displays all the movies by a director using given sort function
	void DisplayDirector(std::string director, std::function<bool(Entry, Entry)> sortFunc)
	{
		std::vector<Entry> MoviesByDirector = DirectorDB[director];
		std::sort(MoviesByDirector.begin(), MoviesByDirector.end(), sortFunc);
		for (auto entry : MoviesByDirector)
		{
			DisplayEntry(entry);
		}
	}
	//private:
	std::map<string, Entry> TitleDB;
	std::map<string, vector<Entry>> ActorDB;
	std::map<string, vector<Entry>> DirectorDB;
	std::map<string, vector<Entry>> GenreDB;
};

class Recommender 
{
public:
	Recommender(MovieDB* mdb) : db(mdb)
	{
	}
	void AddMovie(const string title) 
	{
		MoviesLiked.insert(title);
	}
	void AddGenre(const string genre)
	{
		GenresLiked.insert(genre);
	}
	void DeleteMovie(const string title) 
	{
		MoviesLiked.erase(title);
	}
	void DeleteGenre(const string genre) 
	{
		GenresLiked.erase(genre);
	}
	//find movies that are all genres in GenresLiked
	void RecommendByGenres() 
	{
		std::vector<Entry> moviesRecommended;
		std::set<std::string> titles;
		for (auto movie : db->TitleDB)
		{
			bool containsAllGenres = true; //assume true until determined otherwise
			std::set<string> movieGenres = movie.second.genre;
			//If the movie has fewer total genres than the number of genres selected, we will exclude it.
			if (movieGenres.size() < GenresLiked.size())
			{
				continue;
			}
			//if all the genres are found in the movie's genre set, containsAllGenres will remain true
			for (auto genre : GenresLiked)
			{
				containsAllGenres = (movieGenres.find(genre) != movieGenres.end());
				if (containsAllGenres == false) 
				{
					break;
				}
			}
			//if the movie contains all the genres liked, we add it to the list
			if (containsAllGenres)
			{
				Entry e = movie.second;
				titles.insert(movie.first);
				if (titles.find(movie.first) != titles.end())
				{
					moviesRecommended.push_back(e);
				}
			}
		}
		DisplayVector(moviesRecommended);
	}
	void RecommendByDirector() 
	{
		std::vector<Entry> moviesRecommended;
		std::set<std::string> titles;
		for (auto movie : MoviesLiked)
		{
			std::string director = db->TitleDB[movie].director;
			std::vector<Entry> MoviesByDirector = db->DirectorDB[director];
			for (auto entry : MoviesByDirector)
			{
				titles.insert(movie);
				if (titles.find(movie) != titles.end()) 
				{
					moviesRecommended.push_back(entry);
				}
			}
		}
		DisplayVector(moviesRecommended);
	}
	void RecommendByTopActor() 
	{
		std::vector<Entry> moviesRecommended;
		std::set<std::string> titles;

		for (auto movie : MoviesLiked)
		{
			std::string actor1 = db->TitleDB[movie].actor1;
			std::vector<Entry> MoviesWithActor = db->ActorDB[actor1];
			for (auto entry : MoviesWithActor)
			{
				titles.insert(movie);
				if (titles.find(movie) != titles.end()) {
					moviesRecommended.push_back(entry);
				}
			}
		}
		DisplayVector(moviesRecommended);
	}
	void RecommendByAllActors()
	{
		std::vector<Entry> moviesRecommended;
		std::set<std::string> titles;
		for (auto movie : MoviesLiked)
		{
			std::string actor1 = db->TitleDB[movie].actor1;
			std::vector<Entry> MoviesWithActor = db->DirectorDB[actor1];
			for (auto entry : MoviesWithActor) 
			{
				titles.insert(movie);
				if (titles.find(movie) != titles.end())
				{
					moviesRecommended.push_back(entry);
				}
			}
			std::string actor2 = db->TitleDB[movie].actor2;
			MoviesWithActor = db->DirectorDB[actor2];
			for (auto entry : MoviesWithActor)
			{
				titles.insert(movie);
				if (titles.find(movie) != titles.end())
				{
					moviesRecommended.push_back(entry);
				}
			}
			std::string actor3 = db->TitleDB[movie].actor3;
			MoviesWithActor = db->DirectorDB[actor3];
			for (auto entry : MoviesWithActor) 
			{
				titles.insert(movie);
				if (titles.find(movie) != titles.end()) 
				{
					moviesRecommended.push_back(entry);
				}
			}
		}
		DisplayVector(moviesRecommended);
	}
	void DisplayVector(std::vector<Entry> movies) 
	{
		std::sort(movies.begin(), movies.end(), std::ref(*sortStrategy));
		for (auto movie : movies) 
		{
			db->DisplayEntry(movie);
		}
	}
	void DisplayGenre(std::string genre) 
	{
	   db->DisplayGenre(genre, std::ref(*sortStrategy));
	}
	void DisplayActor(std::string actor)
	{
	   db->DisplayActor(actor, std::ref(*sortStrategy));
	}
	void DisplayDirector(std::string director)
	{
		db->DisplayDirector(director, std::ref(*sortStrategy));
	}

	void changeStrategy(Strategy* strategy) {
		sortStrategy = strategy;
	}
private:
	Strategy* sortStrategy;
	MovieDB* db;
	std::set<string> MoviesLiked;
	std::set<string> GenresLiked;
};

int main()
{

	ifstream file("movie11.txt");
	int choice = 0;



	MovieDB db(file);
	Recommender r(&db);
	CompareByScoreAscending cbsa;
	CompareByScoreDescending cbsd;
	CompareByTitleAscending cbta;
	CompareByTitleDescending cbtd;
	CompareByYearAscending cbya;
	CompareByYearDescending cbyd; 

	r.changeStrategy(&cbsa);
	//r.setSortFunction(CompareByScoreDescending);
	//r.AddMovie("Mr. & Mrs. Smith");
	//r.AddMovie("Bad Boys II");
	//r.RecommendByTopActor();
	//r.AddGenre("Action");
	//r.AddGenre("Fantasy");
	//r.RecommendByGenres();


	//	r.DisplayGenre("Horror");

	do{
		menu(&choice);
		
			// display database choice
			if (choice == 1)
			{
				db.DisplayDB();


			}
			/*if (choice = 2)
			{
				string title;
				cin >> title;
				Entry entry = db.TitleDB[title];
				string actor1 = entry.actor1;
				string actor2 = entry.actor2;
				string actor3 = entry.actor3;
				db.DisplayActor(actor1, CompareByScoreDescending);

			}*/

			// top billed actor search choice
			if (choice == CHANGE_SORT_METHOD) {
				std::cout << "1. Title ascending\n";
				std::cout << "2. Title descending\n";
				std::cout << "3. Year ascending\n";
				std::cout << "4. Year descending\n";
				std::cout << "5. Score ascending\n";
				std::cout << "6. Score descending\n";
				std::cout << "sort method: ";
				int option;
				cin >> option;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (option == 1) {
					r.changeStrategy(&cbta);
					std::cout << "   Sorting by title ascending\n";
				}
				else if (option == 2) {
					r.changeStrategy(&cbtd);
					std::cout << "   Sorting by title descending\n";
				}
				else if (option == 3) {
					r.changeStrategy(&cbya);
					std::cout << "   Sorting by year ascending\n";
				}
				else if (option == 4) {
					r.changeStrategy(&cbyd);
					std::cout << "   Sorting by year descending\n";
				}
				else if (option == 5) {
					r.changeStrategy(&cbsa);
					std::cout << "   Sorting by score ascending\n";
				}
				else if (option == 6) {
					r.changeStrategy(&cbsd);
					std::cout << "   Sorting by score descending\n";
				}
			}else if (choice == ADD_MOVIE)
			{
				std::string title;
				std::cout << "movie title: ";
				getline(cin, title);
				r.AddMovie(title);
			}

			else if (choice == ADD_GENRE)
			{
				std::string genre;
				std::cout << "genre name: ";
				std::cin >> genre;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				r.AddGenre(genre);

			}
			else if (choice == DELETE_MOVIE)
			{
				std::string title;
				std::cout << "movie title: ";
				getline(cin, title);
				r.DeleteMovie(title);
			}
			else if (choice == DELETE_GENRE)
			{
				std::string genre;
				std::cout << "genre name: ";
				std::cin >> genre;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				r.DeleteGenre(genre);
			}
			else if (choice == RECOMMEND_BY_TOP_ACTOR)
			{
				r.RecommendByTopActor();
			}
			else if (choice == RECOMMEND_BY_DIRECTOR)
			{
				r.RecommendByDirector();
			}
			else if (choice == RECOMMEND_BY_GENRE)
			{
				r.RecommendByGenres();
			}
			else if (choice == RECOMMEND_BY_ALL_ACTORS)
			{
				r.RecommendByAllActors();
			}
			else if (choice == DISPLAY_ACTOR) {
				std::string actor;
				std::cout << "actor name: ";
				getline(cin, actor);
				
				r.DisplayActor(actor);
			}
			else if (choice == EXIT) {
				std::cout << "Goodbye!\n";
			}
			else {
				std::cout << "Unrecognized option\n";
			}
				

		}while (choice > 0);
	file.close();
}
