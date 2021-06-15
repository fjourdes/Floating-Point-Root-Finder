#ifndef RETROSPECTIVEDETECTION_H
#define RETROSPECTIVEDETECTION_H

#include "FPRF.h"
#include "Stencils.h"
#include "History.h"
#include <set>

struct Mesh;

class FPRF_API BroadPhase
{
public:
	virtual void findCollisionCandidates(const History &h, const Mesh &m, double outerEta, std::set<VertexFaceStencil> &vfs, std::set<EdgeEdgeStencil> &ees, const std::set<int> &fixedVerts) = 0;
	virtual ~BroadPhase() {}
};

class FPRF_API NarrowPhase
{
public:
	virtual void findCollisions(const History &h, const std::set<std::pair<VertexFaceStencil, double> > &candidateVFS, const std::set<std::pair<EdgeEdgeStencil, double> > &candidateEES,
		std::set<VertexFaceStencil> &vfs, std::set<EdgeEdgeStencil> &ees) = 0;
	virtual ~NarrowPhase() {}
};

#endif
