/*
Условие:
Есть GCODE Данного формата X(value);Y(value);Z(value).
Он используется для передачи команд микроконтроллеру, который в свою очередь
управляет устройством, например манипулятором. Подробнее про GCODE можно
прочитать тут.
Обычно GCODE выполняется построчно, поэтому если в скрипте оказалась ошибка, то
только на ошибочной строке он остановится.
Входные данные:
GCODE

Задача:
Выведете конечные координаты устройства после выполнения комманд GCODE.
P.S. При написании кода обратите внимание на различные форматы GCODE
команд.
*/








#include <iostream>
#include <string>
#include <sstream>


bool run_gcode(const std::string& str)
{
	//состояние системы
	int x = 0;
	int y = 0;
	int z = 0;

	//проверка на отсудствие команд
	if(str.empty())
	{
		std::cout << x << " " << y << " " << z << '\n';
		std::cout << "ERROR SCRIPT LINE 0";
		return false;
	}
	std::stringstream r{ str };

	int xa = 0;
	int ya = 0;
	int za = 0;

	char xc = 0;
	char yc = 0;
	char zc = 0;

	char xt;
	char yt;
	char zt;
	int line = 1;

	//считываем и проверяем начальные координаты
	if(!(r >> xa >> ya >> za))
	{
		std::cout << x << " " << y << " " << z << '\n';
		std::cout << "ERROR SCRIPT LINE " << line;
		return false;
	};

	x += xa;
	y += ya;
	z += za;

	while(!r.eof())
	{
		line++;
		//считываем и парсим строку
		if(r >> xc >> xa >> xt >> yc >> ya >> yt >> zc >> za >> zt)
		{
			if((xc == 'X') &&
			   (yc == 'Y') &&
			   (zc == 'Z') &&
			   (xt == ';') &&
			   (yt == ';') &&
			   (zt == ';'))
			{
				//если прошли проверку исполняем команду
				x += xa;
				y += ya;
				z += za;
			}
		}
		else
		{
			std::cout << x << " " << y << " " << z << '\n';
			std::cout << "ERROR SCRIPT LINE " << line;
			return false;
		}
	}

	std::cout << x << " " << y << " " << z << '\n';
	return true;
}

void main()
{

	const std::string gcode1(
		"10 20 0\n"
		"X-10;Y20;Z30;\n"
		"X40;Y-20;Z20;\n"
		"X-10;Y-20;Z-10;\n"
		"X-10;Y-20;<Z-10;\n"
		"X10;Y20;Z10;\n");


	run_gcode(gcode1);



}