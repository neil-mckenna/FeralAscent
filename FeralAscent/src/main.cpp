#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "framework/Application.h"

using namespace	std;
using namespace sf;
using namespace fa;

const int gameHeight = 768;
const int gameWidth = 1024;


int main()
{
	unique_ptr<fa::Application> app = make_unique<fa::Application>();
	app->Run();

}





