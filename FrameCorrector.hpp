#ifndef FRAME_CORRECTOR_HPP
#define FRAME_CORRECTOR_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include <limits>
#include <algorithm>
#include <ranges>

namespace dc {

    class FrameCorrector {

        public:

            FrameCorrector(cv::Mat const &img, std::vector<cv::Point> frame);
            ~FrameCorrector() = default;
            FrameCorrector() = delete;
            FrameCorrector(FrameCorrector const &) = delete;
            FrameCorrector(FrameCorrector const &&) = delete;
            FrameCorrector &operator=(FrameCorrector const &) = delete;
            FrameCorrector &operator=(FrameCorrector const &&) = delete;

            std::vector<cv::Point> correct_mode();

        private:

            cv::Mat const &img_;
            std::vector<cv::Point> frame_;

    };

}


#endif