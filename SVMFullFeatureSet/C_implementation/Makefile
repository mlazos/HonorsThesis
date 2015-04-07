INCDIR   = -I./include -I./vlib1.0/include
DBG      = -g
OPT      = #-O3
CXX      = g++
CXXFLAGS = $(DBG) $(OPT) $(INCDIR)
LDFLAGS  = $(DBG) $(OPT) -lm
OBJS = error_estimation.o hmm.o regularize.o edginess.o textures.cpp io.o edge_centers.o feature_extraction.o hsv_means.o hsv_histograms.o hsv_conversion.o location.o svm.o

all: train_svm classify_image classify_dataset

classify_dataset: $(OBJS)

train_svm: $(OBJS)

classify_image: $(OBJS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	/bin/rm -f classify_image train_svm classify_dataset *.o
	/bin/rm -rf *.dSYM
clean-all: clean
	/bin/rm -f *~ *.p?m 



