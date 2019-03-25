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
		Output::ExitCodes Raffinamento4latiDatagliare();
		Output::ExitCodes RefineMesh();

		void tagliaLato(GenericEdge* l);
	};

	double distance(const GenericPoint* A, const GenericPoint* B);
	const GenericEdge* LongestEdgePtr(const GenericCell* cell);
	Output::ExitCodes correggiOrientamento(GenericCell* cell);
}

#endif
