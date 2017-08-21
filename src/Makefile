
segmenter: segment.o segmenter.o
	g++ -o segmenter segmenter.o segment.o -ffast-math -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -Dcimg_strict -Dcimg_use_xshm -lXext -Dcimg_use_xrandr -lXrandr

test_connected: segment.o test_connected.o
	g++ -o test_connected test_connected.o segment.o -ffast-math -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -Dcimg_strict -Dcimg_use_xshm -lXext -Dcimg_use_xrandr -lXrandr

test_line_segment: segment.o test_line_segment.o
	g++ -o test_line_segment test_line_segment.o segment.o -ffast-math -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -Dcimg_strict -Dcimg_use_xshm -lXext -Dcimg_use_xrandr -lXrandr

test_image_write: segment.o test_image_write.o
	g++ -o test_image_write test_image_write.o segment.o -ffast-math -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -Dcimg_strict -Dcimg_use_xshm -lXext -Dcimg_use_xrandr -lXrandr

test_preprocess: preprocess.o test_preprocess.o
	g++ -o test_preprocess test_preprocess.o preprocess.o -ffast-math -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -Dcimg_strict -Dcimg_use_xshm -lXext -Dcimg_use_xrandr -lXrandr

preprocess.o: preprocess.cpp
	g++ -c preprocess.cpp

test_preprocess.o: test_preprocess.cpp
	g++ -c test_preprocess.cpp

postprocessor: postprocessor.o postprocess.o
	g++ -o postprocessor postprocess.o postprocessor.o -ffast-math -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -Dcimg_strict -Dcimg_use_xshm -lXext -Dcimg_use_xrandr -lXrandr

postprocessor.o: postprocessor.cpp
	g++ -c postprocessor.cpp 

postprocess.o: postprocess.cpp
	g++ -c postprocess.cpp

dzocr: segment.o dzocr.o
	g++ -o dzocr dzocr.o segment.o -ffast-math -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -Dcimg_strict -Dcimg_use_xshm -lXext -Dcimg_use_xrandr -lXrandr

test_connected.o: test_connected.cpp
	g++ -c test_connected.cpp

test_line_segment.o: test_line_segment.cpp
	g++ -c test_line_segment.cpp

test_image_write.o: test_image_write.cpp
	g++ -c test_image_write.cpp

dzocr.o: dzocr.cpp
	g++ -c dzocr.cpp

segmenter.o: segmenter.cpp
	g++ -c segmenter.cpp

segment.o: segment.cpp
	g++ -c segment.cpp

clean:
	rm -rf *.o segmenter test_connected

cleanobject:
	rm *.o
