#include "DocManager.hpp"

namespace dc {

    DocManager::DocManager(File const &img_file) : img_file(img_file)
    {
        this->image_ = cv::imread(std::string(img_file.get_path()));
    }

    cv::Mat const &DocManager::get_image() { return this->image_; }
    cv::Mat DocManager::get_gray_image() const
    {
        cv::Mat gray;
        cv::cvtColor(this->image_, gray, cv::COLOR_BGR2GRAY);
        return gray;
    }

    cv::Mat DocManager::get_canny_edges(double threshold1, double threshold2)
    {
        cv::Mat canny_img;
        cv::Mat gray = this->get_gray_image();
        cv::Canny(gray, canny_img, 25, 75, 5, true);
        return canny_img;
    }

    std::vector<cv::Point> DocManager::getContours(cv::Mat const &image)
    {
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;

        cv::findContours(image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        std::vector<cv::Point> max_contour;
        int max_perimeter = 0;
        for (auto &contour : contours)
        {
            int tmp_perimeter = 0;
            auto const [min, max] = std::ranges::minmax_element(contour,
                    [](auto& l, auto& r){ return l.x + l.y < r.x + r.y; });
            auto const [min_2, max_2] = std::ranges::minmax_element(contour,
                    [&image](auto& l, auto& r){ 
                        return l.x + image.size().height - l.y < r.x + image.size().height - r.y;
                            });
            tmp_perimeter = max_2->x - min->x + max->y - max_2->y + max->x - min_2->y + min_2->y - min->y;
            if (tmp_perimeter > max_perimeter)
            {
                max_contour = {{min->x, min->y}, {max_2->x, max_2->y},
                    {max->x, max->y}, {min_2->x, min_2->y}};
                max_perimeter = tmp_perimeter;
            }
        }
        std::cout << max_contour << std::endl;
        return max_contour;
    }

    cv::Mat DocManager::get_document(std::vector<cv::Point> &points)
    {
        const auto &img = this->get_image();
        cv::Mat warped_img;
        float w =(float)(points[1].x - points[0].x + points[2].x - points[3].x) / 2;
        float h = (float)(points[3].y - points[0].y + points[2].y - points[1].y) / 2;
        std::vector<cv::Point2f> pointA(points.begin(), points.end());
        std::vector<cv::Point2f> pointB = { {0.0f, 0.0f}, {w, 0.0f}, {w,h}, {0.0f, h} };
        cv::Mat matrix = cv::getPerspectiveTransform(pointA, pointB);

        cv::warpPerspective(img, warped_img, matrix, cv::Point(w, h));

        return warped_img;
    }

}
