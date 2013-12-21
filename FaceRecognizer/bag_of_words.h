#ifndef BOW_H
#define BOW_H

//! OpenCV Include
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/opencv.hpp>

#include <boost/foreach.hpp>

//! Vector Include
#include <vector>

using namespace std;



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

    void train(std::vector<cv::Mat> &images);

    cv::Mat computeMeanHistogram(std::vector<cv::Mat> images);

    void write(cv::FileStorage &fs) const;
    void read(const cv::FileNode& node);                          //Read serialization for this class

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


//These write and read functions must be defined for the serialization in FileStorage to work
void write(cv::FileStorage& fs, const std::string&, const BoW& x);
void read(const cv::FileNode& node, BoW& x, const BoW& default_value = BoW());




#endif // BOW_H
