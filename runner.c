#include "seamcarving.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    struct rgb_img* input_im;
    struct rgb_img* output_im;
    read_in_img(&input_im, "3x4.bin");
    calc_energy(input_im, &output_im);
    write_img(output_im, "3x4Energy.bin");

    double** best_arr = (double**)malloc(sizeof(double*));
    dynamic_seam(output_im, best_arr);
    
    // print best array
    for (int i = 0; i < output_im->height; i++){
        for (int j = 0; j < output_im->width; j++){
            printf("%f ", (*best_arr)[i*(output_im->width)+j]);
        }
        printf("\n");
    }
    return 0;
}