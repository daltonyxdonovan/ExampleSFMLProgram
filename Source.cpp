//include our libraries that we need for the program to run.
//NOTE: you need to make sure you have SFML linked to your program
//On *nix that normally means compiling in the command line with the -lsfml-system.lib,-lsfml-****.lib, etc
//on windows/visual studio/visual studio code, you can set it up to just do it automatically when you press F5, look into it.
//it is a major time saver

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


/*lets break down what a vector is-
a vector is a row of containers. the simplest container you could have. imagine a row of cardboard boxes vvv

 ----  ----  ----
 |1 |  |2 |  |3 |      <-- example of std::vector<int>
 ----  ----  ----

 this is a 1D row of boxes. we have shoved an integer into each of them. this is simply a std::vector<int> 
 (std is the c++ std library, always exists)
 a vector2 is a custom vector that is included in SFML, it can hold _two_ integers. crazy, right?


 -----  -----  -----
 |1,2|  |2,4|  |3,6|	<--- example of std::vector<sf::Vector2> (a vector of Vector2's) 
 -----  -----  -----

 another way we could imagine this is a grid. I know that sounds weird, but stick with me here- each Vector2f has 2 values right?

 ----	 ----	 ----
 |1 |	 |2 |	 |3 |      <-- each Vector2 is a group of 2 numbers
 ----	 ----	 ----
 |2 |	 |4 |	 |6 |      
 ----	 ----	 ----

 we can use this very handy custom vector for things like a 2d position, in fact it was made for that!
 and to boot, you can access the ints inside with .x and .y 

 so say we are accessing boxes[0] up there in the second example. (since indexing starts at 0 in sane languages, 0 is the first)
 if we wanted to change only the horizontal position of that box, it would be 
 boxes[0].x = 2;

 -----  -----  -----
 |2,2|  |2,4|  |3,6|
 -----  -----  -----

 boxes[0].y = 4;

 -----  -----  -----
 |2,4|  |2,4|  |3,6|
 -----  -----  -----

*/





//variables
const int width{ 800 }; //width of window object we want
const int height{ 800 }; // height of such

std::vector<sf::Vector2f> boxes; // <-- create a vector of Vector2f where each box in the vector contains a vector2f with 2 numbers
//you can't add stuff to it until in main(), but you can create it here. in fact, you WANT to, so you don't overload the heap.
// stack vs heap is a topic for another day

//here we will create a square just for shits
sf::RectangleShape shape(sf::Vector2f(50,50));
//okay, let's break this down here. i know it's a lot-


/*


sf::                                          <-- we are accessing the sf namespace, {SFML as a whole}
sf::RectangleShape                            <-- we are calling an instance of the RectangleShape class from the sf namespace
sf::RectangleShape shape                      <-- we are naming the object we are creating from RectangleShape the name 'shape'
sf::RectangleShape shape(sf::Vector2f(50,50)) <-- we are creating a Vector2f (same as a vector2 but contains floats, not ints) with size 50,50 (width, height)

		now that we have successfully created a RectangleShape object named shape, we can access it's properties. let's head down to main()
*/


int main()
{
	//here we will set up our shape object and actually populate our vector to give an example.
	boxes.push_back(sf::Vector2f(200,200)); // we set the boxes[0] to 200,200 to use as a position for our shape

	shape.setFillColor(sf::Color::Red); //set the color of the shape to red
	shape.setPosition(boxes[0]); //set the position of the shape to boxes[0], which is 200,200


	//now let's do the fun stuff!






	//set up window
	sf::RenderWindow window(sf::VideoMode(width, height), "exampleProgram"); //create an object named window, set it to VideoMode(resolution), name it
	sf::Event event; //create our event object to have access to inputs
	
	while (window.isOpen()) //while the window object is not closed, do-
	{
		while (window.pollEvent(event)) //while the window object is open, scan event every frame
										//note: it is _not_ normal to do a while loop inside another, it normally causes infloops.
										//		this is just how SFML does it /shrug
		{
			if (event.type == sf::Event::Closed) //event closed is called by anything that would close the program, {altF4,Xbutton}
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();

				if (event.key.code == sf::Keyboard::Right)
					boxes[0].x += 10; // x is horizontal , so we are adding 10 to the horizontal position of boxes[0]

				if (event.key.code == sf::Keyboard::Left)
					boxes[0].x -= 10;

				if (event.key.code == sf::Keyboard::Up)
					boxes[0].y -= 10; // y is vertical, so we are subtracting 10 from the vertical position of boxes[0]

				if (event.key.code == sf::Keyboard::Down)
					boxes[0].y += 10;
			}
		}

		window.clear(); //every single frame we need to wipe the screen from the last frame. by default, with no arguments,
						//it will wipe the screen black. You can do whatever color like window.clear(sf::Color(255,255,255))
						//															or  window.clear(sf::Color::Red)
						// using things with :: is just grabbing things out of that namespace. the sf namespace has a var named color
						// with a var of red. _NOT TO BE CONFUSED WITH_ grabbing things out of a _class_. for example. Button.color = sf::Color::Red
		
		shape.setPosition(boxes[0]); // <-- make sure we set the position of the shape to the CURRENT position of boxes[0] every frame
		window.draw(shape);			 // <-- and now we draw our shape object to the window object and are done!

		//draw the window. literally just pass the frame to be buffered and displayed.
		window.display();
	}
	//return okay if the program exits properly. main() is looking for a return of type 'int', since 'int' is in front of it
	// 0 is code for okay, 1 is not. lol. 
	
    return 0;
}