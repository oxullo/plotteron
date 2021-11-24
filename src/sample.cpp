//
//  datapoint.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 10.09.21.
//

#include <iostream>

#include <Mahi/Util/Logging/Log.hpp>

#include "sample.hpp"


using namespace mahi::util;


Sample::Sample(double timestamp, std::string raw_line) :
    timestamp(timestamp),
    raw_line(raw_line)
{
}

double Sample::get_timestamp()
{
    return timestamp;
}

std::string Sample::get_raw_line()
{
    return raw_line;
}

double Sample::get_value()
{
    return std::stod(raw_line);
}
