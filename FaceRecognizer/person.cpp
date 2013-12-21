#include "person.h"

Person::Person(int id, std::string name): id_(id), name_(name)
{

}

bool Person::addImage(const cv::Mat &img)
{
    images_.push_back(img.clone());

    return true;
}


//! Write serialization for this class
void Person::write(cv::FileStorage& fs) const{

    fs << "{";
    fs << "id" << id_;
    fs << "name" << name_;
    fs << "images" << "[";

    BOOST_FOREACH(cv::Mat image, images_)
    {
        fs << image ;
    }

    fs << "]";
    fs << "mean_histogram" << mean_histogram_;
    fs << "}";

}

void Person::showImages()
{
    cv::namedWindow("Images");

    BOOST_FOREACH(cv::Mat image,images_)
    {
        cv::imshow("Images",image);
        cv::waitKey(250); // wait 250 ms
    }
}

void Person::setMeanHistogram(cv::Mat &histogram)
{
    mean_histogram_ = histogram;
}

cv::Mat Person::getMeanHistogram()
{
    return mean_histogram_ ;
}

//! Read serialization for this class
void Person::read(const cv::FileNode& node){

    node["id"] >> id_;
    node["name"] >> name_;

    node["images"] >> images_;

    node["mean_histogram"] >> mean_histogram_;

}




//These write and read functions must be defined for the serialization in FileStorage to work
void write(cv::FileStorage& fs, const std::string&, const Person& x)
{
    x.write(fs);
}

void read(const cv::FileNode& node, Person& x, const Person& default_value){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

// This function will print our custom class to the console
std::ostream& operator<<(std::ostream& out, const Person& p)
{
    out << "Person " << p.id_;
    out << "\tName = " << p.name_ << std::endl;
    out << "\tNumber of Images = " << p.images_.size() << std::endl;

    return out;
}

std::string Person::getName()
{
    return name_;
}

void Person::setName(const std::string &name)
{
    name_ = name;
}

void Person::getImages(std::vector<cv::Mat> &images)
{
    images.resize(images_.size());
    std::copy(images_.begin(),images_.end(),images.begin());
}
