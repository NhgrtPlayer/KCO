#include "main.hpp"

const static int MAX_DUPLICATE = 1;

const static std::vector<Item> KFC_LIST = {
	Item("Menu Tenders x4", 7.65),
	Item("Twister", 2),
	Item("Menu Chick'n Box (3 Tenders, M Frite, M Boisson)", 4.95),
	Item("Menu Chick'n Box XL (3 Tenders, G Frite, G Boisson)", (4.95 + 0.75)),
	Item("Sunday Chocolat", 2),
	Item("Crousty", 2),
	Item("Box de 13 Tenders (Mardi uniquement)", 6.95),
	Item("Menu Boxmaster (Boxmaster, M Frite, M Boisson)", 7.85)
};

int item_duplicate(const std::vector<Item>& vec, const std::string& name)
{
	int to_return = 0;

	for (auto const &e : vec){
		if (e.getName() == name)
			to_return++;
	}
	return (to_return);
}

float getTotalPrice(const std::vector<Item>& vec)
{
	float to_return = 0;

	for (auto const &e : vec) {
		to_return += e.getPrice();
	}
	return (to_return);
}

std::vector<Item>
do_magic_stuff(const std::vector<Item>& item_vec,
			const float& budget,
			std::vector< std::vector<Item> >& to_fill,
			std::vector<Item> current = {})
{
	std::vector<Item> to_return = current;

	for (auto const &e : item_vec)
	{
		if (item_duplicate(current, e.getName()) <= MAX_DUPLICATE - 1 && (e.getPrice() + getTotalPrice(to_return)) <= budget)
		{
			std::vector<Item> tmp(to_return);
			tmp.push_back(e);
			to_fill.push_back(do_magic_stuff(item_vec, budget, to_fill, tmp));
		}
	}
	return (to_return);
}

void print_results(std::vector< std::vector<Item> >& vec)
{
	int i = 0, j = 0;

	std::cout << std::fixed << std::setprecision(2);
	for (auto const &e : vec)
	{
		std::cout << i << " (" << getTotalPrice(e) << "): ";
		j = 0;
		for (auto const &f : e)
		{
			std::cout << f.getName();
			j++;
			if (j < e.size())
				std::cout << ", ";
		}
		std::cout << '\n';
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	float budget = std::stof(av[1]);
	std::vector< std::vector<Item> > to_fill;
	do_magic_stuff(KFC_LIST, budget, to_fill);
	std::sort( to_fill.begin( ), to_fill.end( ), [ ]( const std::vector<Item>& lhs, const std::vector<Item>& rhs)
	{
   		return (getTotalPrice(lhs) > getTotalPrice(rhs));
	});
	print_results(to_fill);
}