//Including header files
#include <opencv2/opencv.hpp>
#include <iostream>
#include "File.hpp"
#include "DocManager.hpp"
#include "FrameCorrector.hpp"

int main(int argc, char const *argv[])
{
	if (argc == 1)
	{
		std::cout << "Give me an image" << std::endl;
		return 1;
	}
	auto file = dc::File(argv[1]);
	if (!file.is_valid())
	{
		std::cout << "Invalid file" << std::endl;
		return 2;
	}
	dc::DocManager manager(file);
	cv::Mat edges = manager.get_canny_edges();
	auto contour = manager.getContours(edges);

	dc::FrameCorrector correct_frame(manager.get_image(), contour);

	contour = correct_frame.correct_mode();
	auto document = manager.get_document(contour);

	cv::imshow("Canny image", document);
	cv::imwrite(file.path_to_document(), document);
	cv::waitKey(0);

	return 0;
}
