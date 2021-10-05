// print info about given Mat: type, channels, size
std::string info(const cv::Mat& mat);

// Look Up table convenience wrapper. Use an std::array as LUT (which is easy and efficient).
cv::Mat applyLUT(cv::Mat& image, const std::array<uchar, 256>& LUT);

// apply gamma correction to the given image. I^(1/gamma)
cv::Mat correctGamma(cv::Mat& I, double gamma);

// apply a real-valued float[0,1] or int[0,255] mask to the given image by multiplication.
cv::Mat applyMask(cv::Mat& image, const cv::Mat& mask);
