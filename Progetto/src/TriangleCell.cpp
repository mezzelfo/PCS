#include "TriangleCell.hpp"
#include <math.h>

namespace GeDiM
{
	double TriangleCell::distance(const GenericPoint* A, const GenericPoint* B)
	{
		const Vector3d& Ac = A->Coordinates();
		const Vector3d& Bc = B->Coordinates();
		return sqrt(
				(Ac[0]-Bc[0])*(Ac[0]-Bc[0])+
				(Ac[1]-Bc[1])*(Ac[1]-Bc[1])+
				(Ac[2]-Bc[2])*(Ac[2]-Bc[2]));
	}

	const unsigned int TriangleCell::idLongestEdge() const
	{
		int maxid = 0;
		double maxlength = 99999.9;
		for(auto& lato : edges)
		{
			double d = distance(lato->Point(0), lato->Point(1));
			if (d < maxlength)
			{
				maxid = lato->Id();
				maxlength = d;
			}
		}
		return maxid;
	}
}