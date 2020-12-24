// COMP1521 Final Exam
// Read points and determine bounding box

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Data type definitions

// all values are in the range 0..255
typedef unsigned char Byte;

// an (x,y) coordinate
typedef struct {
	Byte x;
	Byte y;
} Coord;

// a colour, given as 3 bytes (r,g,b)
typedef struct {
	Byte r;
	Byte g;
	Byte b;
} Color;

// a Point has a location and a colour
typedef struct {
	Coord coord;  // (x,y) location of Point
	Color color;  // colour of Point
} Point;

void boundingBox(int, Coord *, Coord *);

int main(int argc, char **argv)
{
	// check command-line arguments
	if (argc < 2) {
		fprintf(stderr, "Usage: %s PointsFile\n", argv[0]);
		exit(1);
	}

	// attempt to open specified file
	int in = open(argv[1],O_RDONLY);
	if (in < 0) {
		fprintf(stderr, "Can't read %s\n", argv[1]);
		exit(1);
	}

	// collect coordinates for bounding box
	Coord topLeft, bottomRight;
	boundingBox(in, &topLeft, &bottomRight);

	printf("TL=(%d,%d)  BR=(%d,%d)\n",
		 topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);

	// clean up
	close(in);
	return 0;
}

void boundingBox(int in, Coord *TL, Coord *BR)
{
	// TODO
    int sizeC = sizeof(Point);
    Point first;
    read(in, &first, sizeC);
    Byte minx = first.coord.x;
    Byte miny = first.coord.y;
    Byte maxx = first.coord.x;
    Byte maxy = first.coord.y;
    lseek(in, 0L, SEEK_SET);
    Point reader;
    while(read(in, &reader, sizeC) == sizeC){
        if(reader.coord.x < minx){
            minx = reader.coord.x;
        }
        else if(reader.coord.x > maxx){
            maxx = reader.coord.x;
        }
        if(reader.coord.y < miny){
            miny = reader.coord.y;
        }
        else if(reader.coord.y > maxy){
            maxy = reader.coord.y;
        }
    }
    TL->x = minx;
    TL->y = maxy;
    BR->x = maxx;
    BR->y = miny;
}
