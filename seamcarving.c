#include"seamcarving.h"

void calc_energy(struct rgb_img *im, struct rgb_img **grad)
/*
Compute the dual-gradient energy function and place it in the struct rgb_img *grad.
*/
{
int y, x, xp1, xm1, yp1, ym1;// xp1 = 'x plus 1', xm1 = 'x minus 1' to deal with "wrapping around"
uint8_t r_x, r_y, g_x, g_y, b_x, b_y; 
//R_x(y, x) = (y, x+1)_red - (y, x-1)_red
r_x = get_pixel(im, y, xp1, 0) - get_pixel(im, y, xm1, 0);
g_x = get_pixel(im, y, xp1, 1) - get_pixel(im, y, xm1, 0);
b_x = get_pixel(im, y, xp1, 2) - get_pixel(im, y, xm1, 0);

//R_y(y, x) = (y+1, x)_red - (y-1, x)_red
r_y = get_pixel(im, yp1, x, 0)- get_pixel(im, ym1, x, 0);
g_y = get_pixel(im, yp1, x, 1)- get_pixel(im, ym1, x, 0);
b_y = get_pixel(im, yp1, x, 2)- get_pixel(im, ym1, x, 0);

//put it together: \delta^{2}_{x} \(y, x\) = (r_x)^2 + (b_x)^2 + (g_x)^2
int d2x = ((int)r_x)*((int)r_x) + ((int)b_x)*((int)b_x) + ((int)g_x)*((int)g_x); 
//uint8_t will definitely not work here for d2x; using int instead. Also too lazy too get pow() function from math library... maybe I should not be lazy... gonna go eat dinner now brb lol.

}

void dynamic_seam(struct rgb_img *grad, double **best_arr)
/*
Allocates and computes the dunamic array *best_arr. 
(*best_arr)[i*width+j] contains the minimum cost of a seam from the top of grad to the point (i,j).
*/
{

}

void recover_path(double *best, int height, int width, int **path)
/*
This function allocates a path through the minimum seam as defined by the array best.
*/
{

}

void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path)
/*
The function creates the destination image, and writes to it the source image, with the seam removed.
*/
{

}