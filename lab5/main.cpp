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

#include <stdint.h>

int main(int argc, char *argv[])
{
    union ticks {
        uint64_t t64;
        struct s32
        {
            uint32_t th, tl;
        } t32;
    } start, end;
    double cpu_Hz = 2.1e9;
    long long total_clocks = 0;
    long long total_frames = 0;

    CvCapture *capture = cvCreateCameraCapture(0);
    if (!capture)
        return 0;
    while (1)
    {
        IplImage *frame = cvQueryFrame(capture);
        if (!frame)
            break;

        total_frames++;
        asm("rdtsc\n"
            : "=a"(start.t32.th), "=d"(start.t32.tl));
        IplImage *img1 = ic1(cvCloneImage(frame));
        IplImage *img2 = ic2(cvCloneImage(frame));
        IplImage *img3 = ic3(cvCloneImage(frame));
        asm("rdtsc\n"
            : "=a"(end.t32.th), "=d"(end.t32.tl));
        total_clocks += end.t64 - start.t64;

        cvShowImage("Anonimous", img1);
        cvShowImage("3Colours", img2);
        cvShowImage("Pixelize", img3);

        cvReleaseImage(&img1);
        cvReleaseImage(&img2);
        cvReleaseImage(&img3);

        char c = cvWaitKey(33);
        if (c == 27)
            break;
    }
    cvReleaseCapture(&capture);
    cvDestroyWindow("Anonimous");
    cvDestroyWindow("3Colours");
    cvDestroyWindow("3Pixelize");
    printf("Total frames = %lli(~%lli sec), Calculation Time = %lli clocks (~%f sec)\n", total_frames, total_frames / (1000 / 33), total_clocks, total_clocks / cpu_Hz);
}

// cmake .
// make