#include <iostream>
#include <pressure_paroscientific/Driver.hpp>


void usage()
{
	std::cerr << "You must enter for example : serial:///dev/ttyACM3:115200 " << std::endl;
}


int main(int argc, char** argv)
{

	if (argc != 2)
	{
		usage();
		return 1;
	}

	pressure_paroscientific::Driver driver;
	driver.open(argv[1]);

	while (true) {
		driver.collectPeriodicData();
		pressure_paroscientific::ParoData data = driver.getData();
		std::cout << data.time.toString() << "   ";
		driver.dumpData();
	}

	return 0;
}
