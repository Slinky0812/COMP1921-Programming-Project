pgmEcho:
	- echoes one file into another
	- can be run using ./pgmEcho inputFile.pgm outputFile.pgm
	- can echo both ASCII and binary files
	- should print "ECHOED" if successful

pgmComp:
	- compares two pgm files to see if they're logically identical
	- can be run using ./pgmComp inputFile.pgm outputFile.pgm
	- can compare ASCII files together and binary files together
	- shoudl print "IDENTICAL" if logically equivalent or "DIFFERENT" if not

pgma2b:
	- converts an ASCII file into binary
	- can be run using ./pgma2b inputFile.pgm outputFile.pgm
	- should print "CONVERTED" if successful

pgmb2a:
	- converts a binary file into ASCII
	- can be run using ./pgmb2a inputFile.pgm outputFile.pgm
	- should print "CONVERTED" if successful

pgmReduce:
	- reduces a file's size by a given factor
	- can be run using ./pgmReduce inputFile.pgm reduction_factor outputFile.pgm
	- can reduce both ASCII and binary files
	- should print "REDUCED" if successful

pgmTile:
	- divides a file into smaller files with a given factor
	- can be run using ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm
	- can divide both ASCII and binary files
	- should print "TILED" if successful

pgmAssemble:
	- creates a large image with a given width and height out of several given smaller images
	- can be run using ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+
	- can assemble both ASCII and binary files
	- should print "ASSEMBLED" if successful
