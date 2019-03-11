#include "TriangleRefiner.hpp"
#include <set>

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
    	std::set<unsigned int> idEdgesToCut;
    	for(unsigned int t : idCellsToRefine)
    	{
    		TriangleCell* ptr = (TriangleCell*)meshPointer->Cell(t);
    		idEdgesToCut.insert(ptr->idLongestEdge());
    	}

    	for (unsigned int p : idEdgesToCut)
    	{
    		std::cout<<p<<'\n';
    	}
    	
        //while(not idCellsToRefine.empty())
    	


    	return Output::Success;
    }
}