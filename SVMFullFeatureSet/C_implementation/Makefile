INCDIR   = -I./include -I./vlib1.0/include
DBG      = -g
OPT      = #-O3
CXX      = g++
CXXFLAGS = $(DBG) $(OPT) $(INCDIR)
LDFLAGS  = $(DBG) $(OPT) -lm 
OBJS = svm.o edge_centers.o location.o hsv_histograms.o hsv_conversion.o hsv_means.o#$(wildcard *.cpp)


all: classify_image

classify_image: $(OBJS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	/bin/rm -f classify_image *.o

clean-all: clean
	/bin/rm -f *~ *.p?m 



