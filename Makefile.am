# global compile and link options
AM_CPPFLAGS = $(BOOST_CPPFLAGS)

# targets to build and install
lib_LTLIBRARIES = libimengine.la
bin_PROGRAMS = imbenchmark imgenerate imdemo imextend

# extra targets that should be built locally but not installed
noinst_PROGRAMS = imbenchmark imdemo imextend

# instructions for building each program

imgenerate_SOURCES = src/imgenerate.cc
imgenerate_DEPENDENCIES = $(lib_LIBRARIES)
imgenerate_LDADD = -lboost_program_options -L. -limengine

imbenchmark_SOURCES = src/imbenchmark.cc
imbenchmark_DEPENDENCIES = $(lib_LIBRARIES)
imbenchmark_LDADD = -L. -limengine

imdemo_SOURCES = src/imdemo.cc
imdemo_DEPENDENCIES = $(lib_LIBRARIES)
imdemo_LDADD = -L. -limengine

imextend_SOURCES = src/imextend.cc
imextend_DEPENDENCIES = $(lib_LIBRARIES)
imextend_LDADD = -L. -limengine

# instructions for building the library

libimengine_la_SOURCES = \
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

# library headers to install (nobase prefix preserves directories under bosslya)
# Anything that includes config.h should *not* be listed here.
# and is not part of the package public API.

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
