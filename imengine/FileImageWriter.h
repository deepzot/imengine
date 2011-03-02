// Created 17-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_FILE_IMAGE_WRITER
#define IMENGINE_FILE_IMAGE_WRITER

#include "imengine/AbsImageWriter.h"

#include <string>

namespace imengine {
    // Writes pixel values to the named file (or else stdout) with one line per row
	class FileImageWriter : public AbsImageWriter {
	public:
		FileImageWriter(std::string const &filename = "");
		virtual ~FileImageWriter();
        virtual void open(int size, double scale);
        virtual void write(int x, int y, double value);
        virtual void close();
	private:
        std::string _filename;
        std::ostream *_os;
        int _lastX;
	}; // FileImageWriter
} // imengine

#endif // IMENGINE_FILE_IMAGE_WRITER
