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
