bin_PROGRAMS = imbenchmark imgenerate imdemo
imbenchmark_SOURCES = src/imbenchmark.cc
imgenerate_SOURCES = src/imgenerate.cc
imdemo_SOURCES = src/imdemo.cc

imbenchmark_DEPENDENCIES = $(lib_LIBRARIES)
imgenerate_DEPENDENCIES = $(lib_LIBRARIES)
imdemo_DEPENDENCIES = $(lib_LIBRARIES)

# compile and link options
LDADD = -L. -limengine

lib_LIBRARIES = libimengine.a
libimengine_a_SOURCES = \
	imengine/AbsCoordTransform.cc \
	imengine/AbsImageEngine.cc \
	imengine/AbsImageFilter.cc \
	imengine/AbsImageWriter.cc \
	imengine/AbsPixelFunction.cc \
	imengine/AbsRadialProfile.cc \
	imengine/ArrayImageWriter.cc \
	imengine/BicubicImageEngine.cc \
	imengine/BilinearImageEngine.cc \
	imengine/DataGrid.cc \
	imengine/EllipticityTransform.cc \
	imengine/PolarEllipticityTransform.cc \
	imengine/FastTransform.cc \
	imengine/FileImageWriter.cc \
	imengine/GenericPixelFunction.cc \
	imengine/IdentityTransform.cc \
	imengine/ImageEngine.cc \
	imengine/ImageResponseModel.cc \
	imengine/InterpolationData.cc \
	imengine/MidpointImageEngine.cc \
	imengine/ModelBuilder.cc \
	imengine/OversamplingImageEngine.cc \
	imengine/ResizingImageEngine.cc \
	imengine/PngImageWriter.cc \
	imengine/SilentImageWriter.cc \
	imengine/SlowTransform.cc \
	imengine/TransformData.cc \
	imengine/TransformedProfileFunction.cc \
	imengine/RuntimeError.cc \
	imengine/InvalidValue.cc \
	imengine/PixelFunctionSum.cc \
	imengine/models/DeltaFunction.cc \
	imengine/models/DiskDemo.cc \
	imengine/models/DiskProfile.cc \
	imengine/models/ExponentialProfile.cc \
	imengine/models/GaussianDemo.cc \
	imengine/models/SersicDemo.cc \
	imengine/models/GaussianProfile.cc \
	imengine/models/MoffatProfile.cc \
	imengine/models/AiryDemo.cc

nobase_include_HEADERS = \
	imengine/imengine.h \
	imengine/types.h \
	imengine/ptr_types.h \
	imengine/fftw.h \
	imengine/AbsCoordTransform.h \
	imengine/AbsImageEngine.h \
	imengine/AbsImageWriter.h \
	imengine/AbsPixelFunction.h \
	imengine/AbsRadialProfile.h \
	imengine/ArrayImageWriter.h \
	imengine/BicubicImageEngine.h \
	imengine/BilinearImageEngine.h \
	imengine/DataGrid.h \
	imengine/EllipticityTransform.h \
	imengine/PolarEllipticityTransform.h \
	imengine/FastTransform.h \
	imengine/FileImageWriter.h \
	imengine/GenericPixelFunction.h \
	imengine/IdentityTransform.h \
	imengine/ImageEngine.h \
	imengine/InterpolationData.h \
	imengine/MidpointImageEngine.h \
	imengine/ModelBuilder.h \
	imengine/PngImageWriter.h \
	imengine/SilentImageWriter.h \
	imengine/SlowTransform.h \
	imengine/TransformData.h \
	imengine/TransformedProfileFunction.h \
	imengine/OversamplingImageEngine.h \
	imengine/ResizingImageEngine.h \
	imengine/AbsImageFilter.h \
	imengine/ImageResponseModel.h \
	imengine/RuntimeError.h \
	imengine/InvalidValue.h \
	imengine/PixelFunctionSum.h \
	imengine/Observer.h \
	imengine/ObserverDelegate.h \
	imengine/models/DeltaFunction.h \
	imengine/models/DiskDemo.h \
	imengine/models/DiskProfile.h \
	imengine/models/ExponentialProfile.h \
	imengine/models/GaussianDemo.h \
	imengine/models/SersicDemo.h \
	imengine/models/GaussianProfile.h \
	imengine/models/MoffatProfile.h \
	imengine/models/AiryDemo.h

