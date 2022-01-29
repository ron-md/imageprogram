#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"

/*
 * This method enlarges a 24-bit, uncompressed .bmp file that has been
 * read in using readFile(), by doubling the number of rows and
 * columns. Also the image will convert to gray scale if requested.
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the original number of rows
 * cols     - the original number of columns
 * bw       - convert to gray scale if not zero
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows (twice as many)
 * newcols  - the new number of columns (twice as many)
 */
int process(PIXEL* original, int rows, int cols, int bw,
	    PIXEL** new, int* newrows, int* newcols)
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */
    
    int row, col;
    
    *newrows = rows * 2;
    *newcols = cols * 2;
    
    if ((rows <= 0) || (cols <= 0)) return -1; //if bmp file is corrupt or no file produced, return error
    
    *new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));
    
    for (row=0; row < rows; row++)
      for (col=0; col < cols; col++) {
          
          PIXEL* oG = original + row*cols +col;
          for(int i = 0; i < 2; i++)
          for(int j = 0; j < 2; j++)
          {
              PIXEL *n = (*new) + (2 * row) * *newcols +(2 * col) + (i * *newcols) + j;
              *n = *oG;
              
              if(bw) //bw paramterx
              {
                  n->r = 0.2126*(n->r)+0.7152*(n->g)+0.0722*(n->b);
                  n->g = 0.2126*(n->r)+0.7152*(n->g)+0.0722*(n->b);
                  n->b = 0.2126*(n->r)+0.7152*(n->g)+0.0722*(n->b);
              }
          }
      }
    
  
    
  return 0;
}

/*
 * This method horizontally flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile(). 
 * 
 * THIS IS PROVIDED TO YOU AS AN EXAMPLE FOR YOU TO UNDERSTAND HOW IT
 * WORKS
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */
int flip (PIXEL *original, int rows, int cols, PIXEL **new) 
{
  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++)
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col;
      PIXEL* n = (*new) + row*cols + (cols-1-col);
      *n = *o;
    }

  return 0;
}


int main(int argc, char* argv[])
{
  int rows, cols, rows2, cols2;
  PIXEL *pix, *npix;
   

  if(argc == 1 || argc == 2 || argc > 4) //>bmptool or >bmptool input.bmp is NONO
  {
      printf("please provide an input file and output filename in bmp format\n");
      return -1;
  }
    else if( argc == 3 && (strcmp(argv[1], "-b") != 0 || strcmp(argv[1], "[-b]") != 0))
    {
        printf("Processing...\n");
        if((readFile(argv[1], &rows, &cols, &pix)) == -1) // if no file names presented get em ATTA HERE
        {
            return -1;
        }
        readFile(argv[1], &rows, &cols, &pix);
        printf("UpScaling...\n");
        process(pix, rows, cols, 0, &npix, &rows2, &cols2);
        writeFile(argv[2], rows2, cols2, npix);
        printf("Done\n");
        
    }
    
    else if( argc == 4 && (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "[-b]") == 0))
    {
        printf("Processing...\n");
        if((readFile(argv[2], &rows, &cols, &pix)) == -1)
        {
            return -1;
        }
        readFile(argv[2], &rows, &cols, &pix);
        printf("UpScaling...\n");
        process(pix, rows, cols, 2, &npix, &rows2, &cols2);
        writeFile(argv[3], rows2, cols2, npix);
        printf("Done\n");
        
    }
    
    else npix = 0, pix = 0;
        
    if( argc == 4 && (readFile(argv[2], &rows, &cols, &pix)) == -1) // this is just to print error if 4 arguments are passed but they arent files or are missing -b
    {
        return -1;
    }
    
  /* Professor's Example. Left in for testing purposes
  printf("read from file: example.bmp\n");
  readFile("example.bmp", &rows, &cols, &pix);

  printf("scale image UP\n");
  process(pix, rows, cols, 0, &npix, &rows2, &cols2);

  printf("write to file: flipped.bmp\n");
  writeFile("flipped.bmp", rows2, cols2, npix);
    */
    
    
  free(pix);
  free(npix);
   
  return 0;
}
