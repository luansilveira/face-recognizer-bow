#ifndef PEOPLE_H
#define PEOPLE_H

#include "person.h"
#include <vector>
#include <string>

#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>

#include <iostream>

#include <boost/foreach.hpp>


class People
{
public:
    People();


    int addNewPerson(std::string name);

    bool addImage(int person_id,std::string filename);

    void write(cv::FileStorage& fs) const ;                       //Write serialization for this class

    void read(const cv::FileNode& node);                          //Read serialization for this class

    // This function will print our custom class to the console
    friend std::ostream& operator<<(std::ostream& out, const People& p);

    void getNames(std::vector<std::string> &names);

private:

    std::vector<Person> people;
};


//These write and read functions must be defined for the serialization in FileStorage to work
void write(cv::FileStorage& fs, const std::string&, const People& x);
void read(const cv::FileNode& node, People& x, const People& default_value = People());



#endif // PEOPLE_H
