/* Author: Aditya Upadhye 

   This is an implementation of Rock, Paper, Scissors game using an abstract class. 

   Abstract class provides the interface, and derived classes provide the implementation and data.

   Other language features that have been used are enum class, static_cast, unique_ptr and srand() function.

   Two global friend functions have been used to aid the program.

 */


#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <memory>

class Player
{

	public:

		virtual void select_rps() = 0;
		virtual void set_name() = 0;
		virtual short get_selected_rps() const = 0;
		virtual std::string get_name() const = 0;
		virtual void incr_points() = 0;
		virtual short get_points() const = 0;
		virtual ~Player(){};

};

/////////////////////////////////////////////////////////////////////////////////////////////

class Human_player: public Player 
{

	public:

		friend void check_for_rps(const std::unique_ptr<Player>&, const std::unique_ptr<Player>&);
		friend bool winner_found(const std::unique_ptr<Player>&, const std::unique_ptr<Player>&);

                   
		void select_rps() override
		{

			while (true)
			{

				std::cout << "\n" << name << ", select rock [ r ], paper [ p ] or scissors [ s ]" << std::endl;
				std::cin >> c;


				if (c != 'p' && c!= 'r' && c!= 's' )

					std::cout << "Invalid input." << std::endl;

				else

					break;

			}

			switch (c)
			{

				case ('r'):
					usr_selected_obj = Rps::rock;
					break;

				case ('p'):
					usr_selected_obj = Rps::paper;
					break;

				case ('s'):
					usr_selected_obj = Rps::scissors;


			}
		}


		void set_name() override
		{

			std::cout << "Enter your name:" << std::endl;
			std::cin >> name;

		}

		short get_selected_rps() const override
		{

			return (static_cast<short>(usr_selected_obj));   

		}

		std::string get_name() const override
		{
			return name;
		}

		void incr_points() override
		{

			points += 1;

		}

		short get_points() const override
		{

			return points;

		}


	private:

		std::string name = "player_name_uninitialised";

		short points = 0;

		enum class Rps: char {rock, paper, scissors};

		Rps usr_selected_obj = Rps::rock;

		char c;

};

/////////////////////////////////////////////////////////////////////////////////////////////

class Comp: public Player
{

	public:

		friend void check_for_rps(const std::unique_ptr<Player>&, const std::unique_ptr<Player>&);
		friend bool winner_found(const std::unique_ptr<Player>&, const std::unique_ptr<Player>&);
                
		void select_rps() override
		{

			cmp_selected_obj = (rand() % 3);

			std::cout << "\n\n" << name << " selected this: " << obj[cmp_selected_obj] << "\n\n";

		}

		void set_name() override
		{

			std::cout << "\nComputer name set to " << name << std::endl; 

		}

		short get_selected_rps() const override
		{

			return cmp_selected_obj;

		}

		std::string get_name() const override 
		{ 

			return name; 

		}

		void incr_points() override
		{

			points += 1;

		}

		short get_points() const override
		{

			return points;

		}


	private:

		std::string name = "Conscious Binary";

		short cmp_selected_obj = 0;

		short points = 0;

		std::vector<std::string> obj {"Rock", "Paper", "Scissors"};

};

///////////////////////////////////////////////////////////////////////// 

void check_for_rps(const std::unique_ptr<Player>& one, const std::unique_ptr<Player>& two)
{

	short one_rps = one -> get_selected_rps(); 
	short two_rps = two -> get_selected_rps();

	if (one_rps == two_rps)
	{

		std::cout << "Equal match; a tie." << std::endl;
	}

	else if ((one_rps == 0 && two_rps == 2) || (one_rps == 1 && two_rps == 0) || (one_rps == 2 && two_rps == 1))  // Rock = 0, Paper = 1 and Scissors = 2.
	{

		one -> incr_points(); 
		std::cout << one -> get_name() << " won this round." << std::endl;

	}

	else 
	{

		two -> incr_points();   
		std::cout << two -> get_name() << " won this round." << std::endl;

	}

}

bool winner_found(const std::unique_ptr<Player>& one, const std::unique_ptr<Player>& two)
{

	short op = one -> get_points();
	short tp = two -> get_points();

	if (op < 3 && tp < 3)
		return false;

	std::string player_name;

	if (op == 3)

		player_name = one -> get_name();

	else

		player_name = two -> get_name();


	std::cout <<"\n\n" << player_name << " has won." << std::endl; 

	return true;

}

////////////////////////////////////////////////////////////////////////

int main()
{

	srand(time(0));

	std::cout << "ROCK, PAPER AND SCISSORS: BEST OF THREE\n\n";

	std::unique_ptr<Player> hp {new Human_player()};
	hp -> set_name();

	std::unique_ptr<Player> cp {new Comp()};
	cp -> set_name();

	while (true)
	{

		hp -> select_rps();
		cp -> select_rps();

		check_for_rps(hp, cp);

		std::cout <<"\n\n" << hp -> get_name() << ": points = " << hp -> get_points() << std::endl;
		std::cout << cp -> get_name() << ": points = " << cp -> get_points() << std::endl;

		if (winner_found(hp, cp))
			break;

	}

	return 0;

}
