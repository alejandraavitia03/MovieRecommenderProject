#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int menu(int *choice)
{

	cout << "1. view movie database" << endl;
	cin >> *choice;
	return *choice;
	
}

int main() {

	ifstream file("movie11.csv");
	int choice = 0;

	menu(&choice);

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



	
	
		while (file.good() && choice==1)
		{

			getline(file, director, ',');
			getline(file, actor1, ',');
			getline(file, actor2, ',');
			getline(file, moviename, ',');
			getline(file, actor3, ',');
			getline(file, rating, ',');
			getline(file, year, ',');
			getline(file, score, ',');
			getline(file, genre, '\n');



			std::cout << "Name: " << moviename << '\n';
			std::cout << "director: " << director << '\n';
			std::cout << "actors: " << actor1 << ", " << actor2 << ", " << actor3 << endl;

			std::cout << "rating: " << rating << '\n';
			std::cout << "year: " << year << '\n';
			std::cout << "score: " << score << '\n';
			std::cout << "genre: " << genre << '\n';
			std::cout << "-------------------" << '\n';
		}
	

	file.close();
}