#include "seamcarving.c"

int main()
{
    struct rgb_img* input_im;
    struct rgb_img* output_im;
    read_in_img(&input_im, "HJoceanSmall.bin");
    calc_energy(input_im, &output_im);
    write_img(output_im, "HJoceanSmallEnergy.bin");
    return 0;
}