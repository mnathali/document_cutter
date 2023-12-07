#ifndef DOCMANAGER_HPP
#define DOCMANAGER_HPP

#include <iostream>
#include "File.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <ranges>

namespace dc {

    class DocManager {

        public:

            DocManager(File const &img_file);
            ~DocManager() = default;
            DocManager() = delete;
            DocManager(DocManager const &) = delete;
            DocManager(DocManager const &&) = delete;
            DocManager& operator=(DocManager const &) = delete;
            DocManager& operator=(DocManager const &&) = delete;
            cv::Mat const &get_image();
            cv::Mat get_gray_image() const;
            cv::Mat get_canny_edges(double threshold1 = 100, double threshold2 = 100);
            std::vector<cv::Point> getContours(cv::Mat const &image);
            cv::Mat get_document(std::vector<cv::Point> &points);


        private:

            File        img_file;
            cv::Mat     image_;


    };


}

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& vec)
{
    o << '[';
    for (typename std::vector<T>::const_iterator it = vec.begin(); it < vec.end(); ++it)
        o << *it << ",";
    o << ']';
    return o;
}

#endif