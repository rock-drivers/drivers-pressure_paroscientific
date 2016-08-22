/*
 * Types.hpp
 *
 *  Created on: 27.12.2012
 *      Author: hbuettner
 */

#ifndef PRESSURE_PAROSCIENTIFIC_TYPES_HPP
#define PRESSURE_PAROSCIENTIFIC_TYPES_HPP

#include <base/Time.hpp>

namespace pressure_paroscientific {
    // namespace pressure_paroscientific

    struct ParoData {
        base::Time  time;
        double  depth;
    };


}


#endif /* PRESSURE_PAROSCIENTIFIC_TYPES_HPP */
