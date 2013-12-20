#ifndef BOW_H
#define BOW_H

//! OpenCV Include
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/opencv.hpp>

#include <ros/ros.h>

#include <people.h>

//! Vector Include
#include <vector>

using namespace std;

namespace dolphin_slam
{

class BoW
{
public:
    BoW();
    ~BoW();

    void readDictionary(const char *path);
    cv::Mat createHistogram(const cv::Mat &image);

    void setThreshold(int threshold);
    int getThreshold();


    void setNumberOfGroups(int number_of_groups);

    void train(People *people);

private:
    int threshold_;
    int number_of_groups_;

    cv::Mat dictionary_;
    cv::Mat histogram_;

    vector<cv::KeyPoint> keypts_;

    cv::SurfFeatureDetector *detector_;
    cv::BOWImgDescriptorExtractor *bowDE_;
    cv::Ptr<cv::DescriptorExtractor> extractor_;
    cv::Ptr<cv::DescriptorMatcher> matcher_;

};

} // namespace

#endif // BOW_H
