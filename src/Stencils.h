#ifndef STENCILS_H
#define STENCILS_H

#include <cassert>
#include <utility>

struct VertexFaceStencil
{
    int p;
    int q0, q1, q2;
    bool isnew;

    VertexFaceStencil(int p_, int q0_, int q1_, int q2_);

    bool operator<(const VertexFaceStencil& other) const;
};

struct EdgeEdgeStencil
{
    int p0, p1;
    int q0, q1;
    bool isnew;

    EdgeEdgeStencil(int p0_, int p1_, int q0_, int q1_);

    bool operator<(const EdgeEdgeStencil& other) const;
};

#endif
