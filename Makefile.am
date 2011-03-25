bin_PROGRAMS = benchmark generate
benchmark_SOURCES = src/benchmark.cc
generate_SOURCES = src/generate.cc

benchmark_DEPENDENCIES = $(lib_LIBRARIES)
generate_DEPENDENCIES = $(lib_LIBRARIES)

# compile and link options
LDADD = -L. -limengine

lib_LIBRARIES = libimengine.a
libimengine_a_SOURCES = imengine/AbsCoordTransform.cc \
	imengine/DataGrid.cc \
	imengine/MidpointImageEngine.cc \
	imengine/models/MoffatProfile.cc \
	imengine/AbsImageEngine.cc \
	imengine/EllipticityTransform.cc \
	imengine/ModelBuilder.cc \
	imengine/PngImageWriter.cc \
	imengine/AbsImageWriter.cc \
	imengine/FastTransform.cc \
	imengine/models/DeltaFunction.cc \
	imengine/SilentImageWriter.cc \
	imengine/AbsPixelFunction.cc \
	imengine/FileImageWriter.cc \
	imengine/models/DiskDemo.cc \
	imengine/SlowTransform.cc \
	imengine/AbsRadialProfile.cc \
	imengine/GenericPixelFunction.cc \
	imengine/models/DiskProfile.cc \
	imengine/TransformData.cc \
	imengine/ArrayImageWriter.cc \
	imengine/IdentityTransform.cc \
	imengine/models/ExponentialProfile.cc \
	imengine/TransformedProfileFunction.cc \
	imengine/BicubicImageEngine.cc \
	imengine/ImageEngine.cc \
	imengine/models/GaussianDemo.cc \
	imengine/BilinearImageEngine.cc \
	imengine/InterpolationData.cc \
	imengine/models/GaussianProfile.cc

nobase_include_HEADERS = \
	imengine/imengine.h \
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
	imengine/fftw.h \
	imengine/ptr_types.h \
	imengine/types.h
