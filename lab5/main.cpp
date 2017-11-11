#include <opencv2/highgui/highgui.hpp>

IplImage *ic1(IplImage *image)
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

IplImage *ic2(IplImage *image)
{
    for (int y = 0; y < image->height; y++)
    {
        uchar *ptr = (uchar *)(image->imageData + y * image->widthStep);
        for (int x = 0; x < image->width; x++)
        {
            if (ptr[3 * x] >= ptr[3 * x + 1])
            {
                if (ptr[3 * x] >= ptr[3 * x + 2])
                {
                    ptr[3 * x + 1] = 0;
                    ptr[3 * x + 2] = 0;
                }
                else
                {
                    ptr[3 * x] = 0;
                    ptr[3 * x + 1] = 0;
                }
            }
            else
            {
                if (ptr[3 * x + 1] >= ptr[3 * x + 2])
                {
                    ptr[3 * x] = 0;
                    ptr[3 * x + 2] = 0;
                }
                else
                {
                    ptr[3 * x] = 0;
                    ptr[3 * x + 1] = 0;
                }
            }
        }
    }
    return image;
}

#define PIXEL_SIZE 15
IplImage *ic3(IplImage *image)
{
    for (int y = 0; y < image->height; y += PIXEL_SIZE)
    {
        for (int i = 0; i < PIXEL_SIZE; i++)
        {
            uchar *ptr = (uchar *)(image->imageData + (y + i) * image->widthStep);
            for (int x = 0; x < image->width; x++)
            {
                ptr[3 * x + 0] = ptr[3 * (x / PIXEL_SIZE) * PIXEL_SIZE + 0];
                ptr[3 * x + 1] = ptr[3 * (x / PIXEL_SIZE) * PIXEL_SIZE + 1];
                ptr[3 * x + 2] = ptr[3 * (x / PIXEL_SIZE) * PIXEL_SIZE + 2];
            }
        }
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
        IplImage *img;

        img = cvCloneImage(frame);
        cvShowImage("Anonimous", ic1(img));
        cvReleaseImage(&img);

        img = cvCloneImage(frame);
        cvShowImage("3Colours", ic2(cvCloneImage(frame)));
        cvReleaseImage(&img);

        img = cvCloneImage(frame);
        cvShowImage("Pixelize", ic3(cvCloneImage(frame)));
        cvReleaseImage(&img);

        char c = cvWaitKey(33);
        if (c == 27)
            break;
    }
    cvReleaseCapture(&capture);
    cvDestroyWindow("Anonimous");
    cvDestroyWindow("3Colours");
}

// cmake .
// make