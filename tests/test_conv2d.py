import pytest
import numpy as np
import tensorflow as tf


def conv2d(x, w):
    pass


def conv2d_multi_channel(input, w, s):

    batch, height, width, in_depth = input.shape

    stride = [s, s]
    padding = [0, 0]
    dilation = [1, 1]
    kernel_size = w.shape

    height_out = (height + 2*padding[0] - dilation[0] * (kernel_size[0]-1) - 1) // stride[0] + 1
    width_out = (width + 2*padding[1] - dilation[1] * (kernel_size[1]-1) - 1) // stride[1] + 1

    out_depth = w.shape[3]
    output = np.zeros((batch, height_out, width_out, out_depth))

    for b in range(batch):
      for k in range(out_depth):
          # For each output channel, perform 2d convolution summed across all input channels.
          for i in range(0, height_out):
              for j in range(0, width_out):
                  # Now the inner loop also works across all input channels.
                  for q in range(in_depth):
                      for di in range(kernel_size[0]):
                          for dj in range(kernel_size[1]):
                              w_element = w[di, dj, q, k]
                              ww = stride[0] * i + di
                              hh = stride[1] * j + dj
                              x = input[b, ww, hh, q]
                              output[b, i, j, k] += (x * w_element)
    return output

@pytest.mark.parametrize("w", [7, 15])
@pytest.mark.parametrize("h", [7, 15])
@pytest.mark.parametrize("stride", [1, 2])
def test_conv2d(w, h, stride):

    x = tf.random.uniform(shape=(1, w, h, 1))
    k = tf.random.uniform(shape=(3, 2, 1, 4))

    y_ref = tf.nn.conv2d(x, k, strides=stride, padding='VALID')

    y = conv2d_multi_channel(x, k, stride)

    assert y.shape == y_ref.shape
    assert np.allclose(y, y_ref)

    
# @pytest.mark.parametrize("x", [0, 1])
# @pytest.mark.parametrize("y", [2, 3])
# def test_foo(x, y):
#     assert x == y
