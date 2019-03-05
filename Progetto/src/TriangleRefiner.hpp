#ifndef TRIANGLEREFINER_HPP
#define TRIANGLEREFINER_HPP

#include "GenericDomain.hpp"
#include "GenericMesh.hpp"
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
		TriangleRefiner() { meshPointer = NULL; }
		~TriangleRefiner() { }

		void SetMesh( GenericMesh& mesh ) { meshPointer = &mesh; }
		void SetNumberCellsToRefine( const unsigned int& value ) { idCellsToRefine.reserve(value); }
		void AddCellId( const unsigned int& value ) { idCellsToRefine.push_back(value); }

	  Output::ExitCodes RefineMesh() { return Output::Success; }
	};
}

#endif
