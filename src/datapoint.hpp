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
    DataPoint(double timestamp, std::string raw_line);
    double get_timestamp();
    std::string get_raw_line();
    double get_value();

private:
    double timestamp;
    std::string raw_line;
};

#endif /* datapoint_hpp */
