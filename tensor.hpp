
#pragma once

class foo {
public:
        foo() {}

};


class tensor
{
public:
        tensor()
                {

                }

        tensor(float *data, unsigned int *sizes, unsigned int *strides)
                {
                        this->pData = data;

                        for (int i=0; i<4; i++)
                        {
                                this->sizes[i] = sizes[i];
                                this->strides[i] = strides[i];
                        }
                }


        void set(float v, unsigned b, unsigned w, unsigned h, unsigned d) {}
        float get(unsigned b, unsigned w, unsigned h, unsigned d) {}

        unsigned size(unsigned d)
                {
                        return sizes[d];
                }
private:
        float *pData;
        unsigned strides[4];
        unsigned sizes[4];
};
