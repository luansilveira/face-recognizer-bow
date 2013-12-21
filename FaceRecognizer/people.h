#ifndef PEOPLE_H
#define PEOPLE_H

#include "person.h"
#include <vector>
#include <string>

#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>

#include <iostream>
#include <bag_of_words.h>

#include <boost/foreach.hpp>
#include <QString>
#include <QTextBrowser>



class People
{

public:
    People();

    void setLog(QTextBrowser *log);

    void testImages();

    int addNewPerson(std::string name);

    bool addImage(int person_id,std::string filename);

    void addTestImages(std::string filename);

    void write(cv::FileStorage& fs) const ;                       //Write serialization for this class

    void read(const cv::FileNode& node);                          //Read serialization for this class

    // This function will print our custom class to the console
    friend std::ostream& operator<<(std::ostream& out, const People& p);

    void getNames(std::vector<std::string> &names);


    void getImages(std::vector <cv::Mat> &images );

    void trainDatabase();

    bool findMatch(cv::Mat & image, int & person_id, std::string &name, double &correlation);

    void showDatabase();

private:

    std::vector<Person> people_;

    std::vector<cv::Mat> test_images_;

    BoW bag_of_words_;

    double match_threshold_;

    QTextBrowser *log_;


signals:
    void writeLog(QString message);

};


//These write and read functions must be defined for the serialization in FileStorage to work
void write(cv::FileStorage& fs, const std::string&, const People& x);
void read(const cv::FileNode& node, People& x, const People& default_value = People());



#endif // PEOPLE_H
