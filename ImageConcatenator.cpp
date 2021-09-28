#include "ImageConcatenator.h"


ImageConcatenator::ImageConcatenator(const std::string& windowname, const Orientation orientation /*= Orientation::Vertical*/)
	: m_windowname(windowname)
	, m_orientation(orientation)
{
}

void ImageConcatenator::add(const cv::Mat& img)
{
	if (img.empty()) return;

	cv::Mat input = img.clone();
	if (img.channels() == 1)
	{
		cv::cvtColor(input, input, cv::COLOR_GRAY2BGR);
	}

	if (m_vis.empty())
	{
		m_vis = input;
	}
	else
	{
		if (m_orientation == Orientation::Horizontal)
		{
			const int newH = m_vis.rows;
			const int newW = (newH / float(input.rows)) * input.cols;
			cv::resize(input, input, cv::Size(newW, newH));

			cv::hconcat(m_vis, input, m_vis);
		}
		else if (m_orientation == Orientation::Vertical)
		{
			const int newW = m_vis.cols;
			const int newH = (newW / float(input.cols)) * input.rows;
			cv::resize(input, input, cv::Size(newW, newH));

			cv::vconcat(m_vis, input, m_vis);
		}
	}
}

void ImageConcatenator::show() const
{
	cv::namedWindow(m_windowname, cv::WINDOW_NORMAL);
	cv::imshow(m_windowname, m_vis);
}

cv::Mat ImageConcatenator::getConcatenatedImg()
{
	return m_vis;
}

