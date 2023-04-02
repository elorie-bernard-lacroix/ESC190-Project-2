#include"seamcarving.h"

void calc_energy(struct rgb_img *im, struct rgb_img **grad)
/*
Compute the dual-gradient energy function and place it in the struct rgb_img *grad.
*/
{

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