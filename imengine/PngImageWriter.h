// Created 02-Mar-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_PNG_IMAGE_WRITER
#define IMENGINE_PNG_IMAGE_WRITER

#include "imengine/AbsImageWriter.h"

#include <string>
#include <cstdio>

namespace imengine {
	class PngImageWriter : public AbsImageWriter {
	public:
		PngImageWriter(std::string const &filename);
		virtual ~PngImageWriter();
        virtual void open(int size, double scale);
        virtual void write(int x, int y, double value);
        virtual void close();
	private:
        std::string _filename;
        std::FILE *_file;
        int _lastX;
	}; // PngImageWriter
} // imengine

#endif // IMENGINE_PNG_IMAGE_WRITER
