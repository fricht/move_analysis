#include <opencv4/opencv2/opencv.hpp>
#include <iostream>


struct {
    bool medium = true; // accumulate the two images (gray color when idle)
    bool unicolor = false; // grayscale output
} flags;


void process_frame(cv::Mat &, cv::Mat &, cv::VideoWriter &);


int main(int argc, char * argv[]) {
    if (argc < 2) {
        std::cout << "missing input file" << std::endl;
        std::cout << "usage : " << argv[0] << " <path/to/video>" << std::endl;
        return EXIT_FAILURE;
    }
    // flags
    std::string filepath = argv[1]; // change this
    std::string out_filepath = filepath + ".moves.mp4";
    bool preview = true; // display preview after computing
    bool no_progress = false;
    flags.medium = true;
    flags.unicolor = false;
    int frame_shift = 10;
    // TODO : analyse flags
    filepath = std::string(argv[1]);

    cv::VideoCapture video(filepath);
    cv::VideoCapture back_video(filepath);
    cv::Size video_size = cv::Size(video.get(cv::CAP_PROP_FRAME_WIDTH), video.get(cv::CAP_PROP_FRAME_HEIGHT));
    cv::VideoWriter output_video(out_filepath, video.get(cv::CAP_PROP_FOURCC), video.get(cv::CAP_PROP_FPS), video_size);

    if (!video.isOpened() || !back_video.isOpened()) {
        std::cout << "Error reading " << filepath << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Processing..." << std::endl;

    int total_frame_count = video.get(cv::CAP_PROP_FRAME_COUNT);
    uint frame_count;
    cv::Mat old_frame;
    cv::Mat current_frame;
    process_frame(old_frame, current_frame, output_video);
    std::cout << frame_count << std::endl;
    for (;;) { // while true loop
        frame_count++;
        if (!no_progress) {std::cout << frame_count << " / " << total_frame_count << std::endl;}
        video.read(current_frame);
        printf("0");
        if (current_frame.empty()) {
            break;
        }
        printf("01");
        if (frame_count > frame_shift) {
            back_video.read(old_frame);
        }
        printf("012");
        process_frame(old_frame, current_frame, output_video);
    }
    // release everything
    video.release();
    back_video.release();
    std::cout << "done : " << out_filepath << std::endl;
    output_video.release();
};


void process_frame(cv::Mat & _old_frame, cv::Mat & current_frame, cv::VideoWriter & video) {
    cv::Mat frame(current_frame.rows, current_frame.cols, current_frame.type());
    cv::Mat old_frame(current_frame.rows, current_frame.cols, current_frame.type());
    cv::bitwise_not(_old_frame, old_frame);
    for (uint i = 0; i < current_frame.rows; i++) {
        for (uint j = 0; j < current_frame.cols; j++) {
            //std::cout << i << " , " << j << std::endl;
            frame.at<cv::Vec3b>(i, j)[0] = (old_frame.at<cv::Vec3b>(i, j)[0] + current_frame.at<cv::Vec3b>(i, j)[0]) / 2;
            frame.at<cv::Vec3b>(i, j)[1] = (old_frame.at<cv::Vec3b>(i, j)[1] + current_frame.at<cv::Vec3b>(i, j)[1]) / 2;
            frame.at<cv::Vec3b>(i, j)[2] = (old_frame.at<cv::Vec3b>(i, j)[2] + current_frame.at<cv::Vec3b>(i, j)[2]) / 2;
        }
    }
    video.write(frame);
};
