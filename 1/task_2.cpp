/*
Условие:
Движение манипуляторов это, конечно, хорошо, но обычно с помощью кода они
двигаются по определенным координатам, для сборки того или иного компонента.
Даны два манипулятора, которые описываются стартовыми центрами O1 и O2 и
радиусом их действия R1 и R2 в декартовой системе координат. Радиус действия не
изменяется в течении работы программы. Также дан массив точек, где лежат детали
P1…Pn.

Задача:
Выведете две строки: какие точки обойдет каждый манипулятор.
Замечание: Важно помнить, что до детали должен дойти “оптимальный” манипулятор
на текущей итерации процесса. Оптимальность можно считать по длине пути до точки.
Радиус не учитывается. Пример ниже.

Пример:
Есть массив точек:
{1, 3}, {2, 1.41}, {0.2, -7} ,{-5, -1} , {0, 9}
Манипуляторы на старте:
M1: ({0, 0} , 4)
M2: ({2, 1}, 3)
*/




#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <string>



class Hand
{
public:
	explicit Hand(double x, double y, double r) :radius(r), Coord({ x,y })
	{};
	double radius;
	std::pair<double, double>Coord;
};

template<class _It>
_It find_best_hand(const _It begin_it,
				   const _It end_it,
				   const std::pair<double, double>& dot)
{
	using pair_d_pHand = std::pair<double, _It>;
	std::vector<pair_d_pHand> hand_in_range;


	for(auto a = begin_it; a != end_it; a++)
	{
		auto dx = dot.first - (*a).Coord.first;
		auto dy = dot.second - (*a).Coord.second;
		auto r = sqrt(pow(dx, 2) + pow(dy, 2));
		if(r <= (*a).radius)
		{
			hand_in_range.push_back({ r, a });
		}
	}
	if(hand_in_range.size() < 1) { return end_it; }

	constexpr auto hand_cmp([](const auto& a, const auto& b) constexpr
	{
		return a.first < b.first;
	});
	auto rez = std::min_element(begin(hand_in_range), end(hand_in_range), hand_cmp);

	return (*rez).second;
}

int main()
{
	std::vector hands
	{
		Hand{0.0,	0.0,	4.0},
		Hand{2.0,	1.0,	3.0}
	};
	std::vector<std::pair<double, double>> dots
	{
		{1,		3},
		{2,		1.41},
		{0.2,	-7},
		{-5,	-1},
		{0,		9}
	};

	std::vector<std::string> str{ hands.size() + 1, "" };

	int iter = 1;
	for(auto& dot : dots)
	{
		auto hand = find_best_hand(begin(hands), end(hands), dot);

		if(hand != end(hands))
		{
			auto id = std::distance(begin(hands), hand);
			int size = str.size();
			for(int i = 0; i < size; i++)
			{
				if(i == 0)
				{

					str[i] += std::to_string(iter++) + "\t\t";
					continue;
				}
				if(i == id + 1)
				{
					str[i] +=
						"{" + std::to_string(dot.first).erase(4)
						+ ", " + std::to_string(dot.second).erase(4) + "}\t";
				}
				else
				{
					str[i] += "\t\t\t";
				}
			}
		}
	}

	auto str_end = str.size();
	std::cout << "iter\t" << str[0] << '\n';
	for(int i = 1; i < str_end; i++)
	{
		std::cout << "hand_" << i << "\t" << str[i] << '\n';
	}

}