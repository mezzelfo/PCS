#include "TriangleRefiner.hpp"

namespace GeDiM
{
	Output::ExitCodes TriangleRefiner::RefineMesh()
	{
		unsigned edgeId = 0;
		while(anyTriangleToCut())		
		{
			edgeId = (edgeId+1)%meshPointer->NumberOfEdges();
			if (not idEdgesToCut.at(edgeId))
				continue;

			GenericEdge* L = meshPointer->Edge(edgeId);

			if (IsOnBorder(L))
			{
				GenericCell* C0;
				if (L->Cell(0) == NULL) C0 = meshPointer->Cell(L->Cell(1)->Id());
				if (L->Cell(1) == NULL) C0 = meshPointer->Cell(L->Cell(0)->Id());
				RefineBorderTriangle(C0);
				idEdgesToCut.at(edgeId) = false;
			}
			else if (LongestEdge(L->Cell(0)) == LongestEdge(L->Cell(1)))
			{
				GenericCell* C0 = meshPointer->Cell(L->Cell(0)->Id());
				GenericCell* C1 = meshPointer->Cell(L->Cell(1)->Id());
				RefinePairedTriangles(C0,C1);
				idEdgesToCut.at(edgeId) = false;
			}
			else
			{
				if (L->HasRightCell()) PrepareTriangle(L->RightCell()->Id());
				if (L->HasLeftCell()) PrepareTriangle(L->LeftCell()->Id());
			}
		}
		return Output::Success;
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
	void TriangleRefiner::PrepareTriangle(const unsigned int& value)
	{
		GenericCell* C = meshPointer->Cell(value);
		const GenericEdge* L = LongestEdge(C);
		idEdgesToCut.at(L->Id()) = true;
		RotateCell(C);
	}
	void TriangleRefiner::PensaciTuAlLatoIgnoto(GenericCell* C, GenericEdge* E)
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
			PrepareTriangle(C0_0->Id());
		if (HasMarkedEdges(C0_1))
			PrepareTriangle(C0_1->Id());
		if (HasMarkedEdges(C1_0))
			PrepareTriangle(C1_0->Id());
		if (HasMarkedEdges(C1_1))
			PrepareTriangle(C1_1->Id());

	}
	void TriangleRefiner::RefineBorderTriangle(GenericCell* C0)
	{
		RotateCell(C0);
		// Get longest edge from any of the input cells
		GenericEdge* longest = meshPointer->Edge(LongestEdge(C0)->Id());

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
			PrepareTriangle(C0_0->Id());
		if (HasMarkedEdges(C0_1))
			PrepareTriangle(C0_1->Id());
	}
}
