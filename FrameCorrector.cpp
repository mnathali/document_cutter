#include "FrameCorrector.hpp"

namespace dc {

    FrameCorrector::FrameCorrector(cv::Mat const &img, std::vector<cv::Point> frame) : img_(img), frame_(frame) {}

    static void drawShape(int action, int x, int y, int flags, void *userdata)
    {
        if (action == cv::EVENT_LBUTTONDOWN)
        {
            std::vector<cv::Point> &frame = *reinterpret_cast<std::vector<cv::Point>*>(userdata);
            auto min_lenght_point = std::ranges::min_element(frame, [x, y](auto &l, auto &r){
                return (l.x - x) * (l.x - x) + (l.y - y) * (l.y - y) <
                            (r.x - x) * (r.x - x) + (r.y - y) * (r.y - y);
            });
            *min_lenght_point = {x, y};
        }
    }

    std::vector<cv::Point> FrameCorrector::correct_mode()
    {
        cv::Mat const &img = this->img_;
        std::vector<cv::Point> &frame = this->frame_;
        int p_radius = (img.size().height + img.size().width) / (2 * 100);
        cv::namedWindow("Correct the frame");
        cv::setMouseCallback("Correct the frame", drawShape, &frame);
        for (int key = 0; key != 13;)
        {
            cv::Mat draw_img;
            this->img_.copyTo(draw_img);
            for (auto &point : frame)
                cv::circle(draw_img, point, p_radius, cv::Scalar(0, 0, 255), p_radius / 4);
            for (int i = 1; i < frame.size(); ++i)
                cv::line(draw_img, frame[i-1], frame[i], cv::Scalar(0, 0, 255), p_radius / 4);
            cv::line(draw_img, frame[0], frame[3], cv::Scalar(0, 0, 255), p_radius / 4);
            cv::imshow("Correct the frame", draw_img);
            key = cv::waitKey(1);
        }
        cv::destroyWindow("Correct the frame");
        return frame;
    }

}