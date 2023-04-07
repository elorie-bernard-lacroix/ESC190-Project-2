#include "seamcarving.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    struct rgb_img* input_im;
    struct rgb_img* output_im;
    read_in_img(&input_im, "6x5.bin");
    calc_energy(input_im, &output_im);
    write_img(output_im, "6x5Energy.bin");

    //double** best_arr = (double**)malloc(sizeof(double*));
    double* best_arr;
    dynamic_seam(output_im, &best_arr);
    
    //print best array
    for (int i = 0; i < output_im->height; i++){
        for (int j = 0; j < output_im->width; j++){
            printf("%f ", (best_arr)[i*(output_im->width)+j]);
        }
        printf("\n");
    }

    int *path;
    recover_path(best_arr, output_im->height, output_im->width, &path);
    
    //print path
    for(int i = 0; i < output_im->height; i++){
        printf(" %d,", path[i]);
    }

    struct rgb_img* seamcut;
    remove_seam(input_im, &seamcut, path);

    for(int i = 0; i < 3; i++){
        input_im = seamcut;
        calc_energy(input_im, &output_im);
        dynamic_seam(output_im, &best_arr);
        recover_path(best_arr, output_im->height, output_im->width, &path);
        remove_seam(input_im, &seamcut, path);
    }

    write_img(seamcut, "fingerscrossed.bin");
    return 0;
}