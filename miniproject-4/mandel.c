#include "bitmap.h"
#include <errno.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int iteration_to_color(int i, int max);
int iterations_at_point(double x, double y, int max);

struct thread_args
{
    struct bitmap *bm;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    int max;
    int threads;
    int begin;
    int end;
};

void *compute_image(struct thread_args *args)
{

    struct bitmap *bm = args->bm;
    double xmin = args->xmin;
    double xmax = args->xmax;
    double ymin = args->ymin;
    double ymax = args->ymax;
    int max = args->max;
    int threads = args->threads;

    int i, j;

    int width = bitmap_width(bm);
    int height = bitmap_height(bm);

    // For every pixel in the image...

    for (j = 0; j < height; j++)
    {

        for (i = 0; i < width; i++)
        {

            // Determine the point in x,y space for that pixel.
            double x = xmin + i * (xmax - xmin) / width;
            double y = ymin + j * (ymax - ymin) / height;

            // Compute the iterations at that point.
            int iters = iterations_at_point(x, y, max);

            // Set the pixel in the bitmap.
            bitmap_set(bm, i, j, iters);
        }
    }
}

void show_help()
{
    printf("Use: mandel [options]\n");
    printf("Where options are:\n");
    printf("-m <max>    The maximum number of iterations per point. (default=1000)\n");
    printf("-n <max>    The number of threads to complete the operation (default=1)");
    printf("-x <coord>  X coordinate of image center point. (default=0)\n");
    printf("-y <coord>  Y coordinate of image center point. (default=0)\n");
    printf("-s <scale>  Scale of the image in Mandlebrot coordinates. (default=4)\n");
    printf("-W <pixels> Width of the image in pixels. (default=500)\n");
    printf("-H <pixels> Height of the image in pixels. (default=500)\n");
    printf("-o <file>   Set output file. (default=mandel.bmp)\n");
    printf("-h          Show this help text.\n");
    printf("\nSome examples are:\n");
    printf("mandel -x -0.5 -y -0.5 -s 0.2\n");
    printf("mandel -x -.38 -y -.665 -s .05 -m 100\n");
    printf("mandel -x 0.286932 -y 0.014287 -s .0005 -m 1000\n\n");
}

int main(int argc, char *argv[])
{
    char c;

    // These are the default configuration values used
    // if no command line arguments are given.

    const char *outfile = "mandel.bmp";
    double xcenter = 0;
    double ycenter = 0;
    double scale = 4;
    int image_width = 500;
    int image_height = 500;
    int max = 1000;
    int threads = 1;

    // For each command line argument given,
    // override the appropriate configuration value.

    while ((c = getopt(argc, argv, "x:y:s:W:H:m:n:o:h")) != -1)
    {
        switch (c)
        {
        case 'x':
            xcenter = atof(optarg);
            break;
        case 'y':
            ycenter = atof(optarg);
            break;
        case 's':
            scale = atof(optarg);
            break;
        case 'W':
            image_width = atoi(optarg);
            break;
        case 'H':
            image_height = atoi(optarg);
            break;
        case 'm':
            max = atoi(optarg);
            break;
        case 'n':
            threads = atoi(optarg);
            break;
        case 'o':
            outfile = optarg;
            break;
        case 'h':
            show_help();
            exit(1);
            break;
        }
    }

    // Display the configuration of the image.
    printf("mandel: x=%lf y=%lf scale=%lf max=%d outfile=%s\n", xcenter, ycenter, scale, max, outfile);

    // Create a bitmap of the appropriate size.
    struct bitmap *bm = bitmap_create(image_width, image_height);

    // Fill it with a dark blue, for debugging
    bitmap_reset(bm, MAKE_RGBA(0, 0, 255, 0));

    // Compute the Mandelbrot image
    struct thread_args args[threads-1];
    pthread_t tid[threads];

    int rowIntervals[threads];

    // pthread_attr_t attr;
    for (int i = 0; i < threads; i++)
    {

        int rowStart = rowIntervals[i];
        int rowEnd = rowIntervals[i+1];

        args[i].bm = bm;
        args[i].xmin = xcenter - scale;
        args[i].xmax = xcenter + scale;
        args[i].ymin = ycenter - scale;
        args[i].ymax = ycenter + scale;
        args[i].max = max;
        args[i].begin = rowStart;
        args[i].end = rowEnd;

        pthread_create(&tid[i], NULL, compute_image, (void *)&args[i]);

    }

    for(int i = 0; i < threads; i++)
    {
        pthread_join(tid[i], NULL);
    }

    // Save the image in the stated file.
    if (!bitmap_save(bm, outfile))
    {
        fprintf(stderr, "mandel: couldn't write to %s: %s\n", outfile, strerror(errno));
        return 1;
    }

    return 0;
}

/*
Compute an entire Mandelbrot image, writing each point to the given bitmap.
Scale the image to the range (xmin-xmax,ymin-ymax), limiting iterations to "max"
*/

/*
Return the number of iterations at point x, y
in the Mandelbrot space, up to a maximum of max.
*/

int iterations_at_point(double x, double y, int max)
{
    double x0 = x;
    double y0 = y;

    int iter = 0;

    while ((x * x + y * y <= 4) && iter < max)
    {

        double xt = x * x - y * y + x0;
        double yt = 2 * x * y + y0;

        x = xt;
        y = yt;

        iter++;
    }

    return iteration_to_color(iter, max);
}

/*
Convert a iteration number to an RGBA color.
Here, we just scale to gray with a maximum of imax.
Modify this function to make more interesting colors.
*/

int iteration_to_color(int i, int max)
{
    int blueR = 44 * i / max;
    int blueG = 255 * i / max;
    int blueB = 234 * i / max;

    int greenR = 11 * i / max;
    int greenG = 57 * i / max;
    int greenB = 72 * i / max;

    if (i != max)
    {
        return MAKE_RGBA(blueR, blueG, blueB, 0);
    }
    else
    {
        return MAKE_RGBA(greenR, greenG, greenB, 0);
    }
}
