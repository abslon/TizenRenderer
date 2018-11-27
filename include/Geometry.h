/*
 * Geometry.h
 *
 *  Created on: Nov 23, 2018
 *      Author: abslon
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

using namespace Dali;

struct Vertex
{
	Vector3 aPosition;
	Vector2 aTexCoord;
	Vector3 aNormal;
};

static Vertex cubeVertices[] = {
	{ Vector3(  1.0f,-1.0f,-1.0f ), Vector2( 1.0, 1.0 ), Vector3(0.0, 0.0, -1.0) },
	{ Vector3( -1.0f, 1.0f,-1.0f ), Vector2( 0.0, 0.0 ), Vector3(0.0, 0.0, -1.0) },
	{ Vector3(  1.0f, 1.0f,-1.0f ), Vector2( 0.0, 1.0 ), Vector3(0.0, 0.0, -1.0) },
	{ Vector3( -1.0f, 1.0f, 1.0f ), Vector2( 1.0, 1.0 ), Vector3(0.0, 0.0, 1.0)  },
	{ Vector3(  1.0f,-1.0f, 1.0f ), Vector2( 0.0, 0.0 ), Vector3(0.0, 0.0, 1.0)  },
	{ Vector3(  1.0f, 1.0f, 1.0f ), Vector2( 0.0, 1.0 ), Vector3(0.0, 0.0, 1.0)  },
	{ Vector3(  1.0f, 1.0f, 1.0f ), Vector2( 1.0, 1.0 ), Vector3(1.0, 0.0, 0.0)  },
	{ Vector3(  1.0f,-1.0f,-1.0f ), Vector2( 0.0, 0.0 ), Vector3(1.0, 0.0, 0.0)  },
	{ Vector3(  1.0f, 1.0f,-1.0f ), Vector2( 0.0, 1.0 ), Vector3(1.0, 0.0, 0.0)  },
	{ Vector3(  1.0f,-1.0f, 1.0f ), Vector2( 1.0, 1.0 ), Vector3(0.0, -1.0, 0.0) },
	{ Vector3( -1.0f,-1.0f,-1.0f ), Vector2( 0.0, 0.0 ), Vector3(0.0, -1.0, 0.0) },
	{ Vector3(  1.0f,-1.0f,-1.0f ), Vector2( 0.0, 1.0 ), Vector3(0.0, -1.0, 0.0) },
	{ Vector3( -1.0f,-1.0f,-1.0f ), Vector2( 1.0, 1.0 ), Vector3(-1.0, 0.0, 0.0) },
	{ Vector3( -1.0f, 1.0f, 1.0f ), Vector2( 0.0, 0.0 ), Vector3(-1.0, 0.0, 0.0) },
	{ Vector3( -1.0f, 1.0f,-1.0f ), Vector2( 0.0, 1.0 ), Vector3(-1.0, 0.0, 0.0) },
	{ Vector3(  1.0f, 1.0f,-1.0f ), Vector2( 1.0, 1.0 ), Vector3(0.0, 1.0, 0.0)  },
	{ Vector3( -1.0f, 1.0f, 1.0f ), Vector2( 0.0, 0.0 ), Vector3(0.0, 1.0, 0.0)  },
	{ Vector3(  1.0f, 1.0f, 1.0f ), Vector2( 0.0, 1.0 ), Vector3(0.0, 1.0, 0.0)  },
	{ Vector3(  1.0f,-1.0f,-1.0f ), Vector2( 1.0, 1.0 ), Vector3(0.0, 0.0, -1.0) },
	{ Vector3( -1.0f,-1.0f,-1.0f ), Vector2( 1.0, 0.0 ), Vector3(0.0, 0.0, -1.0) },
	{ Vector3( -1.0f, 1.0f,-1.0f ), Vector2( 0.0, 0.0 ), Vector3(0.0, 0.0, -1.0) },
	{ Vector3( -1.0f, 1.0f, 1.0f ), Vector2( 1.0, 1.0 ), Vector3(0.0, 0.0, 1.0)  },
	{ Vector3( -1.0f,-1.0f, 1.0f ), Vector2( 1.0, 0.0 ), Vector3(0.0, 0.0, 1.0)  },
	{ Vector3(  1.0f,-1.0f, 1.0f ), Vector2( 0.0, 0.0 ), Vector3(0.0, 0.0, 1.0)  },
	{ Vector3(  1.0f, 1.0f, 1.0f ), Vector2( 1.0, 1.0 ), Vector3(1.0, 0.0, 0.0)  },
	{ Vector3(  1.0f,-1.0f, 1.0f ), Vector2( 1.0, 0.0 ), Vector3(1.0, 0.0, 0.0)  },
	{ Vector3(  1.0f,-1.0f,-1.0f ), Vector2( 0.0, 0.0 ), Vector3(1.0, 0.0, 0.0)  },
	{ Vector3(  1.0f,-1.0f, 1.0f ), Vector2( 1.0, 1.0 ), Vector3(0.0, -1.0, 0.0) },
	{ Vector3( -1.0f,-1.0f, 1.0f ), Vector2( 1.0, 0.0 ), Vector3(0.0, -1.0, 0.0) },
	{ Vector3( -1.0f,-1.0f,-1.0f ), Vector2( 0.0, 0.0 ), Vector3(0.0, -1.0, 0.0) },
	{ Vector3( -1.0f,-1.0f,-1.0f ), Vector2( 1.0, 1.0 ), Vector3(-1.0, 0.0, 0.0) },
	{ Vector3( -1.0f,-1.0f, 1.0f ), Vector2( 1.0, 0.0 ), Vector3(-1.0, 0.0, 0.0) },
	{ Vector3( -1.0f, 1.0f, 1.0f ), Vector2( 0.0, 0.0 ), Vector3(-1.0, 0.0, 0.0) },
	{ Vector3(  1.0f, 1.0f,-1.0f ), Vector2( 1.0, 1.0 ), Vector3(0.0, 1.0, 0.0)  },
	{ Vector3( -1.0f, 1.0f,-1.0f ), Vector2( 1.0, 0.0 ), Vector3(0.0, 1.0, 0.0)  },
	{ Vector3( -1.0f, 1.0f, 1.0f ), Vector2( 0.0, 0.0 ), Vector3(0.0, 1.0, 0.0)  },
};


static const unsigned short cubeIndex[] = {
	2, 1, 0,
	5, 4, 3,
	8, 7, 6,
	11, 10, 9,
	14, 13, 12,
	17, 16, 15,
	20, 19, 18,
	23, 22, 21,
	26, 25, 24,
	29, 28, 27,
	32, 31, 30,
	35, 34, 33
};

static Vertex planeVertices[] = {
	{Vector3(1.0f, 0.0f, 1.0f),   Vector2(1.0, 1.0), Vector3(0.0, -1.0, 0.0)},
	{Vector3(-1.0f, 0.0f, -1.0f), Vector2(0.0, 0.0), Vector3(0.0, -1.0, 0.0)},
	{Vector3(1.0f, 0.0f, -1.0f),  Vector2(1.0, 0.0), Vector3(0.0, -1.0, 0.0)},
	{Vector3(-1.0f, 0.0f, 1.0f),  Vector2(0.0, 1.0), Vector3(0.0, -1.0, 0.0)},
};

static const unsigned short planeIndex[] = {
	2, 1, 0,
	0, 1, 3,
	3, 1, 0,
	0, 1, 2
};

#endif /* GEOMETRY_H_ */
