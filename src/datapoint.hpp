//
//  datapoint.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 10.09.21.
//

#ifndef datapoint_hpp
#define datapoint_hpp


class DataPoint {
public:
    DataPoint(double timestamp, double value);
    double get_timestamp();
    double get_value();
    
private:
    double timestamp;
    double value;
};

#endif /* datapoint_hpp */
