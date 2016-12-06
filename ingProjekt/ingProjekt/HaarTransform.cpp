#include "HaarTransform.h"


HaarTransform::HaarTransform(int maxSampleCount, cv::Size winsize) : m_sampleCount(maxSampleCount)
{
    m_eval.init(CvFeatureParams::create(0), maxSampleCount, winsize);
}


HaarTransform::~HaarTransform()
{
}

void HaarTransform::SetImages(std::vector<cv::Mat>& images, cv::Mat& labels)
{
    for (int i = 0; i < images.size(); i++)
    {
        m_eval.setImage(images[i], labels.at<int>(i),i);
    }
}

void HaarTransform::GetFeatures(cv::Mat& resultSet)
{
    resultSet = cv::Mat();
    for (int i = 0; i < m_sampleCount; i++)
    {
        cv::Mat tempMat = cv::Mat(0, 0, CV_32F);
        for (int k = 0; k < m_eval.getNumFeatures(); k++)
        {
            tempMat.push_back(m_eval(k, i));
        }
        resultSet.push_back(tempMat);
    }
}
