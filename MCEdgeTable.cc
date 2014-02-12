/////////////////////////////////////////////////////////////////////////////
//
// MCEdgeTable.cc -- initializes edge table containing triangle locations
//
// Matt Ginzton, 2:26 PM 8/26/98#include <stdio.h>
// adapted from code by Brian Curless, 10/24/95
//
/////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <limits.h>
#include "MCEdgeTable.h"


typedef int EDGE_INDEX;
typedef struct {
  EDGE_INDEX edges[21];
} POLY_CASES;
extern POLY_CASES poly_cases[256];


EdgeTable::EdgeTable()
/* Adapted from InitEdgeTable uses Bill Lorensen's edge table */
{
  int i, ntris;
  VertexIndex index;
  EDGE_INDEX *edges, edge;

  for (index = 0; index < 256; index++) {

    edges = poly_cases[index].edges;
    ntris = 0;
    while (ntris < 5) {
      if (edges[ntris*4] == 0 && edges[ntris*4+1] == 0
	  && edges[ntris*4+2] == 0)
	break;

      ntris++;
    }

    myEdgeTable[index].Ntriangles = ntris;
    if (ntris == 0) {
      myEdgeTable[index].TriangleList = NULL;
    } else {
      myEdgeTable[index].TriangleList = new Triple [ntris];

      for (i = 0; i < 12; i++)
	(myEdgeTable[index].edge)[i] = false;

      for (i = 0; i < ntris; i++) {
	edge = edges[i*4]-1;
	myEdgeTable[index].TriangleList[i].A = edge;
	myEdgeTable[index].edge[edge] = true;

	edge = edges[i*4+1]-1;
	myEdgeTable[index].TriangleList[i].B = edge;
	myEdgeTable[index].edge[edge] = true;

	edge = edges[i*4+2]-1;
	myEdgeTable[index].TriangleList[i].C = edge;
	myEdgeTable[index].edge[edge] = true;
      }
    }
  }
}


EdgeTable::~EdgeTable ()
{
  // TODO
}


EdgeTableEntry&
EdgeTable::operator[] (int index)
{
  return myEdgeTable[index];
}


/*
 * From lorensen_cases.h:
	Bill Lorensen
	GE R&D

	cases for polygoning a cube
 *
 */


static POLY_CASES poly_cases[] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{ 1,  9,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 1 1 */
{ 1,  2, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 2 1 */
{ 2,  9,  4,  0, 10,  9,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 3 2 */
{ 2,  3, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 4 1 */
{ 1,  9,  4,  0,  2,  3, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 5 3 */
{10,  3, 12,  0,  1,  3, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 6 2 */
{ 3,  9,  4,  0,  3, 12,  9,  0, 12, 10,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 7 5 */
{ 4, 11,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 8 1 */
{ 1, 11,  3,  0,  9, 11,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 9 2 */
{ 2, 10,  1,  0,  3,  4, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 10 3 */
{ 2, 11,  3,  0,  2, 10, 11,  0, 10,  9, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 11 5 */
{ 4, 12,  2,  0, 11, 12,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 12 2 */
{ 1, 12,  2,  0,  1,  9, 12,  0,  9, 11, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 13 5 */
{ 4, 10,  1,  0,  4, 11, 10,  0, 11, 12, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 14 5 */
{10,  9, 12,  0, 12,  9, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 15 8 */
{ 5,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 16 1 */
{ 5,  4,  1,  0,  8,  4,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 17 2 */
{ 1,  2, 10,  0,  9,  5,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 18 3 */
{ 5,  2, 10,  0,  5,  8,  2,  0,  8,  4,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 19 5 */
{ 2,  3, 12,  0,  9,  5,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 20 4 */
{ 4,  5,  8,  0,  4,  1,  5,  0,  2,  3, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 21 7 */
{10,  3, 12,  0, 10,  1,  3,  0,  9,  5,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 22 7 */
{ 3, 12, 10,  0,  3, 10,  8,  0,  3,  8,  4,  0,  8, 10,  5,  0,  0,  0,  0,  0, 0}, /* 23 14 */
{ 9,  5,  8,  0,  4, 11,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 24 3 */
{11,  5,  8,  0, 11,  3,  5,  0,  3,  1,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 25 5 */
{10,  1,  2,  0,  9,  5,  8,  0,  3,  4, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 26 6 */
{ 5,  8, 11,  0, 10,  5, 11,  0, 10, 11,  3,  0, 10,  3,  2,  0,  0,  0,  0,  0, 0}, /* 27 9 */
{ 4, 12,  2,  0,  4, 11, 12,  0,  8,  9,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 28 7 */
{ 2, 11, 12,  0,  2,  5, 11,  0,  2,  1,  5,  0,  8, 11,  5,  0,  0,  0,  0,  0, 0}, /* 29 11 */
{ 5,  8,  9,  0, 10,  1, 11,  0, 10, 11, 12,  0, 11,  1,  4,  0,  0,  0,  0,  0, 0}, /* 30 12 */
{ 5,  8, 11,  0,  5, 11, 10,  0, 10, 11, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 31 5 */
{10,  6,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 32 1 */
{10,  6,  5,  0,  1,  9,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 33 3 */
{ 1,  6,  5,  0,  2,  6,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 34 2 */
{ 9,  6,  5,  0,  9,  4,  6,  0,  4,  2,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 35 5 */
{ 2,  3, 12,  0, 10,  6,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 36 3 */
{ 4,  1,  9,  0,  2,  3, 12,  0,  5, 10,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 37 6 */
{ 6,  3, 12,  0,  6,  5,  3,  0,  5,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 38 5 */
{ 3, 12,  6,  0,  4,  3,  6,  0,  4,  6,  5,  0,  4,  5,  9,  0,  0,  0,  0,  0, 0}, /* 39 9 */
{10,  6,  5,  0,  3,  4, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 40 4 */
{ 1, 11,  3,  0,  1,  9, 11,  0,  5, 10,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 41 7 */
{ 1,  6,  5,  0,  1,  2,  6,  0,  3,  4, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 42 7 */
{ 3,  2,  6,  0,  3,  6,  9,  0,  3,  9, 11,  0,  5,  9,  6,  0,  0,  0,  0,  0, 0}, /* 43 11 */
{12,  4, 11,  0, 12,  2,  4,  0, 10,  6,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 44 7 */
{ 5, 10,  6,  0,  1,  9,  2,  0,  9, 12,  2,  0,  9, 11, 12,  0,  0,  0,  0,  0, 0}, /* 45 12 */
{ 6,  5,  1,  0,  6,  1, 11,  0,  6, 11, 12,  0, 11,  1,  4,  0,  0,  0,  0,  0, 0}, /* 46 14 */
{ 6,  5,  9,  0,  6,  9, 12,  0, 12,  9, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 47 5 */
{10,  8,  9,  0,  6,  8, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 48 2 */
{10,  4,  1,  0, 10,  6,  4,  0,  6,  8,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 49 5 */
{ 1,  8,  9,  0,  1,  2,  8,  0,  2,  6,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 50 5 */
{ 2,  6,  4,  0,  4,  6,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 51 8 */
{10,  8,  9,  0, 10,  6,  8,  0, 12,  2,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 52 7 */
{12,  2,  3,  0, 10,  6,  1,  0,  6,  4,  1,  0,  6,  8,  4,  0,  0,  0,  0,  0, 0}, /* 53 12 */
{ 9,  1,  3,  0,  9,  3,  6,  0,  9,  6,  8,  0, 12,  6,  3,  0,  0,  0,  0,  0, 0}, /* 54 11 */
{ 3, 12,  6,  0,  3,  6,  4,  0,  4,  6,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 55 5 */
{ 8, 10,  6,  0,  8,  9, 10,  0,  4, 11,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 56 7 */
{10,  6,  8,  0, 10,  8,  3,  0, 10,  3,  1,  0,  3,  8, 11,  0,  0,  0,  0,  0, 0}, /* 57 14 */
{ 3,  4, 11,  0,  1,  2,  9,  0,  2,  8,  9,  0,  2,  6,  8,  0,  0,  0,  0,  0, 0}, /* 58 12 */
{11,  3,  2,  0, 11,  2,  8,  0,  8,  2,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 59 5 */
{10,  6,  9,  0,  9,  6,  8,  0, 12,  2,  4,  0, 12,  4, 11,  0,  0,  0,  0,  0, 0}, /* 60 10 */
{ 6,  8,  1,  0,  6,  1, 10,  0,  8, 11,  1,  0,  2,  1, 12,  0, 11, 12,  1,  0, 0}, /* 61 7 */
{11, 12,  1,  0, 11,  1,  4,  0, 12,  6,  1,  0,  9,  1,  8,  0,  6,  8,  1,  0, 0}, /* 62 7 */
{11, 12,  6,  0,  8, 11,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 63 2 */
{12,  7,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 64 1 */
{ 1,  9,  4,  0,  6, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 65 4 */
{10,  1,  2,  0,  6, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 66 3 */
{ 2,  9,  4,  0,  2, 10,  9,  0,  6, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 67 7 */
{ 2,  7,  6,  0,  3,  7,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 68 2 */
{ 2,  7,  6,  0,  2,  3,  7,  0,  4,  1,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 69 7 */
{10,  7,  6,  0, 10,  1,  7,  0,  1,  3,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 70 5 */
{ 6, 10,  9,  0,  6,  9,  3,  0,  6,  3,  7,  0,  4,  3,  9,  0,  0,  0,  0,  0, 0}, /* 71 11 */
{ 3,  4, 11,  0, 12,  7,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 72 3 */
{11,  1,  9,  0, 11,  3,  1,  0, 12,  7,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 73 7 */
{ 1,  2, 10,  0,  3,  4, 11,  0,  6, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 74 6 */
{ 6, 12,  7,  0,  2, 10,  3,  0, 10, 11,  3,  0, 10,  9, 11,  0,  0,  0,  0,  0, 0}, /* 75 12 */
{ 7,  4, 11,  0,  7,  6,  4,  0,  6,  2,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 76 5 */
{ 1,  9, 11,  0,  1, 11,  6,  0,  1,  6,  2,  0,  6, 11,  7,  0,  0,  0,  0,  0, 0}, /* 77 14 */
{ 4, 11,  7,  0,  1,  4,  7,  0,  1,  7,  6,  0,  1,  6, 10,  0,  0,  0,  0,  0, 0}, /* 78 9 */
{ 7,  6, 10,  0,  7, 10, 11,  0, 11, 10,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 79 5 */
{ 6, 12,  7,  0,  5,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 80 3 */
{ 5,  4,  1,  0,  5,  8,  4,  0,  7,  6, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 81 7 */
{ 2, 10,  1,  0,  6, 12,  7,  0,  9,  5,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 82 6 */
{12,  7,  6,  0,  2, 10,  8,  0,  2,  8,  4,  0,  8, 10,  5,  0,  0,  0,  0,  0, 0}, /* 83 12 */
{ 7,  2,  3,  0,  7,  6,  2,  0,  5,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 84 7 */
{ 2,  3,  6,  0,  6,  3,  7,  0,  4,  1,  5,  0,  4,  5,  8,  0,  0,  0,  0,  0, 0}, /* 85 10 */
{ 9,  5,  8,  0, 10,  1,  6,  0,  1,  7,  6,  0,  1,  3,  7,  0,  0,  0,  0,  0, 0}, /* 86 12 */
{ 8,  4, 10,  0,  8, 10,  5,  0,  4,  3, 10,  0,  6, 10,  7,  0,  3,  7, 10,  0, 0}, /* 87 7 */
{ 4, 11,  3,  0,  8,  9,  5,  0, 12,  7,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 88 6 */
{ 6, 12,  7,  0,  5,  8,  3,  0,  5,  3,  1,  0,  3,  8, 11,  0,  0,  0,  0,  0, 0}, /* 89 12 */
{ 1,  2, 10,  0,  5,  8,  9,  0,  3,  4, 11,  0,  6, 12,  7,  0,  0,  0,  0,  0, 0}, /* 90 13 */
{10,  3,  2,  0, 10, 11,  3,  0, 10,  5, 11,  0,  8, 11,  5,  0,  6, 12,  7,  0, 0}, /* 91 6 */
{ 9,  5,  8,  0,  4, 11,  6,  0,  4,  6,  2,  0,  6, 11,  7,  0,  0,  0,  0,  0, 0}, /* 92 12 */
{ 6,  2, 11,  0,  6, 11,  7,  0,  2,  1, 11,  0,  8, 11,  5,  0,  1,  5, 11,  0, 0}, /* 93 7 */
{ 1,  6, 10,  0,  1,  7,  6,  0,  1,  4,  7,  0, 11,  7,  4,  0,  9,  5,  8,  0, 0}, /* 94 6 */
{ 7,  6, 10,  0,  7, 10, 11,  0,  5,  8, 10,  0,  8, 11, 10,  0,  0,  0,  0,  0, 0}, /* 95 3 */
{12,  5, 10,  0,  7,  5, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 96 2 */
{ 5, 12,  7,  0,  5, 10, 12,  0,  1,  9,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 97 7 */
{12,  1,  2,  0, 12,  7,  1,  0,  7,  5,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 98 5 */
{ 9,  4,  2,  0,  9,  2,  7,  0,  9,  7,  5,  0,  7,  2, 12,  0,  0,  0,  0,  0, 0}, /* 99 14 */
{ 2,  5, 10,  0,  2,  3,  5,  0,  3,  7,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 100 5 */
{ 4,  1,  9,  0,  2,  3, 10,  0,  3,  5, 10,  0,  3,  7,  5,  0,  0,  0,  0,  0, 0}, /* 101 12 */
{ 1,  3,  5,  0,  5,  3,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 102 8 */
{ 9,  4,  3,  0,  9,  3,  5,  0,  5,  3,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 103 5 */
{12,  5, 10,  0, 12,  7,  5,  0, 11,  3,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 104 7 */
{ 1,  9,  3,  0,  3,  9, 11,  0,  5, 10, 12,  0,  5, 12,  7,  0,  0,  0,  0,  0, 0}, /* 105 10 */
{ 4, 11,  3,  0,  1,  2,  7,  0,  1,  7,  5,  0,  7,  2, 12,  0,  0,  0,  0,  0, 0}, /* 106 12 */
{ 7,  5,  2,  0,  7,  2, 12,  0,  5,  9,  2,  0,  3,  2, 11,  0,  9, 11,  2,  0, 0}, /* 107 7 */
{10,  7,  5,  0, 10,  4,  7,  0, 10,  2,  4,  0, 11,  7,  4,  0,  0,  0,  0,  0, 0}, /* 108 11 */
{ 9, 11,  2,  0,  9,  2,  1,  0, 11,  7,  2,  0, 10,  2,  5,  0,  7,  5,  2,  0, 0}, /* 109 7 */
{ 4, 11,  7,  0,  4,  7,  1,  0,  1,  7,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 110 5 */
{ 7,  5,  9,  0, 11,  7,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 111 2 */
{ 8, 12,  7,  0,  8,  9, 12,  0,  9, 10, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 112 5 */
{ 1,  8,  4,  0,  1, 12,  8,  0,  1, 10, 12,  0,  7,  8, 12,  0,  0,  0,  0,  0, 0}, /* 113 11 */
{12,  7,  8,  0,  2, 12,  8,  0,  2,  8,  9,  0,  2,  9,  1,  0,  0,  0,  0,  0, 0}, /* 114 9 */
{12,  7,  8,  0, 12,  8,  2,  0,  2,  8,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 115 5 */
{ 2,  3,  7,  0,  2,  7,  9,  0,  2,  9, 10,  0,  9,  7,  8,  0,  0,  0,  0,  0, 0}, /* 116 14 */
{ 3,  7, 10,  0,  3, 10,  2,  0,  7,  8, 10,  0,  1, 10,  4,  0,  8,  4, 10,  0, 0}, /* 117 7 */
{ 8,  9,  1,  0,  8,  1,  7,  0,  7,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 118 5 */
{ 8,  4,  3,  0,  7,  8,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 119 2 */
{ 3,  4, 11,  0, 12,  7,  9,  0, 12,  9, 10,  0,  9,  7,  8,  0,  0,  0,  0,  0, 0}, /* 120 12 */
{ 3,  1,  8,  0,  3,  8, 11,  0,  1, 10,  8,  0,  7,  8, 12,  0, 10, 12,  8,  0, 0}, /* 121 7 */
{ 2,  9,  1,  0,  2,  8,  9,  0,  2, 12,  8,  0,  7,  8, 12,  0,  3,  4, 11,  0, 0}, /* 122 6 */
{11,  3,  2,  0, 11,  2,  8,  0, 12,  7,  2,  0,  7,  8,  2,  0,  0,  0,  0,  0, 0}, /* 123 3 */
{ 9, 10,  7,  0,  9,  7,  8,  0, 10,  2,  7,  0, 11,  7,  4,  0,  2,  4,  7,  0, 0}, /* 124 7 */
{ 1, 10,  2,  0, 11,  7,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 125 4 */
{ 8,  9,  1,  0,  8,  1,  7,  0,  4, 11,  1,  0, 11,  7,  1,  0,  0,  0,  0,  0, 0}, /* 126 3 */
{ 8, 11,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 127 1 */
{ 8,  7, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 128 1 */
{ 4,  1,  9,  0, 11,  8,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 129 3 */
{ 1,  2, 10,  0, 11,  8,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 130 4 */
{ 9,  2, 10,  0,  9,  4,  2,  0, 11,  8,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 131 7 */
{12,  2,  3,  0,  7, 11,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 132 3 */
{ 2,  3, 12,  0,  4,  1,  9,  0,  7, 11,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 133 6 */
{ 3, 10,  1,  0,  3, 12, 10,  0,  7, 11,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 134 7 */
{ 7, 11,  8,  0,  3, 12,  4,  0, 12,  9,  4,  0, 12, 10,  9,  0,  0,  0,  0,  0, 0}, /* 135 12 */
{ 8,  3,  4,  0,  7,  3,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 136 2 */
{ 8,  1,  9,  0,  8,  7,  1,  0,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 137 5 */
{ 3,  8,  7,  0,  3,  4,  8,  0,  1,  2, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 138 7 */
{ 2,  7,  3,  0,  2,  9,  7,  0,  2, 10,  9,  0,  9,  8,  7,  0,  0,  0,  0,  0, 0}, /* 139 14 */
{12,  8,  7,  0, 12,  2,  8,  0,  2,  4,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 140 5 */
{12,  8,  7,  0,  2,  8, 12,  0,  2,  9,  8,  0,  2,  1,  9,  0,  0,  0,  0,  0, 0}, /* 141 9 */
{ 1,  4,  8,  0,  1,  8, 12,  0,  1, 12, 10,  0,  7, 12,  8,  0,  0,  0,  0,  0, 0}, /* 142 11 */
{ 8,  7, 12,  0,  8, 12,  9,  0,  9, 12, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 143 5 */
{ 7,  9,  5,  0, 11,  9,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 144 2 */
{ 4,  7, 11,  0,  4,  1,  7,  0,  1,  5,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 145 5 */
{ 9,  7, 11,  0,  9,  5,  7,  0, 10,  1,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 146 7 */
{10,  5,  7,  0, 10,  7,  4,  0, 10,  4,  2,  0, 11,  4,  7,  0,  0,  0,  0,  0, 0}, /* 147 11 */
{ 7,  9,  5,  0,  7, 11,  9,  0,  3, 12,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 148 7 */
{ 2,  3, 12,  0,  4,  1, 11,  0,  1,  7, 11,  0,  1,  5,  7,  0,  0,  0,  0,  0, 0}, /* 149 12 */
{ 5, 11,  9,  0,  5,  7, 11,  0,  1,  3, 10,  0,  3, 12, 10,  0,  0,  0,  0,  0, 0}, /* 150 10 */
{12, 10,  4,  0, 12,  4,  3,  0, 10,  5,  4,  0, 11,  4,  7,  0,  5,  7,  4,  0, 0}, /* 151 7 */
{ 9,  3,  4,  0,  9,  5,  3,  0,  5,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 152 5 */
{ 1,  5,  3,  0,  5,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 153 8 */
{ 2, 10,  1,  0,  3,  4,  5,  0,  3,  5,  7,  0,  5,  4,  9,  0,  0,  0,  0,  0, 0}, /* 154 12 */
{ 2, 10,  5,  0,  2,  5,  3,  0,  3,  5,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 155 5 */
{ 9,  2,  4,  0,  9,  7,  2,  0,  9,  5,  7,  0,  7, 12,  2,  0,  0,  0,  0,  0, 0}, /* 156 14 */
{12,  2,  1,  0, 12,  1,  7,  0,  7,  1,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 157 5 */
{ 5,  7,  4,  0,  5,  4,  9,  0,  7, 12,  4,  0,  1,  4, 10,  0, 12, 10,  4,  0, 0}, /* 158 7 */
{12, 10,  5,  0,  7, 12,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 159 2 */
{ 5, 10,  6,  0,  8,  7, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 160 3 */
{ 1,  9,  4,  0,  5, 10,  6,  0, 11,  8,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 161 6 */
{ 6,  1,  2,  0,  6,  5,  1,  0,  8,  7, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 162 7 */
{11,  8,  7,  0,  9,  4,  5,  0,  4,  6,  5,  0,  4,  2,  6,  0,  0,  0,  0,  0, 0}, /* 163 12 */
{10,  6,  5,  0, 12,  2,  3,  0,  8,  7, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 164 6 */
{ 7, 11,  8,  0,  2,  3, 12,  0,  1,  9,  4,  0,  5, 10,  6,  0,  0,  0,  0,  0, 0}, /* 165 13 */
{ 8,  7, 11,  0,  6,  5, 12,  0,  5,  3, 12,  0,  5,  1,  3,  0,  0,  0,  0,  0, 0}, /* 166 12 */
{ 4,  5,  9,  0,  4,  6,  5,  0,  4,  3,  6,  0, 12,  6,  3,  0, 11,  8,  7,  0, 0}, /* 167 6 */
{ 8,  3,  4,  0,  8,  7,  3,  0,  6,  5, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 168 7 */
{10,  6,  5,  0,  1,  9,  7,  0,  1,  7,  3,  0,  7,  9,  8,  0,  0,  0,  0,  0, 0}, /* 169 12 */
{ 4,  7,  3,  0,  4,  8,  7,  0,  2,  6,  1,  0,  6,  5,  1,  0,  0,  0,  0,  0, 0}, /* 170 10 */
{ 7,  3,  9,  0,  7,  9,  8,  0,  3,  2,  9,  0,  5,  9,  6,  0,  2,  6,  9,  0, 0}, /* 171 7 */
{10,  6,  5,  0, 12,  2,  7,  0,  2,  8,  7,  0,  2,  4,  8,  0,  0,  0,  0,  0, 0}, /* 172 12 */
{ 2,  7, 12,  0,  2,  8,  7,  0,  2,  1,  8,  0,  9,  8,  1,  0, 10,  6,  5,  0, 0}, /* 173 6 */
{ 5,  1, 12,  0,  5, 12,  6,  0,  1,  4, 12,  0,  7, 12,  8,  0,  4,  8, 12,  0, 0}, /* 174 7 */
{ 8,  7, 12,  0,  8, 12,  9,  0,  6,  5, 12,  0,  5,  9, 12,  0,  0,  0,  0,  0, 0}, /* 175 3 */
{ 7, 10,  6,  0,  7, 11, 10,  0, 11,  9, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 176 5 */
{ 4,  7, 11,  0,  1,  7,  4,  0,  1,  6,  7,  0,  1, 10,  6,  0,  0,  0,  0,  0, 0}, /* 177 9 */
{ 1, 11,  9,  0,  1,  6, 11,  0,  1,  2,  6,  0,  6,  7, 11,  0,  0,  0,  0,  0, 0}, /* 178 14 */
{ 7, 11,  4,  0,  7,  4,  6,  0,  6,  4,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 179 5 */
{ 2,  3, 12,  0, 10,  6, 11,  0, 10, 11,  9,  0, 11,  6,  7,  0,  0,  0,  0,  0, 0}, /* 180 12 */
{ 1, 11,  4,  0,  1,  7, 11,  0,  1, 10,  7,  0,  6,  7, 10,  0,  2,  3, 12,  0, 0}, /* 181 6 */
{11,  9,  6,  0, 11,  6,  7,  0,  9,  1,  6,  0, 12,  6,  3,  0,  1,  3,  6,  0, 0}, /* 182 7 */
{ 7, 11,  4,  0,  7,  4,  6,  0,  3, 12,  4,  0, 12,  6,  4,  0,  0,  0,  0,  0, 0}, /* 183 3 */
{ 6,  9, 10,  0,  6,  3,  9,  0,  6,  7,  3,  0,  4,  9,  3,  0,  0,  0,  0,  0, 0}, /* 184 11 */
{10,  6,  7,  0, 10,  7,  1,  0,  1,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 185 5 */
{ 2,  6,  9,  0,  2,  9,  1,  0,  6,  7,  9,  0,  4,  9,  3,  0,  7,  3,  9,  0, 0}, /* 186 7 */
{ 2,  6,  7,  0,  3,  2,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 187 2 */
{ 2,  4,  7,  0,  2,  7, 12,  0,  4,  9,  7,  0,  6,  7, 10,  0,  9, 10,  7,  0, 0}, /* 188 7 */
{12,  2,  1,  0, 12,  1,  7,  0, 10,  6,  1,  0,  6,  7,  1,  0,  0,  0,  0,  0, 0}, /* 189 3 */
{ 1,  4,  9,  0,  6,  7, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 190 4 */
{12,  6,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 191 1 */
{11,  6, 12,  0,  8,  6, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 192 2 */
{11,  6, 12,  0, 11,  8,  6,  0,  9,  4,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 193 7 */
{ 6, 11,  8,  0,  6, 12, 11,  0,  2, 10,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 194 7 */
{12,  8,  6,  0, 12, 11,  8,  0, 10,  9,  2,  0,  9,  4,  2,  0,  0,  0,  0,  0, 0}, /* 195 10 */
{11,  2,  3,  0, 11,  8,  2,  0,  8,  6,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 196 5 */
{ 1,  9,  4,  0,  2,  3,  8,  0,  2,  8,  6,  0,  8,  3, 11,  0,  0,  0,  0,  0, 0}, /* 197 12 */
{10,  8,  6,  0, 10,  3,  8,  0, 10,  1,  3,  0,  3, 11,  8,  0,  0,  0,  0,  0, 0}, /* 198 14 */
{ 8,  6,  3,  0,  8,  3, 11,  0,  6, 10,  3,  0,  4,  3,  9,  0, 10,  9,  3,  0, 0}, /* 199 7 */
{ 3,  6, 12,  0,  3,  4,  6,  0,  4,  8,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 200 5 */
{ 9,  3,  1,  0,  9,  6,  3,  0,  9,  8,  6,  0, 12,  3,  6,  0,  0,  0,  0,  0, 0}, /* 201 11 */
{10,  1,  2,  0,  6, 12,  4,  0,  6,  4,  8,  0,  4, 12,  3,  0,  0,  0,  0,  0, 0}, /* 202 12 */
{10,  9,  3,  0, 10,  3,  2,  0,  9,  8,  3,  0, 12,  3,  6,  0,  8,  6,  3,  0, 0}, /* 203 7 */
{ 2,  4,  6,  0,  4,  8,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 204 8 */
{ 1,  9,  8,  0,  1,  8,  2,  0,  2,  8,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 205 5 */
{10,  1,  4,  0, 10,  4,  6,  0,  6,  4,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 206 5 */
{10,  9,  8,  0,  6, 10,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 207 2 */
{ 6,  9,  5,  0,  6, 12,  9,  0, 12, 11,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 208 5 */
{ 6,  1,  5,  0,  6, 11,  1,  0,  6, 12, 11,  0, 11,  4,  1,  0,  0,  0,  0,  0, 0}, /* 209 14 */
{ 1,  2, 10,  0,  9,  5, 12,  0,  9, 12, 11,  0, 12,  5,  6,  0,  0,  0,  0,  0, 0}, /* 210 12 */
{12, 11,  5,  0, 12,  5,  6,  0, 11,  4,  5,  0, 10,  5,  2,  0,  4,  2,  5,  0, 0}, /* 211 7 */
{ 3,  6,  2,  0,  3,  9,  6,  0,  3, 11,  9,  0,  5,  6,  9,  0,  0,  0,  0,  0, 0}, /* 212 11 */
{ 1,  5, 11,  0,  1, 11,  4,  0,  5,  6, 11,  0,  3, 11,  2,  0,  6,  2, 11,  0, 0}, /* 213 7 */
{ 1,  3,  6,  0,  1,  6, 10,  0,  3, 11,  6,  0,  5,  6,  9,  0, 11,  9,  6,  0, 0}, /* 214 7 */
{10,  5,  6,  0,  3, 11,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 215 4 */
{ 3,  6, 12,  0,  4,  6,  3,  0,  4,  5,  6,  0,  4,  9,  5,  0,  0,  0,  0,  0, 0}, /* 216 9 */
{ 6, 12,  3,  0,  6,  3,  5,  0,  5,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 217 5 */
{ 4, 12,  3,  0,  4,  6, 12,  0,  4,  9,  6,  0,  5,  6,  9,  0,  1,  2, 10,  0, 0}, /* 218 6 */
{ 6, 12,  3,  0,  6,  3,  5,  0,  2, 10,  3,  0, 10,  5,  3,  0,  0,  0,  0,  0, 0}, /* 219 3 */
{ 9,  5,  6,  0,  9,  6,  4,  0,  4,  6,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 220 5 */
{ 1,  5,  6,  0,  2,  1,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 221 2 */
{ 9,  5,  6,  0,  9,  6,  4,  0, 10,  1,  6,  0,  1,  4,  6,  0,  0,  0,  0,  0, 0}, /* 222 3 */
{10,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 223 1 */
{ 5, 11,  8,  0,  5, 10, 11,  0, 10, 12, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 224 5 */
{ 1,  9,  4,  0,  5, 10,  8,  0, 10, 11,  8,  0, 10, 12, 11,  0,  0,  0,  0,  0, 0}, /* 225 12 */
{ 2, 12, 11,  0,  2, 11,  5,  0,  2,  5,  1,  0,  8,  5, 11,  0,  0,  0,  0,  0, 0}, /* 226 11 */
{ 4,  2,  5,  0,  4,  5,  9,  0,  2, 12,  5,  0,  8,  5, 11,  0, 12, 11,  5,  0, 0}, /* 227 7 */
{ 5, 11,  8,  0, 10, 11,  5,  0, 10,  3, 11,  0, 10,  2,  3,  0,  0,  0,  0,  0, 0}, /* 228 9 */
{10,  8,  5,  0, 10, 11,  8,  0, 10,  2, 11,  0,  3, 11,  2,  0,  1,  9,  4,  0, 0}, /* 229 6 */
{11,  8,  5,  0, 11,  5,  3,  0,  3,  5,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 230 5 */
{11,  8,  5,  0, 11,  5,  3,  0,  9,  4,  5,  0,  4,  3,  5,  0,  0,  0,  0,  0, 0}, /* 231 3 */
{ 3, 10, 12,  0,  3,  8, 10,  0,  3,  4,  8,  0,  8,  5, 10,  0,  0,  0,  0,  0, 0}, /* 232 14 */
{10, 12,  8,  0, 10,  8,  5,  0, 12,  3,  8,  0,  9,  8,  1,  0,  3,  1,  8,  0, 0}, /* 233 7 */
{ 4,  8, 12,  0,  4, 12,  3,  0,  8,  5, 12,  0,  2, 12,  1,  0,  5,  1, 12,  0, 0}, /* 234 7 */
{ 2, 12,  3,  0,  9,  8,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 235 4 */
{ 5, 10,  2,  0,  5,  2,  8,  0,  8,  2,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 236 5 */
{ 5, 10,  2,  0,  5,  2,  8,  0,  1,  9,  2,  0,  9,  8,  2,  0,  0,  0,  0,  0, 0}, /* 237 3 */
{ 5,  1,  4,  0,  8,  5,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 238 2 */
{ 5,  9,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 239 1 */
{10, 12,  9,  0, 12, 11,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 240 8 */
{ 4,  1, 10,  0,  4, 10, 11,  0, 11, 10, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 241 5 */
{ 1,  2, 12,  0,  1, 12,  9,  0,  9, 12, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 242 5 */
{ 4,  2, 12,  0, 11,  4, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 243 2 */
{ 2,  3, 11,  0,  2, 11, 10,  0, 10, 11,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 244 5 */
{ 4,  1, 10,  0,  4, 10, 11,  0,  2,  3, 10,  0,  3, 11, 10,  0,  0,  0,  0,  0, 0}, /* 245 3 */
{ 1,  3, 11,  0,  9,  1, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 246 2 */
{ 4,  3, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 247 1 */
{ 3,  4,  9,  0,  3,  9, 12,  0, 12,  9, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 248 5 */
{10, 12,  3,  0,  1, 10,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 249 2 */
{ 3,  4,  9,  0,  3,  9, 12,  0,  1,  2,  9,  0,  2, 12,  9,  0,  0,  0,  0,  0, 0}, /* 250 3 */
{ 2, 12,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 251 1 */
{ 2,  4,  9,  0, 10,  2,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 252 2 */
{ 1, 10,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 253 1 */
{ 1,  4,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0}, /* 254 1 */
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
