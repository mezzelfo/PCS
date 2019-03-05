#include "TriangleRefiner.hpp"

namespace GeDiM
{
    TriangleRefiner::TriangleRefiner() { meshPointer = NULL; printf("HEII\n");}
	TriangleRefiner::~TriangleRefiner() { }
	void TriangleRefiner::SetMesh( GenericMesh& mesh ) {meshPointer = &mesh; }
    void TriangleRefiner::SetNumberCellsToRefine( const unsigned int& value ) { idCellsToRefine.reserve(value); }
    void TriangleRefiner::AddCellId( const unsigned int& value ) { idCellsToRefine.push_back(value); }
    Output::ExitCodes TriangleRefiner::RefineMesh() { return Output::Success; }
}