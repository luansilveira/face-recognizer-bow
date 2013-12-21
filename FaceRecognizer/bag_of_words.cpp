#include "bag_of_words.h"


/*!
 * \brief Constructor
 */
BoW::BoW()
{

    threshold_ = 100;

    number_of_groups_ = 100;

    //! create FlannBased matcher
    matcher_ = cv::DescriptorMatcher::create("FlannBased");

    //! create SURF extractor
    extractor_ = cv::DescriptorExtractor::create("SURF");

    //! create SURF detector
    detector_ = new cv::SurfFeatureDetector(threshold_);

    //! create BoW Image Descriptor Extractor
    bowDE_ = new cv::BOWImgDescriptorExtractor(extractor_,matcher_);
}




/*!
 * \brief Destructor
 */
BoW::~BoW()
{
    //! Realease Pointers
    delete detector_;
    delete bowDE_;
}

/*!
 * \brief Set the SURF's threshold
 * \param Threshold : int
 */
void BoW::setThreshold(int threshold)
{
    //! Set threshold value
    threshold_ = threshold;


    delete detector_;
    //! Set threshold value at the SURF detector
    detector_ = new cv::SurfFeatureDetector(threshold_);
}

void BoW::setNumberOfGroups(int number_of_groups)
{
    number_of_groups_ = number_of_groups;
}

/*!
 * \brief Get the SURF's threshold
 * \return Threshold : int
 */
int BoW::getThreshold()
{
    //! Return threshold value
    return threshold_;
}

/*!
 * \brief Create Histogram from Mat
 * \param Image : Mat
 * \return Histogram : Mat
 */
cv::Mat BoW::createHistogram(const cv::Mat &image)
{
    cv::Mat image_keypoints;
    cv::Mat histogram;
    //! Detect SURF Features in the image
    detector_->detect(image, keypts_);

    //! Create the Image's Histogram
    bowDE_->compute(image,keypts_,histogram);

    cv::drawKeypoints( image, keypts_, image_keypoints, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT );

    //! Return histogram
    return histogram;
}


void BoW::train(std::vector <cv::Mat> &images)
{

    cv::TermCriteria tc(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,10,1.0);
    int retries = 1;
    int flags = cv::KMEANS_PP_CENTERS;

    std::vector<cv::KeyPoint> keypoints;


    /// DICIONARIOS DE TAMANHO: SE NECESSARIO PODEM CRIAR OUTROS, LEMBRAR DE ADICIONAR NOVA CLASSE BOWKMeansTrainer E TAMBÉM USAR O MÉTODO .cluster, ALÉM DE SALVAR O DICIONARIO NO FILESTORAGE
    cv::BOWKMeansTrainer bowTrainer(number_of_groups_, tc, retries, flags);

    cv::Mat features_image;

    BOOST_FOREACH(cv::Mat image, images)
    {
        //cv::imshow("Image",image);
        //cv::waitKey(250);
        detector_->detect(image, keypoints);
        extractor_->compute(image, keypoints, features_image);

        if(!features_image.empty()){
            bowTrainer.add(features_image);
        }
        else
        {
            cout << "features_image empty" << endl;
        }
    }


    dictionary_ = bowTrainer.cluster();

    bowDE_->setVocabulary(dictionary_);

}

cv::Mat BoW::computeMeanHistogram(std::vector <cv::Mat> images)
{
    std::vector <cv::Mat> histograms;
    cv::Mat mean_histogram;


    BOOST_FOREACH(cv::Mat image, images)
    {
        histograms.push_back(createHistogram(image));

   }

    mean_histogram = histograms[0].clone();


    for(int i=1;i<histograms.size();i++)
    {
        mean_histogram += histograms[i];
    }
    mean_histogram /= histograms.size();

    return mean_histogram;
}


/*!
 * \brief Read the BoW's Dictionary
 * \param Path to dictionary : const char*
 */
void BoW::readDictionary(const char* path)
{
    //! Create FileStorage
    cv::FileStorage fs;

    //! Open File especified in the path
    if(fs.open(path, cv::FileStorage::READ))
    {
        cout <<"File sucessful opened: " << path << endl;
    }
    else
    {
        cout <<"Could not open the file: " << path << endl;
    }

    //! Read the dictionary from File
    fs["Dicionario"] >> dictionary_;
    //! Release the File
    fs.release();

    //! Set BoW Vocabulary
    bowDE_->setVocabulary(dictionary_);
}


//! Write serialization for this class
void BoW::write(cv::FileStorage& fs) const{

    fs << "{";
    fs << "number_of_groups" << number_of_groups_;
    fs << "features_threshold" << threshold_;
    fs << "dictionary" << dictionary_;
    fs << "}";

}

void BoW::read(const cv::FileNode &node)
{
    node["number_of_groups"] >> number_of_groups_;
    node["features_threshold"] >> threshold_;

    node["dictionary"] >> dictionary_;

    bowDE_->setVocabulary(dictionary_);
    setThreshold(threshold_);

}


//These write and read functions must be defined for the serialization in FileStorage to work
void write(cv::FileStorage& fs, const std::string&, const BoW& bow)
{
    bow.write(fs);
}

void read(const cv::FileNode& node, BoW& bow, const BoW& default_value)
{
    bow.read(node);
}

