#include "TriangleRefiner.hpp"

namespace GeDiM
{
    TriangleRefiner::TriangleRefiner() { meshPointer = NULL;}
	TriangleRefiner::~TriangleRefiner() { }
	void TriangleRefiner::SetMesh( GenericMesh& mesh ) {meshPointer = &mesh; }
    void TriangleRefiner::AddCellToRefine( const unsigned int& value )
    {
    	TriangleCell* ptr = (TriangleCell*)meshPointer->Cell(value);
    	unsigned int longestId = ptr->idLongestEdge();
    	
    	if (idEdgesToCut.insert(longestId).second == false) return;

    	GenericEdge* latolungo = meshPointer->Edge(longestId);
    	GenericCell* other = (GenericCell*)latolungo->RightCell();
    	if ((other == NULL) || (other == ptr))
    		other = (GenericCell*)latolungo->LeftCell();
    	if ((other != NULL) && (other != ptr))
    		AddCellToRefine(other->Id());
    }
    Output::ExitCodes TriangleRefiner::RefineMesh()
    {
    	while(idEdgesToCut.size() != 0)
    	{
    		auto asdrubale = idEdgesToCut.begin();
    		unsigned int idToCut = *asdrubale;
    		GenericEdge* ptr = meshPointer->Edge(idToCut);
    		cout << ptr->Id() << endl;

    		Vector3d puntomedio = {
    			(ptr->Point(0)->X()+ptr->Point(1)->X())/2.0,
    			(ptr->Point(0)->Y()+ptr->Point(1)->Y())/2.0,
    			0};

    		cout << "Il lato "<<ptr->Id() << " ha "<<ptr->NumberOfChilds() << endl;
    		meshPointer->CutEdgeWithPoints(idToCut, vector<Vector3d>(1,puntomedio));
    		cout << "Il lato "<<ptr->Id() << " ha "<<ptr->NumberOfChilds() << endl;
    		for(int i = 0; i<2; i++)
    		{
    			GenericEdge* figlio = (GenericEdge*)ptr->Child(i);
    			cout << figlio->Point(0)->X() << ";" << figlio->Point(0)->Y() << ";"
    				 << figlio->Point(1)->X() << ";" << figlio->Point(1)->Y() << endl;
    		}



    		idEdgesToCut.erase(asdrubale);
    	}

    	
    	return Output::Success;
    }
}