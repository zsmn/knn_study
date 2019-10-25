CPPFLAGS=-g -Wall 

OPENCV_INCLUDE_DIR = /usr/include/opencv
LIBS= -L /usr/lib -lopencv_core -lopencv_imgproc
INCLUDE = -I ${OPENCV_INCLUDE_DIR}

.PHONY : clean all

all: $(subst .cpp,.o,$(SOURCES))  svm

svm: svm.cpp
	$(CXX) $(CPPFLAGS) ${INCLUDE} $^  ${LIBS} -o $@

clean:
	rm -rf  *.o  svm