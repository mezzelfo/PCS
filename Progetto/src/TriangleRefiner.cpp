#include "TriangleRefiner.hpp"

namespace GeDiM
{
    TriangleRefiner::TriangleRefiner() { meshPointer = NULL;}
	TriangleRefiner::~TriangleRefiner() { }
	void TriangleRefiner::SetMesh( GenericMesh& mesh ) {meshPointer = &mesh; }
    void TriangleRefiner::AddCellToRefine( const unsigned int& value )
    {
        TriangleCell* cellaAttuale = (TriangleCell*)meshPointer->Cell(value);
        cellaAttuale->ruotafinoaquandononciloazzikka();
        // Se la cella che ho in input è gia stata doomed to be cut non c'è più nulla da fare
        if (cellaAttuale->HasProperty("CellaDaRaffinare"))
            return;
        // Altrimenti la setto da tagliare
        CellsToCut.insert(cellaAttuale);
        cellaAttuale->AddProperty("CellaDaRaffinare",(void*)true);
        // E mi registro qual'è il lato più lungo
        GenericEdge* longestEdge = (GenericEdge*)cellaAttuale->LongestEdgePtr();
        cellaAttuale->AddProperty("LongestEdge",(void*)longestEdge);
        // Poi registro sul lato più lungo il fatto che sia da tagliare
        longestEdge->AddProperty("LatoDaTagliare",(void*)true);
        // Poi ricorro sul vicino
        // Mi chiedo se esite il vicino destro e se non sono io
        if ((longestEdge->RightCell() != NULL) and (longestEdge->RightCell() != cellaAttuale))
            AddCellToRefine(longestEdge->RightCell()->Id());
        else if ((longestEdge->LeftCell() != NULL) and (longestEdge->LeftCell() != cellaAttuale))
            AddCellToRefine(longestEdge->LeftCell()->Id());
        
        return;
    }
    Output::ExitCodes TriangleRefiner::RefineMesh()
    {
    	while(not CellsToCut.empty())
    	{
            TriangleCell* cellaAttuale = *CellsToCut.begin();
            GenericEdge* latolungo = (GenericEdge*)cellaAttuale->GetProperty("LongestEdge");

            Vector3d puntomedio = {
                (latolungo->Point(0)->X()+latolungo->Point(1)->X())/2.0,
                (latolungo->Point(0)->Y()+latolungo->Point(1)->Y())/2.0,
                0
            };

            meshPointer->CutEdgeWithPoints(latolungo->Id(),vector<Vector3d>(1,puntomedio));

            int latidatagliare = 0;
            for(int i=0;i<3;i++)
                if(cellaAttuale->Edge(i)->HasProperty("LatoDaTagliare"))
                    latidatagliare++;

            switch (latidatagliare)
            {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                default:
                    cerr <<"Stocazzo"<<endl;
                    break;
            }



            latolungo->SetState(false);
    		cellaAttuale->SetState(false);
    		CellsToCut.erase(cellaAttuale);
    	}

    	
    	return Output::Success;
    }
}