#include "people.h"

using std::cout;

People::People()
{

}

void People::getNames(std::vector<std::string> &names)
{
    BOOST_FOREACH(Person p, people){
        names.push_back(p.getName());
    }
}

int People::addNewPerson(std::string name)
{
    int new_id = people.size();
    Person p(new_id,name);
    people.push_back(p);

    return new_id;
}

bool People::addImage(int person_id, std::string filename)
{
    cv::Mat image;
    if(person_id > 0 && person_id < people.size()){
        image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
        return people[person_id].addImage(image);
    }
    else
    {
        cout << "Invalid ID";
        return false;
    }

}




//! Write serialization for this class
void People::write(cv::FileStorage& fs) const{

    fs  << "People" << "[";
    BOOST_FOREACH(Person p, people)
    {
        p.write(fs);
    }
    fs << "]";

}

//! Read serialization for this class
void People::read(const cv::FileNode& node){

    //cv::FileNode people_fn = node["People"];m'

    cv::FileNode fn = node["People"];
    cv::FileNodeIterator it = fn.begin(), it_end = fn.end();

    for(; it != it_end; ++it)
    {
        people.resize(people.size()+1);

        Person *p = &(people[people.size()-1]);
        p->read(*it);

    }

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
    for(int i=0;i<people.size();i++)
    {
        cout << "Person " << i;
        cout << "\tName = " << people[i].getName() << endl;
        cout << "\tNumber of Images = " << people[i].images.size() << endl;
    }

    return out;
}
