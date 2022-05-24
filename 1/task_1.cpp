/*
Условие:
Есть два манипулятора. Их инструменты находятся в точках О1 и О2 в декартовой
системе координат (X, Y). У каждого манипулятора есть свой радиус эффективного
действия R1 и R2.
Есть целевая точка P1.

Задача:
Определите, каким манипулятором оптимальнее дойти до точки P1.
Если оба манипулятора не могут достать, то вывести сообщение: “OUT OF RANGE”.
Если точка доступна одному манипулятору – использовать его.
*/








#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

//класс манипулятора
class Hand
{
public:
	explicit Hand(double x, double y, double r) :radius(r), Coord({x,y})
	{};
	double radius;
	std::pair<double, double>Coord;
};

//шаблонная фн для поиска оптимального манипулятора
//возвращает итератор манипулятора из входного контейнера
//шаблон чтобы отвязаться от контейнера и не писать полностью название итератора
template<class _It>
_It find_best_hand(const _It begin_it,
					const _It end_it,
					const std::pair<double, double>& dot)
{
	using pair_d_pHand = std::pair<double, _It>;
	//вектор доступных манипуляторв с расчитанным радиусом
	std::vector<pair_d_pHand> hand_in_range;

	//расчёт радиуса
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

	//поиск ближайшего манипулятора
	constexpr auto hand_cmp([](const auto &a, const auto &b) constexpr
	{
		return a.first < b.first;
	});
	auto rez = std::min_element(begin(hand_in_range), end(hand_in_range), hand_cmp);

	return (*rez).second;
}

int main()
{
	//список манипуляторов
	std::vector hands
	{
		Hand{0.0,	0.0,	60.0},
		Hand{0.0,	100.0,	60.0}
	};

	//рабочая точка
	std::pair<double, double> dot{ 0, 51 };

	//полуем итератор оптимального манипулятора
	auto hand = find_best_hand(begin(hands), end(hands), dot);

	if(hand == end(hands))
	{
		std::cout << "OUT OF RANGE\n";
	}
	else
	{
		std::cout << "using hand id "
			//индекс найденого манипулятора в контейнере
			<< std::distance(begin(hands), hand)
			<< '\n';
	}


}