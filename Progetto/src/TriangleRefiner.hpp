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
		vector<bool> idEdgesToCut;

		bool HasMarkedEdges(const GenericCell* C)
		{
			return (idEdgesToCut.at(C->Edge(0)->Id())) or (idEdgesToCut.at(C->Edge(1)->Id())) or (idEdgesToCut.at(C->Edge(2)->Id()));
		}
		bool IsOnBorder(const GenericEdge* E)
		{
			return (E->Cell(0) == NULL) or (E->Cell(1) == NULL);
		}
		GenericPoint* NewPoint()
		{
			GenericPoint* P = meshPointer->CreatePoint();
			meshPointer->AddPoint(P);
			return P;
		}
		GenericEdge* NewEdge()
		{
			GenericEdge* E = meshPointer->CreateEdge();
			meshPointer->AddEdge(E);
			idEdgesToCut.push_back(false);
			return E;
		}
		GenericCell* NewCell()
		{
			GenericCell* C = meshPointer->CreateCell();
			meshPointer->AddCell(C);
			return C;
		}
		void SetEdgeGeometry(GenericEdge* E, const GenericPoint* P0, const GenericPoint* P1, const GenericCell* right, const GenericCell* left)
		{
			//Chiedere a berrone perchè manca E->InitializePoint(2);
			E->AddPoint(P0);
			E->AddPoint(P1);
			E->InitializeCells(2);
			E->AddCell(right);	//RightCell = cell[0]
			E->AddCell(left);	//LeftCell = cell[1]
		}
		void SetFamily(GenericTreeNode* father, GenericTreeNode* C1, GenericTreeNode* C2)
		{
			father->InitializeChilds(2);
			father->AddChild(C1);
			father->AddChild(C2);
			C1->SetFather(father);
			C2->SetFather(father);
		}
		void SetCellPoints(GenericCell* C, const GenericPoint* P0, const GenericPoint* P1, const GenericPoint* P2)
		{
			C->InitializePoints(3);
			C->AddPoint(P0);
			C->AddPoint(P1);
			C->AddPoint(P2);
		}
		void SetCellEdges(GenericCell* C, const GenericEdge* E0, const GenericEdge* E1, const GenericEdge* E2)
		{
			C->InitializeEdges(3);
			C->AddEdge(E0);
			C->AddEdge(E1);
			C->AddEdge(E2);
		}
		const GenericCell* ScegliAltra(const GenericEdge* E, const GenericCell* me)
		{
			if (E->RightCell() == me)
				return E->LeftCell();
			return E->RightCell();
		}

		bool DaDividereinQuattro(const GenericCell* C);
		void RotateCell(GenericCell* C);
		void PensaciTuAlLatoIgnoto(GenericCell* C, GenericEdge* E); // Deve anche far puntare al lato ingoto la cella
		void RefinePairedTriangles(GenericCell* C0, GenericCell* C1);
		void RefineBorderTriangle(GenericCell* C0);
		void Refine4Edges(GenericCell* C);
		static double Distance(const GenericPoint* P1, const GenericPoint* P2) {return (P1->Coordinates()-P2->Coordinates()).norm();}
		const GenericEdge* LongestEdge(const GenericCell* C);
		
		unsigned PrimoDaTagliare(unsigned start);

	public:
		TriangleRefiner() {meshPointer = NULL;}
		~TriangleRefiner() {}

		void SetMesh(GenericMesh& mesh)
		{
			meshPointer = &mesh;
			idEdgesToCut.assign(meshPointer->NumberOfEdges(), false);
		}
		void PrepareForRefineCell(const unsigned int& value);

		Output::ExitCodes RefineMesh();
	};
}

#endif
