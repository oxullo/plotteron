//
//  datapoint.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 10.09.21.
//

#include <iostream>

#include <Mahi/Util/Logging/Log.hpp>

#include "datapoint.hpp"

using namespace mahi::util;


DataPoint::DataPoint(double timestamp, std::string raw_line) :
    timestamp(timestamp),
    raw_line(raw_line)
{
//    std::cerr << "Datapoint ts=" << timestamp << std::endl;
//    std::cerr << "DP v=" << value << std::endl;
}

double DataPoint::get_timestamp()
{
    return timestamp;
}

std::string DataPoint::get_raw_line()
{
    return raw_line;
}

double DataPoint::get_value()
{
    return std::stod(raw_line);
}
