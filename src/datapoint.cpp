//
//  datapoint.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 10.09.21.
//

#include <iostream>

#include "datapoint.hpp"

DataPoint::DataPoint(double timestamp, double value) : timestamp(timestamp), value(value)
{
//    std::cerr << "Datapoint ts=" << timestamp << std::endl;
//    std::cerr << "DP v=" << value << std::endl;
}

double DataPoint::get_timestamp()
{
    return timestamp;
}

double DataPoint::get_value()
{
    return value;
}
