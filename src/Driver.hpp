/*
 * Driver.hpp
 *
 *  Created on: 27.12.2012
 *      Author: hbuettner
 */

#ifndef PRESSURE_PAROSCIENTIFIC_DRIVER_HPP
#define PRESSURE_PAROSCIENTIFIC_DRIVER_HPP

#include <iodrivers_base/Driver.hpp>
#include "PressureTypes.hpp"

namespace pressure_paroscientific
{

    class Driver : public iodrivers_base::Driver
    {
    public:
        Driver();

        /** Tries to access the CTD at the provided URI
         *
         */
        void open(std::string const& uri);
        /** Reads available data and update the \c data structure. If
         * this method returns true, then \c data has been updated with
         * a new, synchronized set of information. Otherwise, call
         * collectPeriodicData again.
         */
        void collectPeriodicData();

        pressure_paroscientific::ParoData getData() const;

        void dumpData() const;

    protected:
        /** Read available packets on the I/O */
        std::string read(int timeout);

        /** Extract an ASCII line from incoming Data
         *
         */
        int extractPacket (uint8_t const *buffer, size_t buffer_size) const;

    private:
        pressure_paroscientific::ParoData     data;
    };

} /* pressure_paroscientific */
#endif /* PRESSURE_PAROSCIENTIFIC_DRIVER_HPP */
