#################################################################
EXECUTABLE=apriltag_test

#################################################################
#compiler
CC=g++

CFAGS=-Ofast

#################################################################
#include files
CFLAGS+=`pkg-config opencv --cflags` `pkg-config opencv --libs`
CFLAGS+=`pkg-config eigen3  --cflags`

CFLAGS+=-I./libapriltags/include/AprilTags

#################################################################
LIB_APRILTAG = libapriltags/src

SRC=$(LIB_APRILTAG)/Edge.cc \
	$(LIB_APRILTAG)/Gaussian.cc \
	$(LIB_APRILTAG)/GLineSegment2D.cc \
	$(LIB_APRILTAG)/Homography33.cc \
	$(LIB_APRILTAG)/Quad.cc \
	$(LIB_APRILTAG)/TagDetection.cc \
	$(LIB_APRILTAG)/TagFamily.cc \
	$(LIB_APRILTAG)/FloatImage.cc \
	$(LIB_APRILTAG)/GLine2D.cc \
	$(LIB_APRILTAG)/GrayModel.cc \
	$(LIB_APRILTAG)/MathUtil.cc \
	$(LIB_APRILTAG)/Segment.cc \
	$(LIB_APRILTAG)/TagDetector.cc \
	$(LIB_APRILTAG)/UnionFindSimple.cc

SRC+=./main.cpp

#################################################################

all:$(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE)
#################################################################
