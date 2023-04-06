#include"seamcarving.h"
#include<math.h>

void calc_energy(struct rgb_img *im, struct rgb_img **grad)
/*
Compute the dual-gradient energy function and place it in the struct rgb_img *grad.
*/
{
    int width, height, y, x, xp1, xm1, yp1, ym1, r_x, r_y, g_x, g_y, b_x, b_y; 
    // xp1 = 'x plus 1', xm1 = 'x minus 1' to deal with "wrapping around"
    width = im->width;
    height = im->height;
    create_img(grad, height, width); //assume **grad is null pointer?
    for(x = 0; x < width; x++){
        for(y = 0; y < height; y++){
            xp1 = x+1;
            xm1 = x-1;
            yp1 = y+1;
            ym1 = y-1;
            
            //wrapping around
            if(x == width-1) xp1 = 0; 
            if(x == 0) xm1 = (width-1);
            if(y == height-1) yp1 = 0;
            if(y == 0) ym1 = (height-1);
            
            //R_x(y, x) = (y, x+1)_red - (y, x-1)_red
            r_x = (int)get_pixel(im, y, xp1, 0) - (int)get_pixel(im, y, xm1, 0);
            g_x = (int)get_pixel(im, y, xp1, 1) - (int)get_pixel(im, y, xm1, 1);
            b_x = (int)get_pixel(im, y, xp1, 2) - (int)get_pixel(im, y, xm1, 2);

            //R_y(y, x) = (y+1, x)_red - (y-1, x)_red
            r_y = (int)get_pixel(im, yp1, x, 0)- (int)get_pixel(im, ym1, x, 0);
            g_y = (int)get_pixel(im, yp1, x, 1)- (int)get_pixel(im, ym1, x, 1);
            b_y = (int)get_pixel(im, yp1, x, 2)- (int)get_pixel(im, ym1, x, 2);

            //put it together: \delta^{2}_{x} \(y, x\) = (r_x)^2 + (b_x)^2 + (g_x)^2
            long int d2x = (r_x)*(r_x) + (b_x)*(b_x) + (g_x)*(g_x); 
            long int d2y = (r_y)*(r_y) + (b_y)*(b_y) + (g_y)*(g_y); 
            //uint8_t will definitely not work here for d2x; using int instead. Also too lazy too get pow() function from math library... maybe I should not be lazy...
            double energy = sqrt((double)(d2x + d2y)); //the irony of using the math.h library on the line directly below...

            uint8_t energy_to_store = (uint8_t)(energy/10.0);
            set_pixel(*grad, y, x, energy_to_store, energy_to_store, energy_to_store);
        }
    }
    
    

}

void dynamic_seam(struct rgb_img *grad, double **best_arr)
/*
Allocates and computes the dunamic array *best_arr. 
(*best_arr)[i*width+j] contains the minimum cost of a seam from the top of grad to the point (i,j).
*/
{

    *best_arr = (double *)malloc(sizeof(double)*(grad->width)*(grad->height)); //allocate memory for best_arr
    int i, j, cur_min;
    i = 0;
    j = 0;
    for (i; i <  grad->height; i++){  // loop through rows

        for (j = 0; j < grad->width; j++){ // loop through columns

            if (i == 0){  // the cost of the first row is just the energy of the pixel
                (*best_arr)[j] = (double)get_pixel(grad, i, j, 0);
            }
            else{  // the cost of the rest of the rows is the energy of the pixel + the minimum cost of the previous row

                if (j == 0){  // if we are at the left edge, we only need to consider the pixel above and to the right
                    if ((*best_arr)[(i-1)*grad->width+j+1] > (*best_arr)[(i-1)*grad->width+j]){
                        cur_min = (*best_arr)[(i-1)*grad->width+j];
                    }
                    else{
                        cur_min = (*best_arr)[(i-1)*grad->width+j+1];
                    }
                }
                else if (j == grad->width-1){  // if we are at the right edge, we only need to consider the pixel above and to the left
                    if ((*best_arr)[(i-1)*grad->width+j-1] > (*best_arr)[(i-1)*grad->width+j]){
                        cur_min = (*best_arr)[(i-1)*grad->width+j];
                    }
                    else{
                        cur_min = (*best_arr)[(i-1)*grad->width+j-1];
                    }
                }
                else{  // otherwise, we need to consider the pixel to the left, the pixel to the right, and the pixel directly above
                    cur_min = (*best_arr)[(i-1)*grad->width+j-1];
                    if ((*best_arr)[(i-1)*grad->width+j] < cur_min){
                        cur_min = (*best_arr)[(i-1)*grad->width+j];
                    }
                    if ((*best_arr)[(i-1)*grad->width+j+1] < cur_min){
                        cur_min = (*best_arr)[(i-1)*grad->width+j+1];
                    }
                }
                (*best_arr)[i*grad->width+j] = (double)get_pixel(grad, i, j, 0) + (double)cur_min;
            }
        }
            
    }

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
    create_img(dest, src->height, src->width-1);
    for(int y = 0; y < src->height; y++){
        int offset = 0; // offset works as built in boolean; 0 means before seam, 1 means after seam
        for(int x = 0; x < src->width-1; x++){
            if (x == path[y]){
                offset = 1;
            }
            set_pixel(*dest, y, x, get_pixel(src, y, x+offset, 0), get_pixel(src, y, x+offset, 1), get_pixel(src, y, x+offset, 2));
        }
    }
}
