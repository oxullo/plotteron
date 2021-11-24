//
//  datapoint.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 10.09.21.
//

#ifndef sample_hpp
#define sample_hpp


class Sample {
public:
    Sample(double timestamp, std::string raw_line);
    double get_timestamp();
    std::string get_raw_line();
    double get_value();

private:
    double timestamp;
    std::string raw_line;
};

#endif /* sample_hpp */
