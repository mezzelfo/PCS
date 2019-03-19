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
		vector<bool> cellsToCut;
		vector<bool> edgesToCut;
	public:
		TriangleRefiner();
		~TriangleRefiner();

		void SetMesh( GenericMesh& mesh );
		void AddCellToRefine( const unsigned int& value );
		Output::ExitCodes RefineMesh();
	};

	double distance(const GenericPoint* A, const GenericPoint* B);
	const GenericEdge* LongestEdgePtr(const GenericCell* cell);
	Output::ExitCodes correggiOrientamento(GenericCell* cell);
}

#endif
