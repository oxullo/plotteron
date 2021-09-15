//
//  scrollingbuffer.hpp
//  plotteron
//
//  Created by OXullo Intersecans on 10.09.21.
//

#ifndef scrollingbuffer_hpp
#define scrollingbuffer_hpp

#include <Mahi/Gui.hpp>


class ScrollingBuffer {
public:
    ScrollingBuffer(int initial_size=6000);

    void add_point(double x, double y);
    void erase();
    double get_min_x();
    double get_max_x();
    void resize(int size);

    ImVector<ImVec2> data;
    int max_size;
    int offset;
};

#endif /* scrollingbuffer_hpp */
