#ifndef TRIANGLEREFINER_HPP
#define TRIANGLEREFINER_HPP

#include "GenericDomain.hpp"
#include "GenericMesh.hpp"
#include "TriangleCell.hpp"
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

namespace GeDiM
{
	class TriangleRefiner
	{
	protected:
		GenericMesh* meshPointer;
		vector<unsigned int> idCellsToRefine;
	public:
		TriangleRefiner();
		~TriangleRefiner();

		void SetMesh( GenericMesh& mesh );
		void SetNumberCellsToRefine( const unsigned int& value );
		void AddCellId( const unsigned int& value );
		
		Output::ExitCodes RefineMesh();
	};
}

#endif
