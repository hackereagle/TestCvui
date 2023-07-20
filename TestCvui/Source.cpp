#include <iostream>
#include <opencv2/opencv.hpp>
#include "cvui.h"

#define WINDOW_NAME     "Setting"
#define SOURCE_WIN_NAME "Source Image"
#define PROC_WIN_NAME   "Processed Image"

int main(int argc, const char** argv)
{
	// Create a frame where components will be rendered to.
	cv::Mat frame = cv::Mat(200, 500, CV_8UC3, cv::Scalar(49, 52, 49));
	cv::Mat srcImg = cv::imread("Z:/sclinWorkDirectory/projects/TestingImages/lena_gray_512.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat procImg = cv::Mat(100, 100, CV_8UC1);

	// Processing parameter
	int width = 3;
	int height = 3;

	// Initialize procImg
	cv::blur(srcImg, procImg, cv::Size(width, height));

	// Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
	const cv::String windows[] = {WINDOW_NAME, SOURCE_WIN_NAME, PROC_WIN_NAME};
	cvui::init(windows, 3);

	while (true) {
		// Fill the frame with a nice color
		frame = cv::Scalar(49, 52, 49);

		// Render UI components to the frame
		cvui::beginColumn(frame, 110, 0, -1, -1, 6);
		//cvui::text(frame, 110, 40, "Hello, world!");
		//cvui::trackbar(frame, 110, 80, 220, &width, (int)3, (int)50, 1);
		//cvui::trackbar(frame, 110, 130, 220, &height, (int)3, (int)50, 1);
		cvui::text("Using blur to test cvui!");
		cvui::space(5);
		cvui::text("Kernel Width:");
		cvui::space(5);
		cvui::trackbar(220, &width, (int)3, (int)50, 1, "%.1Lf", cvui::TRACKBAR_DISCRETE, (int)1);
		cvui::space(5);
		cvui::text("Kernel Height:");
		cvui::space(5);
		cvui::trackbar(220, &height, (int)3, (int)50, 1);

		cv::blur(srcImg, procImg, cv::Size(width, height));

		// Update cvui stuff and show everything on the screen
		cvui::endColumn();
		cvui::update();
		cvui::imshow(SOURCE_WIN_NAME, srcImg);
		cvui::imshow(PROC_WIN_NAME, procImg);
		cvui::imshow(WINDOW_NAME, frame);

		if (cv::waitKey(20) == 27) {
			break;
		}
	}
	return EXIT_SUCCESS;
}