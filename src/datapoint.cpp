//
//  datapoint.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 10.09.21.
//

#include <iostream>

#include "datapoint.hpp"

DataPoint::DataPoint(double value) : timestamp(std::chrono::high_resolution_clock::now()), value(value)
{
//    std::cerr << "Datapoint ts=" << timestamp.time_since_epoch().count() << std::endl;
//    std::cerr << "DP v=" << value << std::endl;
}

double DataPoint::get_timestamp()
{
    return timestamp.time_since_epoch().count();
}

double DataPoint::get_value()
{
    return value;
}
