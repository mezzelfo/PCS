#ifndef TRIANGLEREFINER_HPP
#define TRIANGLEREFINER_HPP

#include "GenericDomain.hpp"
#include "GenericMesh.hpp"
#include "TriangleCell.hpp"
#include "Eigen/Eigen"

#include <set>

using namespace std;
using namespace Eigen;

namespace GeDiM
{
	class TriangleRefiner
	{
	protected:
		GenericMesh* meshPointer;
		set<TriangleCell*> CellsToCut;
	public:
		TriangleRefiner();
		~TriangleRefiner();

		void SetMesh( GenericMesh& mesh );
		void AddCellToRefine( const unsigned int& value );
		Output::ExitCodes RefineMesh();
	};
}

#endif
