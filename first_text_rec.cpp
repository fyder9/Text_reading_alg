#include <string>
#include <stdio.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{	//check for arguments
    if (argc != 2) {
        printf("usage: firts_text_rec.out <Image_Path>\n");
        return -1;
    }
	//getting image with opencv
    Mat image;
    image = imread(argv[1], IMREAD_COLOR);
    if (!image.data) {
        printf("No image data \n");
        return -1;
    }
	//initialize tesseract object
    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
	//initialize tesseract to use english and its deeplearning algorithm	
    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
	//setting tesseract page segmentation mode
    ocr->SetPageSegMode(tesseract::PSM_AUTO); 
	//set the image for tesseract
    ocr->SetImage(image.data, image.cols, image.rows, 3, image.step);
	//get the output text
string outText = string(ocr->GetUTF8Text());
	//output text to the console 
    cout << outText;
	//erase tesseract object
    ocr->End();


    waitKey(0);
    return 0;
}

