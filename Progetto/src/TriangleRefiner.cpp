#include "TriangleRefiner.hpp"

namespace GeDiM
{
    unsigned TriangleRefiner::PrimoDaTagliare(unsigned start)
    {
       for(unsigned edgeId = start; edgeId < meshPointer->NumberOfEdges(); edgeId++)
       {
           if (idEdgesToCut.at(edgeId))
                return edgeId;
       }
       return 9999999;
    }

   	bool TriangleRefiner::DaDividereinQuattro(const GenericCell* C)
	{
		if (idEdgesToCut.at(C->Edge(0)->Id()) and idEdgesToCut.at(C->Edge(1)->Id()) and idEdgesToCut.at(C->Edge(2)->Id()))
		{
			for(int i = 0; i < 3; i++)
			{
				if (C->Edge(i)->HasRightCell() and (C->Edge(i)->RightCell() != C))
				{
					if (LongestEdge(C->Edge(i)->RightCell()) != C->Edge(i))
						return false;
				}
				if (C->Edge(i)->HasLeftCell() and (C->Edge(i)->LeftCell() != C))
				{
					if (LongestEdge(C->Edge(i)->LeftCell()) != C->Edge(i))
						return false;
				}
			}
			return true;
		}
		return false;
	}

	Output::ExitCodes TriangleRefiner::RefineMesh()
	{
	    unsigned vecchio = 0;
	    while(PrimoDaTagliare(0) != 9999999)
        {
            unsigned edgeId = PrimoDaTagliare(vecchio);
            GenericEdge* L = meshPointer->Edge(edgeId);

          	if (not IsOnBorder(L)) // Se il lato è confinante con due triangoli
            {
                GenericCell* C0 = meshPointer->Cell(L->Cell(0)->Id());
                GenericCell* C1 = meshPointer->Cell(L->Cell(1)->Id());
				if (DaDividereinQuattro(C0))
				{
					cerr << "Eccomi1\n" << endl;
					Refine4Edges(C0);
					idEdgesToCut.at(C0->Edge(0)->Id()) = false;
					idEdgesToCut.at(C0->Edge(1)->Id()) = false;
					idEdgesToCut.at(C0->Edge(2)->Id()) = false;
				}
				else if (DaDividereinQuattro(C1))
				{
					cerr << "Eccomi2\n" << endl;
					Refine4Edges(C1);
					idEdgesToCut.at(C0->Edge(0)->Id()) = false;
					idEdgesToCut.at(C0->Edge(1)->Id()) = false;
					idEdgesToCut.at(C0->Edge(2)->Id()) = false;
				}
                else if (LongestEdge(C0) == LongestEdge(C1))
                {
                    RefinePairedTriangles(C0,C1);
                    idEdgesToCut.at(edgeId) = false;
                }

            }
            else // Se il lato è di bordo
            {
                GenericCell* C0;
                if (L->Cell(0) == NULL) C0 = meshPointer->Cell(L->Cell(1)->Id());
                if (L->Cell(1) == NULL) C0 = meshPointer->Cell(L->Cell(0)->Id());
				if (DaDividereinQuattro(C0))
				{
					cerr << "Eccomi3" << endl;
					Refine4Edges(C0);
					idEdgesToCut.at(C0->Edge(0)->Id()) = false;
					idEdgesToCut.at(C0->Edge(1)->Id()) = false;
					idEdgesToCut.at(C0->Edge(2)->Id()) = false;
				}
				else
				{
					RefineBorderTriangle(C0);
					idEdgesToCut.at(edgeId) = false;
				}
                
            }
			
            if(L->IsActive())
			{
				vecchio = (vecchio+1)%meshPointer->NumberOfEdges();
				if (L->HasRightCell()) PrepareForRefineCell(L->RightCell()->Id());
				if (L->HasLeftCell()) PrepareForRefineCell(L->LeftCell()->Id());
			}
            else
                vecchio = 0;
		}
		return Output::Success;
	}
	const GenericEdge* TriangleRefiner::LongestEdge(const GenericCell* C)
	{
		double a = Distance(C->Edge(0)->Point(0),C->Edge(0)->Point(1));
		double b = Distance(C->Edge(1)->Point(0),C->Edge(1)->Point(1));
		double c = Distance(C->Edge(2)->Point(0),C->Edge(2)->Point(1));
		if ((a >= b) and (a >= c))
			return C->Edge(0);
		else if ((b >= a) and (b >= c))
			return C->Edge(1);
		else
			return C->Edge(2);
	}
	void TriangleRefiner::RotateCell(GenericCell* C)
	{
		GenericEdge* L = meshPointer->Edge(LongestEdge(C)->Id());
		// Rotate Edge
		if (L == C->Edge(1))
		{
			C->InsertEdge(C->Edge(2),1);
            C->InsertEdge(C->Edge(0),2);
			C->InsertEdge(L,0);
		}
		else if (L == C->Edge(2))
		{
			C->InsertEdge(C->Edge(1),2);
            C->InsertEdge(C->Edge(0),1);
			C->InsertEdge(L,0);
		}
		// Rotate Points
		while ((C->Point(2) == L->Point(0)) or (C->Point(2) == L->Point(1)))
		{
			const GenericPoint* tmp = C->Point(0);
			C->InsertPoint(C->Point(2),0);
            C->InsertPoint(C->Point(1),2);
			C->InsertPoint(tmp,1);
		}
	}
	void TriangleRefiner::PrepareForRefineCell(const unsigned int& value)
	{
		GenericCell* C = meshPointer->Cell(value);
		const GenericEdge* L = LongestEdge(C);
		idEdgesToCut.at(L->Id()) = true;
		RotateCell(C);	// Forse si può togliere
	}
	void TriangleRefiner::PensaciTuAlLatoIgnoto(GenericCell* C, GenericEdge* E) // Deve anche far puntare al lato ingoto la cella
	{
		if (E->Cell(0) == C->Father())
		{
			E->InsertCell(C,0);
			C->AddCell(E->Cell(1));
		}
		else
		{
			E->InsertCell(C,1);
			C->AddCell(E->Cell(0));
		}
	}
	void TriangleRefiner::RefinePairedTriangles(GenericCell* C0, GenericCell* C1)
	{
		RotateCell(C0);
		RotateCell(C1);

		// Get longest edge from any of the input cells
		GenericEdge* longest = meshPointer->Edge(LongestEdge(C0)->Id());

		// Create empty objects
		GenericPoint* midpoint = NewPoint();

		GenericEdge* subEdge0 = NewEdge();	//Children of longest edge
		GenericEdge* subEdge1 = NewEdge();

		GenericEdge* median0 = NewEdge();
		GenericEdge* median1 = NewEdge();

		GenericCell* C0_0 = NewCell();	//Children of the two cell
		GenericCell* C0_1 = NewCell();
		GenericCell* C1_0 = NewCell();
		GenericCell* C1_1 = NewCell();

		SetFamily(longest,subEdge0,subEdge1);
		SetFamily(C0,C0_0,C0_1);
		SetFamily(C1,C1_0,C1_1);

		// set midpoint coordinates
		midpoint->SetCoordinates(0.5*(longest->Point(0)->Coordinates()+longest->Point(1)->Coordinates()));

		SetEdgeGeometry(subEdge0,C0->Point(0),midpoint,C1_0,C0_0);

		SetEdgeGeometry(subEdge1,midpoint,C0->Point(1),C1_1,C0_1);

		SetEdgeGeometry(median0,C0->Point(2),midpoint,C0_0,C0_1);

		SetEdgeGeometry(median1,midpoint,C1->Point(2),C1_0,C1_1);

		SetCellPoints(C0_0,C0->Point(0),midpoint,C0->Point(2));
		SetCellEdges(C0_0,subEdge0,median0,C0->Edge(2));
		//C0_0->InitializeCells(3);
		C0_0->AddCell(C1_0);
		C0_0->AddCell(C0_1);
		PensaciTuAlLatoIgnoto(C0_0, meshPointer->Edge(C0->Edge(2)->Id()));

		SetCellPoints(C0_1,midpoint,C0->Point(1),C0->Point(2));
		SetCellEdges(C0_1,median0,subEdge1,C0->Edge(1));
		//C0_1->InitializeCells(3);
		C0_1->AddCell(C0_0);
		C0_1->AddCell(C1_1);
		PensaciTuAlLatoIgnoto(C0_1, meshPointer->Edge(C0->Edge(1)->Id()));


		SetCellPoints(C1_0,C0->Point(0),C1->Point(2),midpoint);
		SetCellEdges(C1_0,median1,subEdge0,C1->Edge(1));
		//C1_0->InitializeCells(3);
		C1_0->AddCell(C1_1);
		C1_0->AddCell(C0_0);
		PensaciTuAlLatoIgnoto(C1_0, meshPointer->Edge(C1->Edge(1)->Id()));


		SetCellPoints(C1_1,midpoint,C1->Point(2),C0->Point(1));
		SetCellEdges(C1_1,subEdge1,median1,C1->Edge(2));
		//C1_1->InitializeCells(3);
		C1_1->AddCell(C0_1);
		C1_1->AddCell(C1_0);
		PensaciTuAlLatoIgnoto(C1_1, meshPointer->Edge(C1->Edge(2)->Id()));



		C0->SetState(false);
		C1->SetState(false);
		longest->SetState(false);

		if (HasMarkedEdges(C0_0))
			PrepareForRefineCell(C0_0->Id());
		if (HasMarkedEdges(C0_1))
			PrepareForRefineCell(C0_1->Id());
		if (HasMarkedEdges(C1_0))
			PrepareForRefineCell(C1_0->Id());
		if (HasMarkedEdges(C1_1))
			PrepareForRefineCell(C1_1->Id());

	}
	void TriangleRefiner::RefineBorderTriangle(GenericCell* C0)
	{
		// Get longest edge from any of the input cells
		GenericEdge* longest = meshPointer->Edge(LongestEdge(C0)->Id());
		RotateCell(C0);

		// Create empty objects
		GenericPoint* midpoint = NewPoint();

		GenericEdge* subEdge0 = NewEdge();	//Children of longest edge
		GenericEdge* subEdge1 = NewEdge();

		GenericEdge* median0 = NewEdge();

		GenericCell* C0_0 = NewCell();	//Children of the two cell
		GenericCell* C0_1 = NewCell();

		SetFamily(longest,subEdge0,subEdge1);
		SetFamily(C0,C0_0,C0_1);

		// set midpoint coordinates
		midpoint->SetCoordinates(0.5*(longest->Point(0)->Coordinates()+longest->Point(1)->Coordinates()));

		SetEdgeGeometry(subEdge0,C0->Point(0),midpoint,NULL,C0_0);
		SetEdgeGeometry(subEdge1,midpoint,C0->Point(1),NULL,C0_1);
		SetEdgeGeometry(median0,C0->Point(2),midpoint,C0_0,C0_1);

		SetCellPoints(C0_0,C0->Point(0),midpoint,C0->Point(2));
		SetCellEdges(C0_0,subEdge0,median0,C0->Edge(2));
		//C0_0->InitializeCells(2);
		C0_0->AddCell(C0_1);
		PensaciTuAlLatoIgnoto(C0_0, meshPointer->Edge(C0->Edge(2)->Id()));
		C0_0->AddCell(NULL);

		SetCellPoints(C0_1,midpoint,C0->Point(1),C0->Point(2));
		SetCellEdges(C0_1,median0,subEdge1,C0->Edge(1));
		//C0_1->InitializeCells(2);
		PensaciTuAlLatoIgnoto(C0_1, meshPointer->Edge(C0->Edge(1)->Id()));
		C0_1->AddCell(C0_0);
		C0_1->AddCell(NULL);


		C0->SetState(false);
		longest->SetState(false);

		if (HasMarkedEdges(C0_0))
			PrepareForRefineCell(C0_0->Id());
		if (HasMarkedEdges(C0_1))
			PrepareForRefineCell(C0_1->Id());
	}
	void TriangleRefiner::Refine4Edges(GenericCell* C){

       	// Non mi serve più l'info del lato più lungo quindi forse si può togliere rotatecell
        RotateCell(C);

        GenericPoint* P0 = meshPointer->Point(C->Point(0)->Id());
        GenericPoint* P1 = meshPointer->Point(C->Point(1)->Id());
        GenericPoint* P2 = meshPointer->Point(C->Point(2)->Id());
        GenericEdge* L0 = meshPointer->Edge(C->Edge(0)->Id());
        GenericEdge* L1 = meshPointer->Edge(C->Edge(1)->Id());
        GenericEdge* L2 =  meshPointer->Edge(C->Edge(2)->Id());


        GenericCell* CL0 = meshPointer->Cell(ScegliAltra(L0,C)->Id());
        GenericCell* CL1 = meshPointer->Cell(ScegliAltra(L1,C)->Id());
        GenericCell* CL2 = meshPointer->Cell(ScegliAltra(L2,C)->Id());

        GenericCell* CL0_0 = (CL0 != NULL) ? NewCell() : NULL;
		GenericCell* CL0_1 = (CL0 != NULL) ? NewCell() : NULL;
		GenericEdge* median0 = (CL0 != NULL) ? NewEdge() : NULL;

        GenericCell* CL1_0 = NewCell();
        GenericCell* CL1_1 = NewCell();
        GenericCell* CL2_0 = NewCell();
        GenericCell* CL2_1 = NewCell();

        GenericEdge* median1 = NewEdge();
        GenericEdge* median2 = NewEdge();

        GenericPoint* Pm0= NewPoint(), *Pm1= NewPoint(), *Pm2 = NewPoint();
        GenericEdge *E0= NewEdge(), *E1= NewEdge(), *E2= NewEdge(), *E3= NewEdge(), *E4= NewEdge(), *E5= NewEdge(), *E6= NewEdge(), *E7= NewEdge(), *E8 = NewEdge();
        GenericCell *C0= NewCell(), *C1= NewCell(),*C2= NewCell(), *C3= NewCell();

        C->InitializeChilds(4);
		C->AddChild(C0);
		C->AddChild(C1);
		C->AddChild(C2);
		C->AddChild(C3);
		C0->SetFather(C);
		C1->SetFather(C);
		C2->SetFather(C);
		C3->SetFather(C);

        if (CL0 != NULL) SetFamily(CL0, CL0_0, CL0_1);
        SetFamily(CL1, CL1_0, CL1_1);
        SetFamily(CL2, CL2_0, CL2_1);
        SetFamily(L0, E0, E1);
        SetFamily(L1, E2, E3);
        SetFamily(L2, E4, E5);

        // Inizializzo i punti medi

        Pm0->SetCoordinates(0.5*(P0->Coordinates()+P1->Coordinates()));
        Pm1->SetCoordinates(0.5*(P1->Coordinates()+P2->Coordinates()));
        Pm2->SetCoordinates(0.5*(P2->Coordinates()+P0->Coordinates()));

        if (CL0 != NULL)
		{
			RotateCell(CL0);
        	SetEdgeGeometry(median0, Pm0, CL0->Point(2), CL0_0, CL0_1);
		}
        RotateCell(CL1);
        SetEdgeGeometry(median1, Pm1, CL1->Point(2), CL1_0, CL1_1);
        RotateCell(CL2);
        SetEdgeGeometry(median2, Pm2, CL2->Point(2), CL2_0, CL2_1);

        SetEdgeGeometry(E0, P0, Pm0, CL0_0, C0);
        SetEdgeGeometry(E1, Pm0, P1, CL0_1, C1);
        SetEdgeGeometry(E2, P1, Pm1, CL1_0, C1);
        SetEdgeGeometry(E3, Pm1, P2, CL1_1, C2);
        SetEdgeGeometry(E4, P2, Pm2, CL2_0, C2);
        SetEdgeGeometry(E3, Pm2, P0, CL2_1, C0);

        SetEdgeGeometry(E6, Pm2, Pm0, C0, C3);
        SetEdgeGeometry(E7, Pm0, Pm1, C1, C3);
        SetEdgeGeometry(E8, Pm1, Pm2, C2, C3);


        //Inizializzo le celle

        if(CL0 != NULL)
		{
			SetCellPoints(CL0_0, Pm0, P0, CL0->Point(2));
			SetCellEdges(CL0_0,E0,CL0->Edge(1),median0);
			// TODO: Verso antiorario? Manca comunque una cella
			CL0_0->AddCell(CL0_1);
			PensaciTuAlLatoIgnoto(CL0_0, meshPointer->Edge(CL0->Edge(2)->Id()));

			SetCellPoints(CL0_1, CL0->Point(1),Pm1,CL0->Point(2));
			SetCellEdges(CL0_1,E1,median1,CL0->Edge(1));
			// TODO: Verso antiorario? Manca comunque una cella	
			CL0_1->AddCell(CL0_0);
			PensaciTuAlLatoIgnoto(CL0_1, meshPointer->Edge(CL0->Edge(1)->Id()));
		}

        SetCellPoints(CL1_0, CL1->Point(0),CL1->Point(2),Pm1);
		SetCellEdges(CL1_0,CL1->Edge(2),median1, E2);
		CL1_0->AddCell(CL1_1);
		PensaciTuAlLatoIgnoto(CL1_0, meshPointer->Edge(CL1->Edge(2)->Id()));
		

        SetCellPoints(CL1_1, CL1->Point(1),Pm1,CL1->Point(2));
		SetCellEdges(CL1_1,E3,median1,CL1->Edge(1));
		CL1_1->AddCell(CL1_0);
		PensaciTuAlLatoIgnoto(CL1_1, meshPointer->Edge(CL1->Edge(1)->Id()));


        SetCellPoints(CL2_0, CL2->Point(0),CL2->Point(2),Pm2);
		SetCellEdges(CL2_0,CL2->Edge(2),median2, E4);
		CL2_0->AddCell(CL2_1);
		PensaciTuAlLatoIgnoto(CL2_0, meshPointer->Edge(CL2->Edge(2)->Id()));

        SetCellPoints(CL2_1, CL2->Point(1),Pm2,CL2->Point(2));
		SetCellEdges(CL2_1,E5,median2,CL0->Edge(1));
		CL2_1->AddCell(CL2_0);
		PensaciTuAlLatoIgnoto(CL2_1, meshPointer->Edge(CL2->Edge(1)->Id()));

		// E le celle confinanti?
        SetCellPoints(C0,P0,Pm0,Pm2);
		SetCellEdges(C0,E0,E6,E5);

		SetCellPoints(C1,Pm0,P1,Pm1);
		SetCellEdges(C1,E1,E2,E7);

		SetCellPoints(C2,Pm1,P2,Pm2);
		SetCellEdges(C2,E3,E4,E8);

		SetCellPoints(C3,Pm2,Pm0,Pm1);
		SetCellEdges(C3,E6,E7,E8);

        C->SetState(false);
        if (CL0 != NULL) CL0->SetState(false);
        CL1->SetState(false);
        CL2->SetState(false);
		L0->SetState(false);
		L1->SetState(false);
		L2->SetState(false);


    }
}

