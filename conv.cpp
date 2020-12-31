
#include "tensor.hpp"

class Conv2d {
    public:

        Conv2d() {}

        void GetOutputShape() {}

        void Process() {}
};

void conv2d(tensor &outp, tensor &inp, tensor &w)
{
    const unsigned stride[2] {1, 1};
    const unsigned padding[2] {0, 0};
    const unsigned dilation[2] {1, 1};

    const unsigned kernel_size[2] {w.size(0), w.size(1)};

    const unsigned batch = inp.size(0); //TODO: check sizes order
    const unsigned width = inp.size(0); //TODO: check sizes order
    const unsigned height = inp.size(0); //TODO: check sizes order
    const unsigned in_depth = inp.size(0); //TODO: check sizes order

    const unsigned height_out = (height + 2*padding[0] - dilation[0] * (w.size(0)-1)-1) / stride[0] + 1;
    const unsigned width_out = (width + 2*padding[1] - dilation[1] * (w.size(1)-1)-1) / stride[1] + 1;

    unsigned out_depth = w.size(3);

    //TODO: init outp here

    for (unsigned b = 0; b < batch; b++) {
        for (unsigned k = 0; k < out_depth; k++) {
            for (unsigned i = 0; i < height_out; i++) {
                for (unsigned j = 0; j < width_out; j++) {
                    for (unsigned q = 0; q < in_depth; q++) {
                        for (unsigned di = 0; di < kernel_size[0]; di++) {
                            for (unsigned dj = 0; dj < kernel_size[1]; dj++) {
                                float w_element = w.get(di, dj, q, k);
                                unsigned ww = stride[0] * i + di;
                                unsigned hh = stride[1] * j + dj;
                                float x = inp.get(b, ww, hh, q);
                                float y = outp.get(b, i, j, k);
                                y += w_element * x;
                                outp.set(y, b, i, j, k);
                            }
                        }
                    }
                }
            }
        }
    }

}

    /* batch, height, width, in_depth = input.shape */

    /* stride = [1, 1] */
    /* padding = [0, 0] */
    /* dilation = [1, 1] */
    /* kernel_size = kernel.shape */

    /* height_out = (height + 2*padding[0] - dilation[0] * (kernel_size[0]-1) - 1) // stride[0] + 1 */
    /* width_out = (height + 2*padding[1] - dilation[1] * (kernel_size[1]-1) - 1) // stride[1] + 1 */

    /* out_depth = w.shape[3] */
    /* output = np.zeros((batch, height_out, width_out, out_depth)) */

    /* for b in range(batch): */
    /*   for k in range(out_depth): */
    /*       # For each output channel, perform 2d convolution summed across all input channels. */
    /*       for i in range(0, height_out): */
    /*           for j in range(0, width_out): */
    /*               # Now the inner loop also works across all input channels. */
    /*               for q in range(in_depth): */
    /*                   for di in range(kernel_size[0]): */
    /*                       for dj in range(kernel_size[1]): */
    /*                           w_element = w[di, dj, q, k] */
    /*                           ww = stride[0] * i + di */
    /*                           hh = stride[1] * j + dj */
    /*                           x = input[b, ww, hh, q] */
    /*                           output[b, i, j, k] += (x * w_element) */
