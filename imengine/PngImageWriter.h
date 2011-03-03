// Created 02-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_PNG_IMAGE_WRITER
#define IMENGINE_PNG_IMAGE_WRITER

#include "imengine/ArrayImageWriter.h"

#include <string>
#include <cstdio>

namespace imengine {
	class PngImageWriter : public ArrayImageWriter {
	public:
		PngImageWriter(std::string const &filename);
		virtual ~PngImageWriter();
        virtual void open(int size, double scale);
        virtual void close();
	private:
        std::string _filename;
        std::FILE *_file;
	}; // PngImageWriter
} // imengine

#endif // IMENGINE_PNG_IMAGE_WRITER
