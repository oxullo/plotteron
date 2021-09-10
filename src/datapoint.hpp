//
//  datapoint.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 10.09.21.
//

#ifndef datapoint_hpp
#define datapoint_hpp

#include <chrono>

class DataPoint {
public:
    DataPoint(double value);
    double get_timestamp();
    double get_value();
    
private:
    std::chrono::high_resolution_clock::time_point timestamp;
    double value;
};

#endif /* datapoint_hpp */
