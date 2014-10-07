#ifndef PENALTYGROUP_H
#define PENALTYGROUP_H

#include <Eigen/Core>
#include <vector>
#include "Stencils.h"

class VertexFacePenaltyPotential;
class EdgeEdgePenaltyPotential;

class PenaltyGroup
{
public:
	PenaltyGroup(double curt, double dt, double eta, double stiffness);
	~PenaltyGroup();

	void addVFStencil(VertexFaceStencil stencil);	
	void addEEStencil(EdgeEdgeStencil stencil);

	void addForce(const Eigen::VectorXd &q, Eigen::VectorXd &F);
	void incrementTimeStep();
	double nextFireTime() const;

private:
	PenaltyGroup(const PenaltyGroup &other);
	PenaltyGroup &operator=(const PenaltyGroup &other);

	std::vector<VertexFacePenaltyPotential *> vfforces_;
	std::vector<EdgeEdgePenaltyPotential *> eeforces_;
	int nextstep_;
	double dt_;
	double eta_;
	double stiffness_;
};

#endif