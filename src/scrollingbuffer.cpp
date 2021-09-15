//
//  scrollingbuffer.cpp
//  plotteron
//
//  Created by OXullo Intersecans on 10.09.21.
//

#include "scrollingbuffer.hpp"

ScrollingBuffer::ScrollingBuffer(int initial_size) : max_size(initial_size), offset(0)
{
    data.reserve(initial_size);
}

void ScrollingBuffer::add_point(double x, double y)
{
    if (data.size() < max_size)
        data.push_back(ImVec2(x, y));
    else {
        data[offset] = ImVec2(x, y);
        offset = (offset + 1) % max_size;
    }
}

void ScrollingBuffer::erase()
{
    if (data.size() > 0) {
        data.shrink(0);
        offset = 0;
    }
}

double ScrollingBuffer::get_min_x()
{
    if (data.size() > 0) {
        return data[offset].x;
    } else {
        return 0;
    }
}

double ScrollingBuffer::get_max_x()
{
    if (data.size() > 0) {
        int maxindex = ((offset - 1) % data.size() + data.size()) % data.size();
        return data[maxindex].x;
    } else {
        return 0;
    }
}

void ScrollingBuffer::resize(int size) {
    erase();
    data.reserve(size);
    max_size = size;
}
