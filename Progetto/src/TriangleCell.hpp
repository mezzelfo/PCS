#ifndef TRIANGLECELL_HPP
#define TRIANGLECELL_HPP

#include "GenericDomain.hpp"
#include "GenericMesh.hpp"
#include "Eigen/Eigen"

namespace GeDiM
{
	class TriangleCell : public GeDiM::GenericCell
	{
		public:
		const unsigned int idLongestEdge() const;
		static double distance(const GenericPoint* A, const GenericPoint* B);
	};
}





#endif
