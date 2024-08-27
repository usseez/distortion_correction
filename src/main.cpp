#include <stdio.h>
#include <iostream>
#include <fstream>
#include "opencv2/core/core.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc.hpp"
#include "../include/distortioncorrection.h"//확장자가 다르다는 것을 알려줘야함 매크로로 정의?를 하면됨



//#include "EdgeDetection.h"
// yuv가 input인가...? 그럼 거기서 y field만 받는 방법은.....

//unsigned char inputimage[IMAGEHEIGHT * IMAGEWIDTH * CHANNEL];
//unsigned char bgrimage[IMAGEHEIGHT * IMAGEWIDTH * CHANNEL];
//unsigned char yuvimage[IMAGEHEIGHT * IMAGEWIDTH * CHANNEL];
unsigned char inputbuffer[IMAGEWIDTH * IMAGEHEIGHT * (CHANNEL)];
unsigned char outbuffer[IMAGEWIDTH * IMAGEHEIGHT * (CHANNEL + 1)];

cv::Mat outimage(IMAGEHEIGHT, IMAGEWIDTH, CV_8UC3);


//home/jisu/cstudy/imageoverlay/image/lena.bmpdata2buffer
int data2buffer(cv::Mat image, unsigned char* inputbuffer);
int check_image_exist(cv::Mat image);
void displayimage(const std::string& name, cv::Mat outbuffer);
void createMat(cv::Mat& outputMat, int height, int width, int type, unsigned char* data);
void saveArrayToBinaryFile(const std::string& filePath, unsigned char* data, size_t dataSize);

int main(void) 
{

	inputbuffer[IMAGEHEIGHT * IMAGEWIDTH * CHANNEL];
	//read the image
	cv::Mat image = cv::imread("/mnt/d/cstudy/distortion_correction/image/20240819163408.bmp", 0);
	
	check_image_exist(image);
	data2buffer(image, inputbuffer);




    //main process
    distortion_correction(inputbuffer, outbuffer);


	//buffer to MAT image
	createMat(outimage, IMAGEHEIGHT, IMAGEWIDTH, CV_8UC1, outbuffer);
	// show image
	displayimage("outimage", outimage);




	return 0;

}




void createMat(cv::Mat& outputMat, int height, int width, int type, unsigned char* data) 
{
    // 매개변수로 전달된 cv::Mat 객체를 초기화
    outputMat = cv::Mat(height, width, type, data);

	#if 0//buffer to MAT 3channel bgrimage
	
	for (int pixel = 0; pixel < IMAGEHEIGHT * IMAGEWIDTH * (CHANNEL) ; pixel+=3)
	{
		
		outbuffer.data[pixel] = bgrimage[pixel];
        outbuffer.data[pixel + 1] = bgrimage[pixel + 1];
        outbuffer.data[pixel + 2] = bgrimage[pixel + 2];
 	
	}
	

#endif
}





void displayimage(const std::string& name, cv::Mat outbuffer)
{

	while(1)
	{
		cv::imshow(name, outbuffer);
		cv::waitKey(0);
	}
}


int data2buffer(cv::Mat image, unsigned char* inputbuffer)
{
    check_image_exist(image);
	if (inputbuffer == NULL) return -1;
    

	for (int pixel = 0; pixel < IMAGEHEIGHT * IMAGEWIDTH * CHANNEL; pixel++)
	{
		//FIXME:segmentation fault
		inputbuffer[pixel] = image.data[pixel];
	}

	#if 0
	for (int row = 0; row < IMAGEHEIGHT; row++)
	{
		for (int col = 0; col < IMAGEWIDTH; col++)
		{
			inputbuffer[row * IMAGEWIDTH + col] = image.data[row * IMAGEWIDTH + col];
			//inputimage[row * IMAGEWIDTH + col] = img_data[row * IMAGEWIDTH + col];
			//printf("\t %d", inputimage);
		}
		//cout << "\n" << endl;
	}
	
	#endif

	
	#if 0
	 
	for (int row = 0; row < IMAGEHEIGHT; row++)
	{
		for (int col = 0; col < IMAGEWIDTH; col++)
		{
			unsigned char inputimage = img_data[row * IMAGEWIDTH + col];
			//inputimage[row * IMAGEWIDTH + col] = img_data[row * IMAGEWIDTH + col];
			printf("\t %d", inputimage);
		}
		cout << "\n" << endl;
	}
	#endif
	return 0;
	
}

int check_image_exist(cv::Mat image)
{	
	// Check if the file exists
    if (image.empty()) {
        std::cerr << "Error: Unable to open image file!!" << std::endl;
        return 1;
    }
	return 0;
}
