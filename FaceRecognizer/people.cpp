#include "people.h"

using std::cout;
using std::endl;

People::People()
{
    match_threshold_ = 0.2;
}

void People::setLog(QTextBrowser *log)
{
    log_ = log;
}

void People::testImages()
{
    int person_id;
    std::string name;
    double correlation;

    BOOST_FOREACH(cv::Mat image, test_images_) {
        cv::imshow("Image",image);
        if (findMatch(image,person_id,name,correlation))
        {
            log_->append("Id = " + QString::number(person_id) + " Name = " + QString::fromStdString(name) + " Correlation = " + QString::number(correlation));
            //cout << "Id = " << person_id << " Name = " << name << endl;
        }
        else
        {
            log_->append("There is no match in the database. Correlation = " + QString::number(correlation));
            //cout << "There is no match in the database" << endl;
        }
        cv::waitKey(1000);

    }
}



void People::trainDatabase()
{
    cv::Mat mean_histogram;
    std::vector<cv::Mat> images;
    getImages(images);
    bag_of_words_.train(images);

    images.clear();

    for(int i=0;i<people_.size();i++)
    {
        people_[i].getImages(images);
        mean_histogram = bag_of_words_.computeMeanHistogram(images);

        people_[i].setMeanHistogram(mean_histogram);
    }

}

bool People::findMatch(cv::Mat &image, int &person_id, string &name, double &max_correlation)
{
    cv::Mat histogram = bag_of_words_.createHistogram(image);
    int index;
    double correlation;

    max_correlation = 0;

    for(int i=0;i<people_.size();i++)
    {
        correlation = cv::compareHist(histogram,people_[i].getMeanHistogram(),CV_COMP_CORREL);
        if(correlation > max_correlation)
        {
            max_correlation = correlation;
            index = i;
        }
    }

    //cout << "Max correlation = " << max_correlation << endl;

    if(max_correlation > match_threshold_)
    {
        person_id = index;
        name = people_[index].getName();
        return true;
    }else
    {
        return false;
    }

    return false;
}

void People::getNames(std::vector<std::string> &names)
{
    BOOST_FOREACH(Person p, people_){
        names.push_back(p.getName());
    }
}

void People::getImages(std::vector<cv::Mat> &images)
{
    std::vector <cv::Mat> images_aux;

    images.reserve(100);

    BOOST_FOREACH(Person p,people_)
    {
        p.getImages(images_aux);
        BOOST_FOREACH(cv::Mat image,images_aux)
        {
            images.push_back(image);
        }
    }
}

int People::addNewPerson(std::string name)
{
    int new_id = people_.size();
    Person p(new_id,name);
    people_.push_back(p);

    return new_id;
}

bool People::addImage(int person_id, std::string filename)
{
    cv::Mat image;
    if(person_id >= 0 && person_id < people_.size()){
        image = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);

        //cv::resize(image,image,cv::Size(320,243));

        return people_[person_id].addImage(image);
    }
    else
    {
        cout << "Invalid ID";
        return false;
    }

}

void People::addTestImages(string filename)
{

    cv::Mat image = cv::imread(filename,CV_LOAD_IMAGE_GRAYSCALE);

    //cv::resize(image,image,cv::Size(320,243));


    test_images_.push_back(image);
}

void People::showDatabase()
{
    std::vector<cv::Mat> images;

    BOOST_FOREACH(Person p,people_)
    {
        images.clear();
        p.getImages(images);
        BOOST_FOREACH(cv::Mat image,images)
        {
            cv::imshow("Image",image);
            cv::waitKey(250);
        }
    }
}

//! Write serialization for this class
void People::write(cv::FileStorage& fs) const{

    fs << "{";

    fs  << "people" << "[";
    BOOST_FOREACH(Person p, people_)
    {
        fs << p;
    }
    fs << "]";
    fs << "bag_of_words" << bag_of_words_;

    fs << "test_images" << "[";
    BOOST_FOREACH(cv::Mat im, test_images_)
    {
        fs << im;
    }
    fs << "]";
    fs << "}";


}

//! Read serialization for this class
void People::read(const cv::FileNode& node){

    cv::Mat image;
    cv::FileNode fn = node["people"];
    cv::FileNodeIterator it = fn.begin(), it_end = fn.end();

    for(; it != it_end; ++it)
    {
        people_.resize(people_.size()+1);

        Person *p = &(people_[people_.size()-1]);
        p->read(*it);

    }
    node["bag_of_words"] >> bag_of_words_;

    node["test_images"] >> test_images_;

}




//These write and read functions must be defined for the serialization in FileStorage to work
void write(cv::FileStorage& fs, const std::string&, const People& x)
{
    x.write(fs);
}
void read(const cv::FileNode& node, People& x, const People& default_value){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

// This function will print our custom class to the console
std::ostream& operator<<(std::ostream& out, const People& p)
{
    out << "People" << endl;
    for(int i=0;i<p.people_.size();i++)
    {
        out << p.people_[i] << endl;
    }

    return out;
}
