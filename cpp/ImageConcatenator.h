#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

class ImageConcatenator
{
public:
	enum class Orientation
	{
		Vertical, Horizontal
	};

	ImageConcatenator(const std::string& windowname, const Orientation orientation = Orientation::Vertical);

	void add(const cv::Mat& img);

	void show() const;

	cv::Mat getConcatenatedImg();

private:
	cv::Mat m_vis;
	std::string m_windowname;
	Orientation m_orientation;
};
