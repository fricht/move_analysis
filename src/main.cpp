#include <opencv4/opencv2/opencv.hpp>
#include <iostream>


int main(int argc, char * argv[]) {
    if (argc < 2) {
        std::cout << "missing input file" << std::endl;
        std::cout << "usage : " << argv[0] << " <path/to/video>" << std::endl;
        return EXIT_FAILURE;
    }
    // flags
    std::string filepath;
    bool preview = true;
    int frame_shift = 10;
    // TODO : analyse flags
    filepath = std::string(argv[1]);

    cv::VideoCapture video(filepath);
    cv::VideoCapture back_video(filepath);
    if (!video.isOpened() || !back_video.isOpened()) {
        std::cout << "Error reading " << filepath << std::endl;
        return EXIT_FAILURE;
    }
    //
}
