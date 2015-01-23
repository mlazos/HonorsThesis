INCDIR = -I./include -I./vlib1.0/include
DBG    = -g
OPT    = -O3
CPP    = g++
CFLAGS = $(DBG) $(OPT) $(INCDIR)
LINK   = -lm 
FEATURES = hsv_means hsv_histograms edge_histogram location_percentiles

all: classify_image

classify_image: classify_image.cpp hsv_conversion $(FEATURES)
	$(CPP) $(CFLAGS) -o classify_image classify_image.cpp $(LINK)

hsv_conversion: hsv_conversion.cpp
	$(CPP) $(CFLAGS) -o hsv_conversion hsv_conversion.cpp $(LINK)

hsv_means: hsv_means.cpp 
	$(CPP) $(CFLAGS) -o hsv_means hsv_means.cpp $(LINK)

hsv_histograms: hsv_histograms.cpp 
	$(CPP) $(CFLAGS) -o hsv_histograms hsv_histograms.cpp $(LINK)

edge_histogram: edge_histogram.cpp
	$(CPP) $(CFLAGS) -o edge_histogram edge_histogram.cpp $(LINK)

location_percentiles: location_percentiles.cpp 
	$(CPP) $(CFLAGS) -o location_percentiles location_percentiles.cpp $(LINK)

clean:
	/bin/rm -f classify_image features hsv_means hsv_histograms edge_histogram location_percentiles *.o

clean-all: clean
	/bin/rm -f *~ *.p?m 



