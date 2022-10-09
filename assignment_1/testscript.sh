#!/bin/sh
#
#Test script for pgmEcho, pgmComp

#Compiling pgmEcho
make all

echo ""
#Testing pgmEcho
echo "TESTING PGMECHO"

echo ""
#1. Test argument counts for correct error messages
echo "1. Testing argument count for usage message (argc == 1)"
echo "Expected outcome - Usage: ./pgmEcho inputImage.pgm outputImage.pgm"
./pgmEcho

echo ""
echo "Testing argument count for correct error message (argc == 2)"
echo "Expected outcome - ERROR: Bad Argument Count"
./pgmEcho slice0a.pgm

echo ""
#2. Test the wrong file input to see if correct error message is given (argv[1] == NULL)
echo "2. Testing wrong file input for correct error"
echo "Expected outcome - ERROR: Bad File Name (slice.pgm)"
./pgmEcho slice.pgm test1.pgm

echo ""
#3. Test the comment line to see if correct error message is given (comment line > 128 characters)
echo "3. Testing comment line for correct error"
echo "Expected outcome - ERROR: Bad Comment Line (testCommentLine.pgm)"
./pgmEcho testCommentLine.pgm test1.pgm

echo ""
#4. Test the gray value to see if correct error message is given (gray value != 255)
echo "4. Testing gray value for correct error"
echo "Expected outcome - ERROR: Bad Max Gray Value (testGrayValue.pgm)"
./pgmEcho testGrayValue.pgm test1.pgm

echo ""
#5. Test the max height to see if correct error message is given (height > 65540)
echo "5. Testing max height for correct error"
echo "Expected outcome - ERROR: Bad Dimensions (testGreaterThanMaxHeight.pgm)"
./pgmEcho testGreaterThanMaxHeight.pgm test1.pgm

echo ""
#6. Test the max width to see if correct error message is given (width > 65540)
echo "6. Testing max width for correct error"
echo "Expected outcome - ERROR: Bad Dimensions (testGreaterThanMaxWidth.pgm)"
./pgmEcho testGreaterThanMaxWidth.pgm test1.pgm

echo ""
#7. Test the min height to see if correct error message is given (height < 1)
echo "7. Testing min height for correct error" 
echo "Expected outcome - ERROR: Bad Dimensions (testLessThanMinHeight.pgm)"
./pgmEcho testLessThanMinHeight.pgm test1.pgm

echo ""
#8. Test the min width to see if correct error message is given (width < 1)
echo "8. Testing min width for correct error"
echo "Expected outcome - ERROR: Bad Dimensions (testLessThanMinWidth.pgm)"
./pgmEcho testLessThanMinWidth.pgm test1.pgm

echo ""
#9. Test the magic number to see if correct error message is given (magic number != P2 and magic number != P5])
echo "9. Testing magic number for correct error"
echo "Expected outcome - ERROR: Bad Magic Number (testMagicNum.pgm)"
./pgmEcho testMagicNum.pgm test1.pgm

echo ""
#10. Testing the image data to see if correct error message is given (one byte of image data > 255)
echo "10. Testing image data for correct error"
echo "Expected output - ERROR: Bad data (testImageData.pgm)"
./pgmEcho testImageData.pgm test1.pgm

echo ""
#11. Testing too much image data to see if correct error message is given
echo "11. Testing too much image data for correct error"
echo "Expected output - ERROR: Bad data (testTooMuchData.pgm)"
./pgmEcho testTooMuchData.pgm test1.pgm

echo ""
#12. Testing too little image data to see if correct error message is given
echo "12. Testing too little image data for correct error"
echo "Expected output - ERROR: Bad data (testTooLittleData.pgm)"
./pgmEcho testTooLittleData.pgm test1.pgm

echo ""
#13. Testing the correct output is given if everything is correct
echo "13. Testing for correct ascii input and output"
echo "Expected outcome - ECHOED"
./pgmEcho slice0a.pgm test1.pgm
echo "slice0a.pgm: "
more slice0a.pgm
echo "test1.pgm: "
more test1.pgm

echo ""
#14. Testing to see if pgmEcho echoes binary files
echo "14. Testing for correct binary input and output"
echo "Expected outcome - ECHOED"
./pgmEcho binary.pgm binaryTest.pgm

echo ""
echo ""

#Testing pgmComp
echo "TESTING PGMCOMP"

echo ""
#1. Test argument counts for correct error messages
echo "1. Testing argument count for usage message (argc == 1)"
echo "Expected outcome - Usage: ./pgmComp inputImage.pgm outputImage.pgm"
./pgmComp

echo ""
echo "Testing argument count for correct error message (argc == 2)"
echo "Expected outcome - ERROR: Bad Argument Count"
./pgmComp slice0a.pgm

echo ""
#2. Test the wrong file input to see if correct error message is given (argv[1] == NULL)
echo "2. Testing wrong first file input for correct error"
echo "Expected outcome - ERROR: Bad File Name (slice.pgm)"
./pgmComp slice.pgm output.pgm

echo ""
#3. Test the wrong file input to see if correct error message is given (argv[2] == NULL)
echo "3. Testing wrong second file input for correct error"
echo "Expected outcome - ERROR: Bad File Name (outpt.pgm)"
./pgmComp slice0a.pgm outpt.pgm

echo ""
#4. Test the magic number to see if correct error message is given (magic number != P2 and magic number != P5)
echo "4. Testing magic number for correct error"
echo "Expected outcome - ERROR: Bad Magic Number (testMagicNum.pgm)"
./pgmComp slice0a.pgm testMagicNum.pgm

echo ""
#5. Test the min width to see if correct error message is given (width < 1)
echo "5. Testing min width for correct error"
echo "Expected outcome - ERROR: Bad Dimensions (testLessThanMinWidth.pgm)"
./pgmComp slice0a.pgm testLessThanMinWidth.pgm

echo ""
#6. Test the min height to see if correct error message is given (height < 1)
echo "6. Testing min height for correct error" 
echo "Expected outcome - ERROR: Bad Dimensions (testLessThanMinHeight.pgm)"
./pgmComp slice0a.pgm testLessThanMinHeight.pgm

echo ""
#7. Test the max width to see if correct error message is given (width > 65540)
echo "7. Testing max width for correct error"
echo "Expected outcome - ERROR: Bad Dimensions (testGreaterThanMaxWidth.pgm)"
./pgmComp slice0a.pgm testGreaterThanMaxWidth.pgm

echo ""
#8. Test the max height to see if correct error message is given (height > 65540)
echo "8. Testing max height for correct error"
echo "Expected outcome - ERROR: Bad Dimensions (testGreaterThanMaxHeight.pgm)"
./pgmComp slice0a.pgm testGreaterThanMaxHeight.pgm

echo ""
#9. Test the gray value to see if correct error message is given (gray value != 255)
echo "9. Testing gray value for correct error"
echo "Expected outcome - ERROR: Bad Max Gray Value (testGrayValue.pgm)"
./pgmComp slice0a.pgm testGrayValue.pgm

echo ""
#10. Test the comment line to see if correct error message is given (comment line > 128 characters)
echo "10. Testing comment line for correct error"
echo "Expected outcome - ERROR: Bad Comment Line (testCommentLine.pgm)"
./pgmComp slice0a.pgm testCommentLine.pgm

echo ""
#11. Testing the image data to see if correct error message is given (one byte of image data > 255)
echo "11. Testing image data for correct error"
echo "Expected output - ERROR: Bad data (testImageData.pgm)"
./pgmComp slice0a.pgm testImageData.pgm

echo ""
#12. Testing too much image data to see if correct error message is given
echo "12. Testing too much image data for correct error"
echo "Expected output - ERROR: Bad data (testTooMuchData.pgm)"
./pgmComp slice0a.pgm testTooMuchData.pgm

echo ""
#13. Testing too little image data to see if correct error message is given
echo "13. Testing too little image data for correct error"
echo "Expected output - ERROR: Bad data (testTooLittleData.pgm)"
./pgmComp slice0a.pgm testTooLittleData.pgm


echo ""
#14. Testing the correct output is given if everything is correct
echo "14. Testing for correct input and output"
echo "Expected outcome - IDENTICAL"
./pgmComp slice0a.pgm test1.pgm
echo "slice0a.pgm: "
more slice0a.pgm
echo "test1.pgm: "
more test1.pgm

echo ""
#15. Testing to see if pgmComp accepts binary files
echo "15. Testing for correct binary input and output"
echo "Expected outcome - IDENTICAL"
./pgmComp binary.pgm binaryTest.pgm


echo ""
echo ""

#Testing pgma2b
echo "TESTING PGMA2B"

echo ""
#1. Test argument counts for correct error messages
echo "1. Testing argument count for usage message (argc == 1)"
echo "Expected outcome - Usage: ./pgma2b inputImage.pgm outputImage.pgm"
./pgma2b

echo""
echo "Testing argument count for correct error message (argc == 2)"
echo "Expected outcome - ERROR: Bad Argument Count"
./pgma2b slice0a.pgm

echo ""
#2. Test the wrong file input to see if correct error message is given (argv[1] == NULL)
echo "2. Testing wrong file input for correct error"
echo "Expected outcome - ERROR: Bad File Name (slice.pgm)"
./pgma2b slice.pgm test2.pgm

echo ""
#3. Test the comment line to see if correct error message is given (comment line > 128 characters)
echo "3. Testing comment line for correct error"
echo "Expected outcome - ERROR: Bad Comment Line (testCommentLine.pgm)"
./pgma2b testCommentLine.pgm test2.pgm

echo ""
#4. Test the gray value to see if correct error message is given (gray value != 255)
echo "4. Testing gray value for correct error"
echo "Expected outcome - ERROR: Bad Max Gray Value (testGrayValue.pgm)"
./pgma2b testGrayValue.pgm test2.pgm

echo ""
#5. Test the max height to see if correct error message is given (height > 65540)
echo "5. Testing max height for correct error" 
echo "Expected outcome - ERROR: Bad Dimensions (testGreaterThanMaxHeight.pgm)"
./pgma2b testGreaterThanMaxHeight.pgm test2.pgm

echo ""
#6. Test the max width to see if correct error message is given (width > 65540)
echo "6. Testing max width for correct error"
echo "Expected outcome - ERROR: Bad Dimensions (testGreaterThanMaxWidth.pgm)"
./pgma2b testGreaterThanMaxWidth.pgm test2.pgm

echo ""
#7. Test the min height to see if correct error message is given (height < 1)
echo "7. Testing min height for correct error"
echo "Expected outcome - ERROR: Bad Dimensions (testLessThanMinHeight.pgm)"
./pgma2b testLessThanMinHeight.pgm test2.pgm

echo ""
#8. Test the min width to see if correct error message is given (width < 1)
echo "8. Testing min width for correct error" 
echo "Expected outcome - ERROR: Bad Dimensions (testLessThanMinWidth.pgm)"
./pgma2b testLessThanMinWidth.pgm test2.pgm

echo ""
#9. Test the magic number to see if correct error message is given (magic number != P2)
echo "9. Testing magic number for correct error"
echo "Expected outcome - ERROR: Bad Magic Number (testMagicNum.pgm)"
./pgma2b testMagicNum.pgm test2.pgm

echo ""
#10. Testing the image data to see if correct error message is given (one byte of image data > 255)
echo "10. Testing image data for correct error"
echo "Expected output - ERROR: Bad data (testImageData.pgm)"
./pgma2b testImageData.pgm test2.pgm

echo ""
#11. Testing too much image data to see if correct error message is given
echo "11. Testing too much image data for correct error"
echo "Expected output - ERROR: Bad data (testTooMuchData.pgm)"
./pgma2b testTooMuchData.pgm test2.pgm

echo ""
#12. Testing too little image data to see if correct error message is given
echo "12. Testing too little image data for correct error"
echo "Expected output - ERROR: Bad data (testTooLittleData.pgm)"
./pgma2b testTooLittleData.pgm test2.pgm

echo ""
#13. Testing the correct output is given if everything is correct
echo "13. Testing for correct input and output"
echo "Expected outcome - CONVERTED"
./pgma2b slice0a.pgm test2.pgm

echo ""
#14. Testing the input file to see if correct error message is given (input file is a binary file)
echo "14. Testing binary file input for correct error"
echo "Expected outcome - ERROR: Bad Magic Number (test2.pgm)"
./pgma2b binary.pgm test2.pgm


echo ""
echo ""

#Testing pgmb2a
echo "TESTING PGMB2A"

echo ""
#1. Test argument counts for correct error messages
echo "1. Testing argument count for usage message (argc == 1)"
echo "Expected outcome - Usage: ./pgmb2a inputImage.pgm outputImage.pgm"
./pgmb2a

echo""
echo "Testing argument count for correct error message (argc == 2)"
echo "Expected outcome - ERROR: Bad Argument Count"
./pgmb2a slice0a.pgm

echo ""
#2. Test the wrong file input to see if correct error message is given (argv[1] == NULL)
echo "2. Testing wrong file input for correct error"
echo "Expected outcome - ERROR: Bad File Name (slice.pgm)"
./pgmb2a slice.pgm test3.pgm

echo ""
#3. Test the comment line to see if correct error message is given (comment line > 128 characters)
echo "3. Testing comment line for correct error"
echo "Expected outcome - ERROR: Bad Comment Line (testCommentLine.pgm)"
./pgmb2a testCommentLine.pgm test3.pgm

echo ""
#4. Test the gray value to see if correct error message is given (gray value != 255)
echo "4. Testing gray value for correct error"
echo "Expected outcome - ERROR: Bad Max Gray Value (testGrayValue.pgm)"
./pgmb2a testGrayValue.pgm test3.pgm

echo ""
#5. Test the max height to see if correct error message is given (height > 65540)
echo "5. Testing max height for correct error" 
echo "Expected outcome - ERROR: Bad Dimensions (testGreaterThanMaxHeight.pgm)"
./pgmb2a testGreaterThanMaxHeight.pgm test3.pgm

echo ""
#6. Test the max width to see if correct error message is given (width > 65540)
echo "6. Testing max width for correct error"
echo "Expected outcome - ERROR: Bad Dimensions (testGreaterThanMaxWidth.pgm)"
./pgmb2a testGreaterThanMaxWidth.pgm test3.pgm

echo ""
#7. Test the min height to see if correct error message is given (height < 1)
echo "7. Testing min height for correct error" 
echo "Expected outcome - ERROR: Bad Dimensions (testLessThanMinHeight.pgm)"
./pgmb2a testLessThanMinHeight.pgm test3.pgm

echo ""
#8. Test the min width to see if correct error message is given (width < 1)
echo "8. Testing min width for correct error" 
echo "Expected outcome - ERROR: Bad Dimensions (testLessThanMinWidth.pgm)"
./pgmb2a testLessThanMinWidth.pgm test3.pgm

echo ""
#9. Test the magic number to see if correct error message is given (magic number != P5)
echo "9. Testing magic number for correct error"
echo "Expected outcome - ERROR: Bad Magic Number (testMagicNum.pgm)"
./pgmb2a testMagicNum.pgm test3.pgm

echo ""
#10. Testing too much image data to see if correct error message is given
echo "10. Testing too much image data for correct error"
echo "Expected output - ERROR: Bad data (testTooMuchData.pgm)"
./pgmb2a testTooMuchData.pgm test3.pgm

echo ""
#11. Testing too little image data to see if correct error message is given
echo "11. Testing too little image data for correct error"
echo "Expected output - ERROR: Bad data (testTooLittleData.pgm)"
./pgmb2a testTooLittleData.pgm test3.pgm

echo ""
#12. Testing the correct output is given if everything is correct
echo "12. Testing for correct input and output"
echo "Expected outcome - CONVERTED"
./pgmb2a binary.pgm test3.pgm

echo ""
#13. Testing the input file to see if correct error message is given (input file is an ASCII file)
echo "13. Testing ASCII file input for correct error"
echo "Expected outcome - ERROR: Bad Magic Number (slice0a.pgm)"
./pgmb2a slice0a.pgm test3.pgm

echo ""
echo ""
#Testing between pgma2b and pgmb2a
echo "TESTING MIXING PGMB2A AND PGMA2B"

echo ""
#Testing to see if 2 ascii files are logically equivalent by coverting one file to binary with pgma2b, reconverting it to ascii using pgmb2a, and then comparing it using pgmComp
echo "Testing 2 ASCII files are equivalent when converting one to binary and reconverting it to ASCII"
echo "Expected outcome - CONVERTED, CONVERTED, IDENTICAL"
./pgma2b slice0a.pgm binary.pgm
./pgmb2a binary.pgm ascii.pgm
./pgmComp slice0a.pgm ascii.pgm

echo ""
#Testing to see if 2 binary files are logically equivalent by coverting one file to ascii with pgmb2a, reconverting it to binary using pgma2b, and then comparing it using pgmComp
echo "Testing 2 binary files are equivalent when converting one to ASCII and reconverting it to binary"
echo "Expected outcome - CONVERTED, CONVERTED, IDENTICAL"
./pgmb2a binary.pgm ascii.pgm
./pgma2b ascii.pgm binaryTest.pgm
./pgmComp binary.pgm binaryTest.pgm

echo ""
echo ""
#Testing pgmReduce
echo "TESTING PGMREDUCE"

echo ""
#Testing reducing a 10x10 ASCII image with factor 3
echo "Testing reducing a 10x10 ASCII image with factor 3"
echo "Expected outcome - REDUCED"
./pgmReduce 10x10.pgm 3 reduced.pgm
echo "10x10.pgm: "
more 10x10.pgm
echo "reduced.pgm: "
more reduced.pgm

echo ""
#Testing reducing a 5x5 ASCII image with unique pixels and factor 2
echo "Testing reducing a 5x5 ASCII image with unique pixels and factor 2"
echo "Expected outcome - REDUCED"
./pgmReduce differentPixels.pgm 2 reduced.pgm
echo "differentPixels.pgm: "
more differentPixels.pgm
echo "reduced.pgm: "
more reduced.pgm

echo ""
#Testing reducing a 10x10 binary image with factor 3
echo "Testing reducing a 10x10 binary image with factor 3"
echo "Expected outcome - CONVERTED, REDUCED"
./pgma2b 10x10.pgm binary10x10.pgm
./pgmReduce binary10x10.pgm 3 reduced.pgm

echo ""
#Testing reducing a 5x5 binary image with unique pixels and factor 2
echo "Testing reducing a 5x5 binary image with unique pixels and factor 2"
echo "Expected outcome - CONVERTED, REDUCED"
./pgma2b differentPixels.pgm binaryDifferent.pgm
./pgmReduce binaryDifferent.pgm 2 reduced.pgm

echo ""
echo ""

#Testing pgmTile
echo "TESTING PGMTILE"

echo ""
#1. Test argument counts for correct error messages
echo "1. Testing argument count for usage message (argc == 1)"
echo "Expected outcome - Usage: ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm"
./pgmTile

echo""
echo "Testing argument count for correct error message (argc == 2)"
echo "Expected outcome - ERROR: Bad Argument Count"
./pgmTile slice0a.pgm

echo ""
#2. Test the wrong file input to see if correct error message is given (argv[1] == NULL)
echo "2. Testing wrong file input for correct error"
echo "Expected outcome - ERROR: Bad File Name (slice.pgm)"
./pgmTile slice.pgm 2 "slice_<row>_<column>.pgm"

echo ""
#3. Test the comment line to see if correct error message is given (comment line > 128 characters)
echo "3. Testing comment line for correct error"
echo "Expected outcome - ERROR: Bad Comment Line (testCommentLine.pgm)"
./pgmTile testCommentLine.pgm 2 "testCommentLine_<row>_<column>.pgm"

echo ""
#4. Test the gray value to see if correct error message is given (gray value != 255)
echo "4. Testing gray value for correct error"
echo "Expected outcome - ERROR: Bad Max Gray Value (testGrayValue.pgm)"
./pgmTile testGrayValue.pgm 2 "testGrayValue_<row>_<column>.pgm"

echo ""
#5. Test the max height to see if correct error message is given (height > 65540)
echo "5. Testing max height for correct error" 
echo "Expected outcome - ERROR: Bad Dimensions (testGreaterThanMaxHeight.pgm)"
./pgmTile testGreaterThanMaxHeight.pgm 2 "testGreaterThanMaxHeight_<row>_<column>.pgm"

echo ""
#6. Test the max width to see if correct error message is given (width > 65540)
echo "6. Testing max width for correct error"
echo "Expected outcome - ERROR: Bad Dimensions (testGreaterThanMaxWidth.pgm)"
./pgmTile testGreaterThanMaxWidth.pgm 2 "testGreaterThanMaxWidth_<row>_<column>.pgm"

echo ""
#7. Test the min height to see if correct error message is given (height < 1)
echo "7. Testing min height for correct error" 
echo "Expected outcome - ERROR: Bad Dimensions (testLessThanMinHeight.pgm)"
./pgmTile testLessThanMinHeight.pgm 2 "testLessThanMinHeight_<row>_<column>.pgm"

echo ""
#8. Test the min width to see if correct error message is given (width < 1)
echo "8. Testing min width for correct error" 
echo "Expected outcome - ERROR: Bad Dimensions (testLessThanMinWidth.pgm)"
./pgmTile testLessThanMinWidth.pgm 2 "testLessThanMinHeight_<row>_<column>.pgm"

echo ""
#9. Test the magic number to see if correct error message is given (magic number != P5)
echo "9. Testing magic number for correct error"
echo "Expected outcome - ERROR: Bad Magic Number (testMagicNum.pgm)"
./pgmTile testMagicNum.pgm 2 "testMagicNum_<row>_<column>.pgm"

echo ""
#10. Testing too much image data to see if correct error message is given
echo "10. Testing too much image data for correct error"
echo "Expected output - ERROR: Bad data (testTooMuchData.pgm)"
./pgmTile testTooMuchData.pgm 2 "testTooMuchData_<row>_<column>.pgm"

echo ""
#11. Testing too little image data to see if correct error message is given
echo "11. Testing too little image data for correct error"
echo "Expected output - ERROR: Bad data (testTooLittleData.pgm)"
./pgmTile testTooLittleData.pgm 2 "testTooLittleData_<row>_<column>.pgm"

echo ""
#12. Testing for correct error message if non-numeric factor is given
echo "13. Testing for correct error message if non-numeric factor is given"
echo "Expected outcome - ERROR: Miscellaneous (Non-numeric scaling factor)"
./pgmTile slice0a.pgm a "slice0a_<row>_<column>.pgm"

echo ""
#13. Testing for correct error message if negative factor is given
echo "13. Testing for correct error message if negative factor is given"
echo "Expected outcome - ERROR: Miscellaneous (Negative scaling factor)"
./pgmTile slice0a.pgm -2 "slice0a_<row>_<column>.pgm"

echo ""
#14. Testing for correct tiling with an ASCII file
echo "14. Testing for correct input and output with an ASCII file"
echo "Expected outcome - TILED"
./pgmTile tileTesting/slice0a.pgm 2 "tileTesting/slice0a_<row>_<column>.pgm"
echo "slice0a.pgm: "
more tileTesting/slice0a.pgm
echo "slice0a_0_0.pgm: "
more tileTesting/slice0a_0_0.pgm
echo "slice0a_0_1.pgm: "
more tileTesting/slice0a_0_1.pgm
echo "slice0a_1_0.pgm: "
more tileTesting/slice0a_1_0.pgm
echo "slice0a_1_1.pgm: "
more tileTesting/slice0a_1_1.pgm

echo ""
#15. Testing for correct tiling with a binary file
echo "15. Testing for correct input and output with a binary file"
echo "Expected outcome - TILED"
./pgmTile tileTesting/binary.pgm 2 "tileTesting/binary_<row>_<column>.pgm" 


echo ""
echo ""

#Testing pgmAssemble
echo "TESTING PGMASSEMBLE"

echo ""
#1. Testing for correct error message if non-numeric row is given
echo "1. Testing for correct error message if non-numeric row is given"
echo "Expected outcome - ERROR: Bad Layout"
./pgmAssemble assemble.pgm a 4 0 0 slice0a.pgm 0 2 slice0a.pgm 2 0 slice0a.pgm 2 2 slice0a.pgm

echo ""
#2. Testing for correct error message if negative row is given
echo "2. Testing for correct error message if negative row is given"
echo "Expected outcome - ERROR: Bad Layout"
./pgmAssemble assemble.pgm -2 4 0 0 slice0a.pgm 0 2 slice0a.pgm 2 0 slice0a.pgm 2 2 slice0a.pgm

echo ""
#3. Testing for correct error message if non-numeric column is given
echo "3. Testing for correct error message if non-numeric column is given"
echo "Expected outcome - ERROR: Bad Layout"
./pgmAssemble assemble.pgm 4 a 0 0 slice0a.pgm 0 2 slice0a.pgm 2 0 slice0a.pgm 2 2 slice0a.pgm

echo ""
#4. Testing for correct error message if negative column is given
echo "4. Testing for correct error message if negative column is given"
echo "Expected outcome - ERROR: Bad Layout"
./pgmAssemble assemble.pgm 4 -2 0 0 slice0a.pgm 0 2 slice0a.pgm 2 0 slice0a.pgm 2 2 slice0a.pgm

echo ""
#5. Testing for correct input and output for ASCII file
echo "Testing for correct input and output for ASCII file"
echo "Expected outcome - ASSEMBLED"
./pgmAssemble assemble.pgm 4 4 0 0 slice0a.pgm 0 2 slice0a.pgm 2 0 slice0a.pgm 2 2 slice0a.pgm
echo "slice0a.pgm: "
more slice0a.pgm
echo "assemble.pgm: "
more assemble.pgm

echo ""
#5. Testing for correct input and output for binary file
echo "Testing for correct input and output for binary file"
echo "Expected outcome - ASSEMBLED"
./pgmAssemble assembleBinary.pgm 4 4 0 0 binary.pgm 0 2 binary.pgm 2 0 binary.pgm 2 2 binary.pgm

echo ""
#Removing our object files
echo "Removing our object files"
make clean