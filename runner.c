#include "seamcarving.c"

int main()
{
    struct rgb_img* input_im;
    struct rgb_img* output_im;
    read_in_img(&input_im, "3x4.bin");
    calc_energy(input_im, &output_im);
    write_img(output_im, "3x4Energy.bin");
    return 0;
}