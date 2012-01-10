/*
 * Driver.cpp
 *
 *  Created on: 27.12.2012
 *      Author: hbuettner
 */

#include <string>
#include <iostream>
#include <errno.h>
#include <iodrivers_base/Timeout.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

#include "Driver.hpp"

using namespace pressure_paroscientific;
using namespace std;
using namespace boost;


Driver::Driver()
    : iodrivers_base::Driver(64)
{
    data.depth = 0;
}

void Driver::open(const std::string & uri)
{
    openURI(uri);
}


void Driver::collectPeriodicData()
{
    string message;
    try {
        message = read(2000);
    } catch (iodrivers_base::TimeoutError&) {
        cout << "pressure_paroscientific timeout" << endl;
        return;
    }

    message.erase(0,1);
    //cout << "Data received: " << message;
    data.time = base::Time::now();
    data.depth = atof(message.c_str());
}

pressure_paroscientific::ParoData Driver::getData() const
{
    return data;
}

void Driver::dumpData() const
{
    cout << setprecision(3) << data.time << " "
         << setprecision(3) << data.depth <<  endl;
}

std::string Driver::read(int timeout)
{
//  *ppppppp.ppp

    char buffer[MAX_PACKET_SIZE];
    size_t packet_size = readPacket(reinterpret_cast<uint8_t *>( buffer), MAX_PACKET_SIZE, 5000, timeout);
    return string(buffer, packet_size);
}

int Driver::extractPacket(const uint8_t *buffer, size_t buffer_size) const
{

    for (size_t i = 0; i < buffer_size; i++) {
        if (buffer[i] == '\n') {
            if ( i < 12 ) {
                return -(i + 1);
            }
            return i + 1;
        }
    }
    return 0;
}



