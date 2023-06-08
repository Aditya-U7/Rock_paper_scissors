/* Author: Aditya Upadhye 

This is an implementation of Rock, Paper, Scissor game using an abstract class. 

Abstract class provides the interface, and derived classes provide the implementation and data.

Other language features that have been used are enum class, static_cast and srand() function.

Two global friend functions have been used to aid the program.

*/


#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

class Player
{

	public:

		virtual void select_rps() = 0;
		virtual void set_name() = 0;
		virtual short get_selected_rps() = 0;
		virtual ~Player(){};
		virtual std::string get_name() = 0;
		virtual void incr_points() = 0;
		virtual short get_points() = 0;

};

/////////////////////////////////////////////////////////////////////////////////////////////

class Human_player: public Player 
{

	public:

		friend void check_for_rps(Player*, Player*);
		friend bool winner_found(Player*, Player*);


		void select_rps() override
		{

			while (true)
			{

				std::cout << "\n" << name << ", select rock [ r ], paper [ p ] or scissor [ s ]" << std::endl;
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
					break;

			}
		}


		void set_name() override
		{

			std::cout << "Enter your name:" << std::endl;
			std::cin >> name;

		}

		std::string get_name() override
		{
			return name;
		}

		short get_selected_rps() override
		{

			return (static_cast<short>(usr_selected_obj));   

		}

		short get_points() override
		{

			return points;

		}

		void incr_points() override
		{

			points += 1;

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

		friend void check_for_rps(Player*, Player*);
		friend bool winner_found(Player*, Player*);

		void set_name() override
		{

			std::cout << "\nComputer name set to " << name << std::endl; 

		}

		std::string get_name() override 
		{ 

			return name; 

		}

		void select_rps() override
		{

			cmp_selected_obj = (rand() % 3);

			std::cout << "\n\n" << name << " selected this: " << obj[cmp_selected_obj] << "\n\n";

		}

		short get_selected_rps() override
		{

			return cmp_selected_obj;

		}

		void incr_points() override
		{

			points += 1;

		}

		short get_points() override
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

void check_for_rps(Player* one, Player* two)
{

	short one_rps = one -> get_selected_rps(); 
	short two_rps = two -> get_selected_rps();

	if (one_rps == two_rps)
	{

		std::cout << "Equal match; a tie." << std::endl;
	}

	else if ((one_rps == 0 && two_rps == 2) || (one_rps == 1 && two_rps == 0) || (one_rps == 2 && two_rps == 1))
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

bool winner_found(Player* one, Player* two)
{

	short op = one -> get_points();
	short tp = two -> get_points();

	if (op < 3 && tp < 3)
		return false;

	std::string player_name;

	if (op == 3)
	{

		player_name = one -> get_name();

	}

	else if (tp == 3)
	{

		player_name = two -> get_name();

	}

	std::cout <<"\n\n" << player_name << " has won." << std::endl; 

	return true;

}

////////////////////////////////////////////////////////////////////////

int main()
{

	srand(time(0));

	std::cout << "ROCK, PAPER AND SCISSORS: BEST OF THREE\n\n";

	Player* hp {new Human_player()};
	hp -> set_name();

	Player* cp {new Comp()};
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
