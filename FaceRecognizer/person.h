#ifndef PERSON_H
#define PERSON_H
#include <vector>
#include <string>

#include <opencv/cv.h>
#include <iostream>
#include <boost/foreach.hpp>
#include <opencv/highgui.h>

class Person
{
public:
    Person(int id=0,std::string name="name");

    void write(cv::FileStorage& fs) const ;                       //Write serialization for this class

    void read(const cv::FileNode& node);                          //Read serialization for this class

    // This function will print our custom class to the console
    friend std::ostream & operator << (std::ostream& out, const Person& p);

    bool addImage(const cv::Mat &img);

    std::string getName();
    void setName(const std::string &name);

private:
    std::vector< cv::Mat> images_;
    int id_;
    std::string name_;

};

//These write and read functions must be defined for the serialization in FileStorage to work
void write(cv::FileStorage& fs, const std::string&, const Person& x);
void read(const cv::FileNode& node, Person& x, const Person& default_value = Person());



#endif // PERSON_H
