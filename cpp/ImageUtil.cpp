
std::string info(const cv::Mat& mat)
{
	std::string r;

	const int type = mat.type();
	const uchar depth = type & CV_MAT_DEPTH_MASK;
	const uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	r += " " + std::to_string(mat.cols) + "x" + std::to_string(mat.rows);

	return r;
}

cv::Mat applyLUT(cv::Mat& image, const std::array<uchar, 256>& LUT)
{
	const cv::Matx<uchar, 1, 256> matLUT(LUT.data());
	cv::LUT(image, matLUT, image);
	return image;
}

cv::Mat correctGamma(cv::Mat& I, double gamma)
{
	const double inverse_gamma = 1.0 / gamma;

	cv::Mat lut_matrix(1, 256, CV_8UC1);
	uchar* ptr = lut_matrix.ptr();
	for (int i = 0; i < 256; i++)
		ptr[i] = (int)(pow((double)i / 255.0, inverse_gamma) * 255.0);

	cv::LUT(I, lut_matrix, I);
	return I;
}

cv::Mat applyMask(cv::Mat& image, const cv::Mat& mask)
{
	CV_DbgAssert(image.size == mask.size);

	cv::Mat floatMask;
	if (mask.depth() == CV_32F || mask.depth() == CV_64F)
	{
		floatMask = mask;
	}
	else
	{
		mask.convertTo(floatMask, CV_32F, 1.f / 255.f);
	}

	if (image.channels() == 3 && floatMask.channels() == 1)
	{
		cv::cvtColor(floatMask, floatMask, cv::COLOR_GRAY2BGR);
	}

	image.convertTo(image, CV_32F);
	cv::multiply(image, floatMask, image);
	image.convertTo(image, CV_8U);
	return image;
}

