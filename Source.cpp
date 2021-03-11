

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

int menu(int* choice)
{

	cout << "1. view movie database" << endl;
	cout << "2. Recommend by top billed actors" << endl;
	cout << "3. recommend by genre" << endl;
	cout << "4. recommend by director" << endl;
	cout << "5. recommend by movies actor played in" << endl;

	cout << "input choice number: ";
	cin >> *choice;
	return *choice;

}
struct Entry {
	string title;
	string director;
	string actor1;
	string actor2;
	string actor3;
	set<string> genre;
	string rating;
	int year;
	int score;
};
bool CompareByScoreAscending(Entry e1, Entry e2) {
	return e1.score < e2.score;
}
bool CompareByScoreDescending(Entry e1, Entry e2) {
	return e1.score > e2.score;
}
bool CompareByYearAscending(Entry e1, Entry e2) {
	return e1.year < e2.year;
}
bool CompareByYearDescending(Entry e1, Entry e2) {
	return e1.score > e2.score;
}
bool CompareByTitleAscending(Entry e1, Entry e2) {
	return e1.title < e2.title;
}
bool CompareByTitleDescending(Entry e1, Entry e2) {
	return e1.title > e2.title;
}
enum SORT_MODE {
	YEAR_ASCENDING,
	YEAR_DESCENDING,
	SCORE_ASCENDING,
	SCORE_DESCENDING,
	TITLE_ASCENDING,
	TITLE_DESCENDING
};
class MovieDB {

public:
	MovieDB(ifstream& file) {
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
			for (auto g : e.genre) {
				GenreDB[g].push_back(e);
			}
			TitleDB[moviename] = e;
			if (actor1.compare("")) {
				ActorDB[actor1].push_back(e);
			}
			if (actor2.compare("")) {
				ActorDB[actor2].push_back(e);
			}
			if (actor3.compare("")) {
				ActorDB[actor3].push_back(e);
			}
			DirectorDB[director].push_back(e);
		}

	}
	void DisplayEntry(Entry entry) {
		std::cout << "Name: " << entry.title << '\n';
		std::cout << "director: " << entry.director << '\n';
		std::cout << "actors: " << entry.actor1 << ", " << entry.actor2 << ", " << entry.actor3 << '\n';
		std::cout << "rating: " << entry.rating << '\n';
		std::cout << "year: " << entry.year << '\n';
		std::cout << "score: " << entry.score << '\n';
		std::cout << "genre: ";
		for (auto g : entry.genre) {
			std::cout << g << "|";
		}
		std::cout << "\n";
		std::cout << "-------------------" << '\n';
	}

	void DisplayDB() {
		for (auto movie : TitleDB)
		{
			string moviename = movie.first;
			Entry entry = movie.second;
			DisplayEntry(entry);
		}
	}
	//displays all the films in a genre using given sort function
	void DisplayGenre(std::string genre, std::function<bool(Entry, Entry)> sortFunc) {
		std::vector<Entry> MoviesInGenre = GenreDB[genre];
		std::sort(MoviesInGenre.begin(), MoviesInGenre.end(), sortFunc);
		for (auto entry : MoviesInGenre) {
			DisplayEntry(entry);
		}
	}
	//displays all the movies with an actor using given sort function
	void DisplayActor(std::string actor, std::function<bool(Entry, Entry)> sortFunc) {
		std::vector<Entry> MoviesWithActor = ActorDB[actor];
		std::sort(MoviesWithActor.begin(), MoviesWithActor.end(), sortFunc);
		for (auto entry : MoviesWithActor) {
			DisplayEntry(entry);
		}
	}
	//displays all the movies by a director using given sort function
	void DisplayDirector(std::string director, std::function<bool(Entry, Entry)> sortFunc) {
		std::vector<Entry> MoviesByDirector = DirectorDB[director];
		std::sort(MoviesByDirector.begin(), MoviesByDirector.end(), sortFunc);
		for (auto entry : MoviesByDirector) {
			DisplayEntry(entry);
		}
	}
	//private:
	std::map<string, Entry> TitleDB;
	std::map<string, vector<Entry>> ActorDB;
	std::map<string, vector<Entry>> DirectorDB;
	std::map<string, vector<Entry>> GenreDB;
};

class Recommender {
public:
	Recommender(MovieDB* mdb) : db(mdb) {
		sortFunction = CompareByTitleAscending;
	}
	void AddMovie(const string title) {
		MoviesLiked.insert(title);
	}
	void AddGenre(const string genre) {
		GenresLiked.insert(genre);
	}
	void DeleteMovie(const string title) {
		MoviesLiked.erase(title);
	}
	void DeleteGenre(const string genre) {
		GenresLiked.erase(genre);
	}
	//find movies that are all genres in GenresLiked
	void RecommendByGenres() {
		std::vector<Entry> moviesRecommended;
		std::set<std::string> titles;
		for (auto movie : db->TitleDB) {
			bool containsAllGenres = true; //assume true until determined otherwise
			std::set<string> movieGenres = movie.second.genre;
			//If the movie has fewer total genres than the number of genres selected, we will exclude it.
			if (movieGenres.size() < GenresLiked.size()) {
				continue;
			}
			//if all the genres are found in the movie's genre set, containsAllGenres will remain true
			for (auto genre : GenresLiked) {
				containsAllGenres = (movieGenres.find(genre) != movieGenres.end());
				if (containsAllGenres == false) {
					break;
				}
			}
			//if the movie contains all the genres liked, we add it to the list
			if (containsAllGenres) {
				Entry e = movie.second;
				titles.insert(movie.first);
				if (titles.find(movie.first) != titles.end()) {
					moviesRecommended.push_back(e);
				}
			}
		}
		DisplayVector(moviesRecommended);
	}
	void RecommendByDirector() {
		std::vector<Entry> moviesRecommended;
		std::set<std::string> titles;
		for (auto movie : MoviesLiked) {
			std::string director = db->TitleDB[movie].director;
			std::vector<Entry> MoviesByDirector = db->DirectorDB[director];
			for (auto entry : MoviesByDirector) {
				titles.insert(movie);
				if (titles.find(movie) != titles.end()) {
					moviesRecommended.push_back(entry);
				}
			}
		}
		DisplayVector(moviesRecommended);
	}
	void RecommendByTopActor() {
		std::vector<Entry> moviesRecommended;
		std::set<std::string> titles;

		for (auto movie : MoviesLiked) {
			std::string actor1 = db->TitleDB[movie].actor1;
			std::vector<Entry> MoviesWithActor = db->ActorDB[actor1];
			for (auto entry : MoviesWithActor) {
				titles.insert(movie);
				if (titles.find(movie) != titles.end()) {
					moviesRecommended.push_back(entry);
				}
			}
		}
		DisplayVector(moviesRecommended);
	}
	void RecommendByAllActors() {
		std::vector<Entry> moviesRecommended;
		std::set<std::string> titles;
		for (auto movie : MoviesLiked) {
			std::string actor1 = db->TitleDB[movie].actor1;
			std::vector<Entry> MoviesWithActor = db->DirectorDB[actor1];
			for (auto entry : MoviesWithActor) {
				titles.insert(movie);
				if (titles.find(movie) != titles.end()) {
					moviesRecommended.push_back(entry);
				}
			}
			std::string actor2 = db->TitleDB[movie].actor2;
			MoviesWithActor = db->DirectorDB[actor2];
			for (auto entry : MoviesWithActor) {
				titles.insert(movie);
				if (titles.find(movie) != titles.end()) {
					moviesRecommended.push_back(entry);
				}
			}
			std::string actor3 = db->TitleDB[movie].actor3;
			MoviesWithActor = db->DirectorDB[actor3];
			for (auto entry : MoviesWithActor) {
				titles.insert(movie);
				if (titles.find(movie) != titles.end()) {
					moviesRecommended.push_back(entry);
				}
			}
		}
		DisplayVector(moviesRecommended);
	}
	void DisplayVector(std::vector<Entry> movies) {
		std::sort(movies.begin(), movies.end(), sortFunction);
		for (auto movie : movies) {
			db->DisplayEntry(movie);
		}
	}
	void setSortFunction(std::function<bool(Entry, Entry)> sortFunc) {
		sortFunction = sortFunc;
	}
	void DisplayGenre(std::string genre) {
		db->DisplayGenre(genre, sortFunction);
	}
	void DisplayActor(std::string actor) {
		db->DisplayActor(actor, sortFunction);
	}
	void DisplayDirector(std::string director) {
		db->DisplayDirector(director, sortFunction);
	}
private:
	MovieDB* db;
	std::set<string> MoviesLiked;
	std::set<string> GenresLiked;
	std::function<bool(Entry, Entry)> sortFunction;
};
enum Options {
	EXIT,
	DISPLAY_DB,
	CHANGE_SORT_MODE,
	DISPLAY_ACTOR,

};

int main() {

	ifstream file("movie11.txt");
	int choice = 0;



	MovieDB db(file);
	Recommender r(&db);
	//r.setSortFunction(CompareByScoreDescending);
	//r.AddMovie("Mr. & Mrs. Smith");
	//r.AddMovie("Bad Boys II");
	//r.RecommendByTopActor();
	//r.AddGenre("Action");
	//r.AddGenre("Fantasy");
	//r.RecommendByGenres();


	//	r.DisplayGenre("Horror");

	
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
		if (choice == 2)
		{
			string movname1, movname2;
			char input;
			
			cout << "a. 1 movie input" << endl;
			cout << "b. 2 movie inputs" << endl;
			cin >> input;
			if (input == 'a')
			{
				cout << "enter movie title: ";
				cin.ignore();
				getline(cin, movname1);
				r.setSortFunction(CompareByScoreDescending);
				r.AddMovie(movname1);
				r.RecommendByTopActor();
			}
			else if (input == 'b')
			{
				cout << "enter movie title 1: ";
				cin.ignore();
				getline(cin, movname1);
				cout << "enter movie title 2: ";
				cin.ignore();
				getline(cin, movname2);
				system("cls");
				r.setSortFunction(CompareByScoreDescending);
				r.AddMovie(movname1);
				r.AddMovie(movname2);
				r.RecommendByTopActor(); // recommends by top billed actor in that movie title
			}
		}

		else if (choice == 3)
		{
			string genre1;
			string genre2;
			char genrenum;
			cout << "a. input 1 genre" << endl;
			cout << "b. input 2 genres" << endl;
			cin >> genrenum;
			system("cls");

			// if user chooses 1 genre input
			if (genrenum == 'a')
			{
				cout << "enter genre 1: ";

				cin >> genre1;
				system("cls");

				r.setSortFunction(CompareByScoreDescending); //sorts by rating
				r.AddGenre(genre1); // sends user entry too add genre
				r.RecommendByGenres(); // displays recommends user entry
			}
			else if (genrenum == 'b')
			{
				cout << "enter genre 1: ";
				cin >> genre1;
				cout << "enter genre 2: ";
				cin >> genre2;
				system("cls");
				
				r.setSortFunction(CompareByScoreDescending); //sorts by rating
				r.AddGenre(genre1); // sends user entry too add genre
				r.AddGenre(genre2); // sends user entry too add genre
				r.RecommendByGenres(); // displays recommends user entry
			}
		}

		else if (choice == 4)
		{
			string dirname;
			cout << "enter director name: ";
			cin.ignore();
			getline(cin, dirname);
			r.DisplayDirector(dirname);
		}
		
		else if (choice == 5)
		{
			string actorname;
			cout << "enter actor name: ";
			cin.ignore();
			getline(cin, actorname);
			r.DisplayActor(actorname);
			r.RecommendByAllActors();
		}



	file.close();
}
