# the compiler: gcc for C program, define as g++ for C++
  CC = g++
 

  CXXFLAGS  = -g -Wall
  
  #LIBS = gtkmm-3.0
  PACKAGES = gtkmm-3.0
  PKGCONFIG = pkg-config
	CXXFLAGS = $(shell $(PKGCONFIG) --cflags $(PACKAGES))

	
	

  TARGET = SFgrafika-main
 	LDLIBS = $(shell pkg-config --libs gtkmm-3.0)
 	
  all: $(TARGET)
 
  $(TARGET): $(TARGET).cpp
							$(CC) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp $(LDLIBS)
 
  clean:
			$(RM) $(TARGET)
              
              

