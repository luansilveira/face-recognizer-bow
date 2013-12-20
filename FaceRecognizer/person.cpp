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

    fs << "ID" << id_;
    fs << "Name" << name_;
    fs << "Images" << "[";

    BOOST_FOREACH(cv::Mat image, images_)
    {
        fs << image ;
    }

    fs << "]";

}

void Person::showImages()
{
    cv::namedWindow("Images");

    BOOST_FOREACH(cv::Mat image,images)
    {
        cv::imshow("Images",image);
        cv::waitKey(250); // wait 250 ms
    }
}

//! Read serialization for this class
void Person::read(const cv::FileNode& node){

    node["ID"] >> id_;
    node["Name"] >> name_;

    node["Images"] >> images_;

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
    out << "{ id = " << p.id_ << ", ";
    out << "Name = " << p.name_ << "}";
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
