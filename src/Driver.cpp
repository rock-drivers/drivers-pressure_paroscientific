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
#include <iomanip>

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

	message.erase(0,5); // remove the star + "0001" so 5 characters
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
	cout << setprecision(3) << "TIME = " << data.time << setprecision(3) << "  DEPTH = "<< data.depth<<endl;
}

std::string Driver::read(int timeout)
{
	// Format received = *ppppppp.ppp
	char buffer[MAX_PACKET_SIZE];
	size_t packet_size = readPacket(reinterpret_cast<uint8_t *>( buffer), MAX_PACKET_SIZE, 5000, timeout);
	return string(buffer, packet_size);
}

/** DecToHex
    Print an Hex value from a decimal value

    @param  n Type int

    @return string
*/
string DecToHex(int n)
{
    ostringstream oss;
    oss<<hex<<n;
    return oss.str();
}

/** extractPacket
    Extract the packet in the buffer

    @param buffer      Type uint8_t const
    @param buffer_size Type size_t

    @return int -buffer size or buffer size of the packet
*/
int Driver::extractPacket(const uint8_t *buffer, size_t buffer_size) const
{
//    for (int i = 0 ; i < (int)buffer_size ; i++ ){
//        std::cout<<"("<<i<<")"<<"="<<DecToHex((int)buffer[i])<<" ";
//        if(i%20==0 &&i!=0)
//            std::cout<<""<<std::endl;
//    }
//    std::cout<<""<<std::endl;

	if(buffer_size > 0){
		if(buffer[0] == 0x2A){ // 0x2A = * in ASCII code
			//std::cout<<"[extractPacket]: We have a valid header"<<std::endl;

			if(buffer[buffer_size-1] == '\n'){
				//std::cout<<"[extractPacket]: We have a full packet"<<std::endl;
				//there is a full packet in buffer, starting at the first buffer byte. Return the packet size.
				//That data will be copied back to the buffer given to readPacket.
				return buffer_size;
			}
			else {
				//a packet begins at the first byte of buffer, but the end of the packet is not in buffer yet. Return 0.
				//std::cout<<"[extractPacket]: First byte but not the end of the packet YET"<<std::endl;
				return 0;
			}
		}//byte1 is not "*"
		else{
			//there is the beginning of a packet but it is not starting at the first byte of buffer.
			//In that case, return -position_packet_start, where position_packet_start is the position of the packet in buffer.
			for (unsigned int pos_pack_start = 0 ; pos_pack_start < buffer_size - 1 ; pos_pack_start++){
				if(buffer[pos_pack_start] == 0x2A){ // 0x2A = * in ASCII code
					//std::cout<<"[extractPacket]: We have a header but not at pos 1"<<std::endl;
					return -pos_pack_start;
				}
			}
                        return 0;
		}

	}//buffer_size <= 0
	else{
		//there is no packet in the buffer. In that case, return -buffer_size to
		//discard all the data that has been gathered until now.
		std::cout<<"[extractPacket]: no packet in buffer"<<std::endl;
		return -buffer_size;
	}

}



