## Different implements of image convolution

#### The implemented flavors so far:
- Sequential
- Coarse-grained Non-SVM without loop unrolling.
- Coarse-grained SVM without loop unrolling.
- Coarse-grained Non-SVM with loop unrolling.
- Coarse-grained SVM with loop unrolling.

Some clarifiactions:
- **Coarse-grained** means that image boundaries are handeled entirly
on the host while inner region is handeled by the device.
- **Non-SVM** means that collaboration between the device and host is
done using OpenCL regular memory buffers (cl_mem).
- **SVM** means that collaboration between the device and host is
done using opecl SVM buffer objects.
- **With/out loop unrolling** indicates whether loops in the kernel
implementation is urolled or not (to test performance gains from
elemenating branching entirly in kernels).

All these implementations can be found in main.cpp file!