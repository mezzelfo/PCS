#include "TriangleRefiner.hpp"

namespace GeDiM
{
    TriangleRefiner::TriangleRefiner() { meshPointer = NULL; printf("HEII\n");}
	TriangleRefiner::~TriangleRefiner() { }
	void TriangleRefiner::SetMesh( GenericMesh& mesh ) {meshPointer = &mesh; }
    void TriangleRefiner::SetNumberCellsToRefine( const unsigned int& value ) { idCellsToRefine.reserve(value); }
    void TriangleRefiner::AddCellId( const unsigned int& value ) { idCellsToRefine.push_back(value); }
    Output::ExitCodes TriangleRefiner::RefineMesh()
    {
    	idCellsToRefine.shrink_to_fit();
    	std::cout << "Il numero di celle da rifinire: " << idCellsToRefine.size() << std::endl;
    	std::set<GenericEdge> idEdgesToCut;
    	for(auto& t : idCellsToRefine)
    		idEdgesToCut.push_back(t.idLongestEdge());

    	//while(not idCellsToRefine.empty())
    	


    	return Output::Success;
    }
}