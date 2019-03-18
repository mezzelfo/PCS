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

	const GenericEdge* TriangleCell::LongestEdgePtr() const
	{
		GenericEdge* m = 0;
		double maxlength = 99999.9;
		for(auto& lato : edges)
		{
			double d = distance(lato->Point(0), lato->Point(1));
			if (d < maxlength)
			{
				m = (GenericEdge*)lato;
				maxlength = d;
			}
		}
		return m;
	}


	void TriangleCell::ruotafinoaquandononciloazzikka()
	{
		while (LongestEdgePtr() != edges[0])
        {
            GenericEdge* tmp0 = (GenericEdge*)edges[0];
            GenericEdge* tmp1 = (GenericEdge*)edges[1];
            GenericEdge* tmp2 = (GenericEdge*)edges[2];
            edges[0] = tmp1;
            edges[1] = tmp2;
            edges[2] = tmp0;
        }

        while (LongestEdgePtr()->Point(0) != points[0])
        {
            GenericPoint* tmp0 = (GenericPoint*)points[0];
            GenericPoint* tmp1 = (GenericPoint*)points[1];
            GenericPoint* tmp2 = (GenericPoint*)points[2];
            points[0] = tmp1;
            points[1] = tmp2;
            points[2] = tmp0;
        }

	}
}
