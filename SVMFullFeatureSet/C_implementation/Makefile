INCDIR   = -I./include -I./vlib1.0/include
DBG      = -g
OPT      = -O3
CXX      = g++
CXXFLAGS = $(DBG) $(OPT) $(INCDIR)
LDFLAGS  = $(DBG) $(OPT) -lm 
OBJS = classify_image.o hsv_conversion.o#$(wildcard *.cpp)


all: classify_image

%: %.o
	$(CXX) $(LDFLAGS) -o $@ $^

classify_image: $(OBJS)

clean:
	/bin/rm -f classify_image features hsv_means hsv_histograms edge_histogram location_percentiles *.o

clean-all: clean
	/bin/rm -f *~ *.p?m 



