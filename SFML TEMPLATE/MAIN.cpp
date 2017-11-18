#include <iostream>
#include <SFML\Main.hpp>
#include <time.h>
#include "Manager.h"
//
int main()
{
	srand(time(NULL));
	Manager *manager = new Manager();
	manager->Programa();
	delete manager;
	return 0;
}