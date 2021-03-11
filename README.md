# FAN Spotlight 
 Our final project for CS 100 at UC Riverside. Our group is consisted of three team members and we collaborating together to design a movie library software. 
## Authors: 
 * Frances Isabelle Cristobal(https://github.com/frxncrxs)
 * Alejandra Avitia-Davila(https://github.com/alejandraavitia03)
 * Neda Karemi(https://github.com/nedurland)


## Project Description
  Our goal is to create a movie library/feed manager that allows users to have a feed with recommended movies based off genre and reviews. We will also be incorporating a library system which will allow them to keep track of movies they've watched and want to watch. Our software will allow users to leave ratings and reviews for others to see. We will be using an easy to use GI for our software.
### Why this is our choice:
 The reason we have chosen to create a movie library/feed software is because we are huge fans of films and are currently unsatisfied with different applications available to find movies based on ratings and genre. By creating this software we are hoping to make a much more user friendly and simple experience for ourselves and other movie fanatics who are having trouble picking a movie.
### How we will carry on:
* Language and Tools used:
	* C++ - The language we will be using.

* Input: 
	Like Pinterest or We Heart It, users will be prompted to give input:
	* Favorite:
		* Movies
		* TV Shows 
	* Personalized
		* Reviews 
		* Ratings
* Output: 
	With the given input we will return the user a customized feed for them and display other users reviews and ratings. 
* Design patterns we will be using:
	* Strategy Pattern: This design pattern was picked because it allow us to have something that does one thing and implement them in different ways. For example we have two interfaces, Sort and Recommend that will be called differently. Recommend will allow us to recommend by Genre, Director and Actors. The sorting algorithms will sort the recommended list by ratings and release date.

	* Composite Pattern: This design was chosed for its hierarchy structure. As we know many movies do not have only one single genre. We will hold the movies by their genres. Our interface MovieComponent will be inherited by the MovieGenre composite and will be used to make more components. In this hierarchy our lief is Movie and will not have any children.
		


## Class Diagram
Composite Pattern

![alt text](https://github.com/cs100/final-project-nkare001-aavit004-fcris002/blob/e152d15ffcb8df1e0f2364876f3e9bd9f7677bd9/UML's/FAN%20Spotlight-Composite%20Pattern%20.png)

Strategy Pattern

![alt text](https://github.com/cs100/final-project-nkare001-aavit004-fcris002/blob/e152d15ffcb8df1e0f2364876f3e9bd9f7677bd9/UML's/FAN%20Spotlight-Strategy%20Pattern.png)

Combined Patterns

![alt text](https://github.com/cs100/final-project-nkare001-aavit004-fcris002/blob/e152d15ffcb8df1e0f2364876f3e9bd9f7677bd9/UML's/FAN%20Spotlight-Combined%20Patterns.png)
Overall
![alt text](https://github.com/cs100/final-project-nkare001-aavit004-fcris002/blob/3df8d614f20d55343067f6b030f0f667bf8e86e6/UML's/FAN%20Spotlight-Overall.png)

 

 > ## Final deliverable
 > All group members will give a demo to the TA during lab time. The TA will check the demo and the project GitHub repository and ask a few questions to all the team members. 
 > Before the demo, you should do the following:
 > * Complete the sections below (i.e. Screenshots, Installation/Usage, Testing)

 
 ## Screenshots
 This will show a quick demo of someone who has openend the app. After that the chose to change the way our program sorts their output and chose to do it by descending rating. After they decide to add a movie, Fight Club, by which they will be receiving their recommendations. Once that movie is inserted they will chose to see their recommendation by Director and will get all they movies with the director of Fight Club, David Fincher. 
 **Welcome page:**
 
 ![alt text](https://github.com/cs100/final-project-nkare001-aavit004-fcris002/blob/master/Project_Screenshots/Screen%20Shot%202021-03-11%20at%201.28.14%20AM.png)
 
 **Sorting Input:**
 
 ![alt text](https://github.com/cs100/final-project-nkare001-aavit004-fcris002/blob/master/Project_Screenshots/Screen%20Shot%202021-03-11%20at%201.28.35%20AM.png)
 
 **Chose descending rating.**
 ![alt text](https://github.com/cs100/final-project-nkare001-aavit004-fcris002/blob/master/Project_Screenshots/Screen%20Shot%202021-03-11%20at%201.28.55%20AM.png)
 
 **Add movie: Fight Club**
 
 ![alt text](https://github.com/cs100/final-project-nkare001-aavit004-fcris002/blob/master/Project_Screenshots/Screen%20Shot%202021-03-11%20at%201.29.30%20AM.png)
 
 **Choosing Recommendation by Director**
 
 ![alt text](https://github.com/cs100/final-project-nkare001-aavit004-fcris002/blob/master/Project_Screenshots/Screen%20Shot%202021-03-11%20at%201.30.07%20AM.png)
 
 **Reccomendation with David Fincher:**
 
 ![alt text](https://github.com/cs100/final-project-nkare001-aavit004-fcris002/blob/master/Project_Screenshots/Screen%20Shot%202021-03-11%20at%201.30.27%20AM.png)
 
 
 ## Installation/Usage
 Our project user interface will be through the executable.
 Instructions on installing and running our application:
  * Download our code from the master branch
  * Open project on an IDE or text editor.
  * Run the program
  ### Usage
  * step 1: add a movie or genre
  * step 2: choose a sort method
  * step 3: click a recommend choice
> recommend by top billed actor
* how this works is that, whatever movie you have entered into your favorites, it will recommend movies based off the top billed actor in that movie
> Recommend by Director
* how this works is that whatever movie you have entered into your favorite, it will recommend movies based off that director
> Recommend by Genre
* how this works is that whatever movie or genre you have entered into your like list, it will recommend all the movies in that genre sorted by whichever sort you choose
> Recommend by Movies actor Played in
* how this works it will recommend movies based off whatever actor you have typed in. it will then sort and display all movies he or she has been featured in
> ## Testing
 > How was your project tested/validated? If you used CI, you should have a "build passing" badge in this README.
 
