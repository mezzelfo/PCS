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
            GenericCell* cellaAttuale = *CellsToCut.begin();
            GenericEdge* latolungo = (GenericEdge*)cellaAttuale->GetProperty("LongestEdge");
            cout << "Raffino la cella numero: " << cellaAttuale->Id() << endl;

            Vector3d puntomedio = {
                (latolungo->Point(0)->X()+latolungo->Point(1)->X())/2.0,
                (latolungo->Point(0)->Y()+latolungo->Point(1)->Y())/2.0,
                0
            };

            meshPointer->CutEdgeWithPoints(latolungo->Id(),vector<Vector3d>(1,puntomedio));


            GenericPoint* A = (GenericPoint*)latolungo->Point(0);
            GenericPoint* B = (GenericPoint*)latolungo->Point(1);
            GenericPoint* D = (GenericPoint*)cellaAttuale->Point(2);


            GenericEdge* L1=(GenericEdge*)latolungo->Child(0);
            GenericPoint* C = (GenericPoint*)L1->Point(1);
            GenericEdge* latoNuovo= meshPointer->CreateEdge();
            meshPointer->AddEdge(latoNuovo);
            latoNuovo->AddPoint(C);
            latoNuovo->AddPoint(D);
            latoNuovo->AllocateCells(2);



            //Crea la prima cella
            GenericCell* Pippo = meshPointer->CreateCell();
            meshPointer->AddCell(Pippo);
            list<unsigned int> listalati = {L1->Id(),latoNuovo->Id(),cellaAttuale->Edge(2)->Id()};
            list<unsigned int> listapunti = {A->Id(),C->Id(),D->Id()};
            meshPointer->CreateCellChild2D(*Pippo, *cellaAttuale,listalati,listapunti,false);



            cout << CellsToCut.size() << endl;

            //Crea la seconda cella
            GenericEdge* L2 =(GenericEdge*)latolungo->Child(1);
            GenericCell* Pippo2 = meshPointer->CreateCell();
            meshPointer->AddCell(Pippo2);
            list<unsigned int> listalati2 = {L2->Id(),cellaAttuale->Edge(2)->Id(),latoNuovo->Id()};
            list<unsigned int> listapunti2 = {C->Id(),B->Id(),D->Id()};
            meshPointer->CreateCellChild2D(*Pippo2, *cellaAttuale,listalati2,listapunti2,false);

            //controlla se bisogna tagliare altri lati nel figlio 1
            if(Pippo->Edge(2)->HasProperty("LatoDaTagliare")){
                     cout << "Rimando la cella numero: " << Pippo->Id() << endl;
                     cout << "a destra la numero: " << Pippo->Edge(2)->RightCell()->Id() << endl;
                     cout << "a sinistra la numero: " << Pippo->Edge(2)->LeftCell()->Id() << endl;

                    AddCellToRefine(Pippo->Id());
            }
            //controlla se bisogna tagliare altri lati nel figlio 2
            if(Pippo2->Edge(2)->HasProperty("LatoDaTagliare")){
                     cout << "Rimando la cella numero: " << Pippo2->Id() << endl;
                     cout << "a destra la numero: " << Pippo2->Edge(2)->RightCell()->Id() << endl;
                     cout << "a sinistra la numero: " << Pippo2->Edge(2)->LeftCell()->Id() << endl;
                    AddCellToRefine(Pippo2->Id());
                }


            latolungo->SetState(false);
    		cellaAttuale->SetState(false);
    		CellsToCut.erase(cellaAttuale);
    	}


    	return Output::Success;
    }
}
