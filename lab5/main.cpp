#include <opencv2/highgui/highgui.hpp>

IplImage *ac1(IplImage *image)
{
    int i = 0;
    for (int y = 0; y < image->height; y++)
    {
        uchar *ptr = (uchar *)(image->imageData +
                               y * image->widthStep);
        for (int x = 0; x < image->width; x++)
        {
            ptr[3 * x] += i;
            ptr[3 * x + 1] += i;
            ptr[3 * x + 2] += i;
        }
        i += 15;
        i %= 256;
    }
    return image;
}

int main(int argc, char *argv[])
{
    CvCapture *capture = cvCreateCameraCapture(0);
    if (!capture)
        return 0;
    while (1)
    {
        IplImage *frame = cvQueryFrame(capture);
        if (!frame)
            break;
        cvShowImage("test", ac1(cvCloneImage(frame)));
        char c = cvWaitKey(33);
        if (c == 27)
            break;
    }
    cvReleaseCapture(&capture);
    cvDestroyWindow("test");
}

// cmake .
// make