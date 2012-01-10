#include <iostream>
#include <pressure_paroscientific/Driver.hpp>

int main(int argc, char** argv)
{
	pressure_paroscientific::Driver driver;
    driver.open("udpserver://4446");

    while (true) {
        driver.collectPeriodicData();
        pressure_paroscientific::ParoData data = driver.getData();
        std::cout << data.time.toString() << "    ";
        driver.dumpData();
    }

	return 0;
}
