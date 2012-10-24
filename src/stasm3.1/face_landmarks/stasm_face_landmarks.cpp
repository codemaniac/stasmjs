#include <stdio.h>

#include "cv.h"
#include "highgui.h"
#include "stasm_min.hpp"

int main (void)
{
    const char *image_name = "../data/test-image.jpg";
    IplImage *img = cvLoadImage(image_name, CV_LOAD_IMAGE_COLOR);
    if(img == NULL) {
        printf("Error: Cannot open %s\n", image_name);
        return -1;
    }
    // sanity checks (assumes imageData is vector of b,r,g bytes)
    if(img->nChannels != 3 || img->depth != IPL_DEPTH_8U ||
            img->origin != 0 || img->widthStep != 3 * img->width) {
        printf("Error: %s is an unrecognized image type\n", image_name);
        return -1;
    }
    // locate the facial landmarks with stasm
    int nlandmarks;
    int landmarks[500]; // space for x,y coords of up to 250 landmarks
    AsmSearch(&nlandmarks, landmarks,
                 image_name, img->imageData, img->width, img->height,
                 1 /* is_color */, NULL /* conf_file0 */, NULL /* conf_file1 */);
    if (nlandmarks == 0) {
        printf("\nError: Cannot locate landmarks in %s\n", image_name);
        return -1;
    }

    printf("landmarks:\n");
    for (int i = 0; i < nlandmarks; i++)
        printf("%3d: %4d %4d\n", i, landmarks[2 * i], landmarks[2 * i + 1]);
    return 0;
}
