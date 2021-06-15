#pragma once

#include "RetrospectiveDetection.h"
#include "FPRF.h"

struct AABBNode
{
	virtual ~AABBNode() {}
	virtual bool isLeaf() = 0;

	double mincorner[3];
	double maxcorner[3];
};

class NodeComparator
{
public:
	NodeComparator(int axis) : axis(axis) {}

	bool operator()(AABBNode *left, AABBNode *right)
	{
		return left->mincorner[axis] < right->mincorner[axis];
	}

private:
	int axis;
};

struct AABBInteriorNode : public AABBNode
{
	virtual ~AABBInteriorNode() 
	{
		delete left; 
		delete right;
	}

	bool isLeaf() override {return false;}

	int splitaxis;
	AABBNode *left, *right;
};

struct AABBLeafNode : public AABBNode
{
	bool isLeaf() override {return true;}

	int face;
};

class FPRF_API AABBBroadPhase : public BroadPhase
{
public:
    AABBBroadPhase();

	void findCollisionCandidates(const History &h, const Mesh &m, double outerEta, std::set<VertexFaceStencil> &vfs, std::set<EdgeEdgeStencil> &ees, const std::set<int> &fixedVerts) override;
private:
	AABBNode *buildAABBTree(const History &h, const Mesh &m, double outerEta);
	AABBNode *buildAABBInterior(std::vector<AABBNode *> &children);
	void intersect(AABBNode *left, AABBNode *right, const Mesh &m, std::set<VertexFaceStencil> &vfs, std::set<EdgeEdgeStencil> &ees, const std::set<int> &fixedVerts);
};
