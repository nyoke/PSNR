#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"

double psnr(cv::Mat img1, cv::Mat img2)
{
	cv::Mat img1_gray, img2_gray;
	cv::Mat img1_16s, img2_16s;
	cv::Scalar s;
	double mse, psnr;

	// グレースケールに変換
	cv::cvtColor(img1, img1_gray, CV_BGR2GRAY);
	cv::cvtColor(img2, img2_gray, CV_BGR2GRAY);

	//符号有り16bitに変換
	img1_gray.convertTo(img1_16s, CV_16S);
	img2_gray.convertTo(img2_16s, CV_16S);

	// MSE, PSNR算出
	img1_16s -= img2_16s;
	s = sum(img1_16s.mul(img1_16s));
	mse = s[0]/img1_16s.rows/img1_16s.cols;
	psnr = 10*log10(255*255/mse);

	return psnr;
}

int main(int argc, char* argv[]) {

	//原画像と処理画像を読み込む．
	cv::Mat src = cv::imread(argv[1]);
	cv::Mat dst = cv::imread(argv[2]);

	std::cout << psnr(src, dst) << std::endl;

	return 0;
}
