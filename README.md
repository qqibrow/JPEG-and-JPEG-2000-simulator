JPEG-and-JPEG-2000-simulator
============================

a program that simulating how JPEG and JPEG 2000 works

JPEG
=====


The JPEG compression process is as blow. Firstly, it converts the RGB to YCrCb color space. since human perception is less tolerant to Y compression compared to CrCb, so we can compress them differently. Secondly, we do a 8*8 block division on this image. For every block, we first do DCT then quantize it according to the quatization table. For the topleft one, we call it DC coefficient. for the rest ones, we call them AC coefficient. DC and AC coeffcient are encoded seperately because the DC coefficients are more similar to each other, so encode them tegether can reduce the entropy. Then we use a zig-zag way to iterate the block of the rest AC coefficients from lefttop to rightbottom and therefore get a sequence. Haffman code is used to compress DC coefficients. For AC coefficients, we encode them according to a Code Table. Finally, the encoder send the encoded DC coefficients, AC coefficients, and the haffman tree to the decode side.

This program only simulate the process from the block to the sequence. For example, given the input 8*8 block:

64 2 3 61 60 6 7 57

9 55 54 12 13 51 50 16

17 47 46 20 31 43 42 24

40 26 27 37 36 30 31 33

32 34 35 29 28 38 39 25

41 23 22 44 45 19 18 48

49 15 14 52 53 11 10 56

8 58 59 5 4 62 63 1

output DCT result: 

261.25  -0.344868  -1.63321  0.982125  1.24999  -1.46984  -0.676503  1.73381  
0.982125  -0.270966  -1.2832  0.771645  14.9718  -1.15485  -0.53152  1.36224  
-0.676502  0.186645  0.883883  -0.531519  -0.676498  0.795474  0.366117  -0.938326  
-1.73379  0.478354  2.26532  -1.36224  102.155  2.03874  0.938318  -2.40484  
-1.25001  2.09359  1.6332  12.0039  -1.25  14.2531  0.676498  -0.788698  
0.344881  -0.0951506  -0.450599  0.270963  102.611  -0.405517  -0.186652  0.478361  
1.6332  -0.4506  -2.13388  1.2832  1.63322  -1.92045  -0.883884  2.26532  
1.46985  -0.405529  -1.92044  1.15485  9.03066  -1.72835  -0.795475  2.03873  

output quantized result: 

16  0  0  0  0  0  0  0  
0  0  0  0  1  0  0  0  
0  0  0  0  0  0  0  0  
0  0  0  0  2  0  0  0  
0  0  0  0  0  0  0  0  
0  0  0  0  1  0  0  0  
0  0  0  0  0  0  0  0  
0  0  0  0  0  0  0  0  

the sequence:
15zeros before1
14zeros before2
14zeros before1


JPEG2000
=========

for the process of JPEG2000, please refer to the paper: Wavelets for Computer Graphics: A Primer. This program totally implemented the algorithm of Two-dimensional Haar wavelet transforms on page 4. 

input: a 8*8 block. just as the input of JPEG

transform output:
33  0  0  0  0  0  1  0  
0  0  0  0  0  0  1  0  
0  0  0  -1  4  -4  3  -4  
0  0  0  0  4  -4  4  -4  
0  0  1  1  27  -25  23  -21  
1  -1  0  1  -11  9  -4  5  
0  0  1  1  -5  7  -9  11  
0  0  0  0  21  -23  25  -27  






