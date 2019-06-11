#ifndef TRIANGLEREFINER_HPP
#define TRIANGLEREFINER_HPP

#include "GenericDomain.hpp"
#include "GenericMesh.hpp"
#include "Eigen/Eigen"
#include <set>

using namespace std;
using namespace Eigen;

namespace GeDiM
{
class TriangleRefiner
{
protected:
	GenericMesh *meshPointer;
	set<unsigned int> idCellsToRefine;

public:
	TriangleRefiner() { meshPointer = NULL; }
	~TriangleRefiner() {}

	void SetMesh(GenericMesh &mesh) { meshPointer = &mesh; }
	void AddCellId(const unsigned int &value) { idCellsToRefine.emplace(value); }

	Output::ExitCodes RefineMesh()
	{
		while (!idCellsToRefine.empty())
		{
			int id = *idCellsToRefine.begin();
			std::cout << "raffino cella id: " << id << std::endl;
			RefineTriangle(id);
			idCellsToRefine.erase(id);
		}
		return Output::Success;
	}
	Output::ExitCodes RefineTriangle(const unsigned int &value);
	void RotateCell(GenericCell *C)
	{
		GenericEdge *L = meshPointer->Edge(LongestEdge(C)->Id()); // Creo un puntatore al lato pi� lungo del triangolo
		// Ruoto i lati al fine di avere L in posizione 0 e mantenendo il verso antiorario della rappresentazione
		if (L == C->Edge(1))
		{
			C->InsertEdge(C->Edge(2), 1);
			C->InsertEdge(C->Edge(0), 2);
			C->InsertEdge(L, 0);
		}
		else if (L == C->Edge(2))
		{
			C->InsertEdge(C->Edge(1), 2);
			C->InsertEdge(C->Edge(0), 1);
			C->InsertEdge(L, 0);
		}
		// Ruoto i punti fino a quando quello in posizione 2 non appartiene pi� al lato pi� lungo L
		while ((C->Point(2) == L->Point(0)) or (C->Point(2) == L->Point(1)))
		{
			const GenericPoint *tmp = C->Point(0); // Creo una variabile temporanea per effettuare gli scambi di posizione
			C->InsertPoint(C->Point(2), 0);
			C->InsertPoint(C->Point(1), 2);
			C->InsertPoint(tmp, 1);
		}
	}
	const GenericEdge *LongestEdge(const GenericCell *C)
	{
		double a = SqrDistance(C->Edge(0)->Point(0), C->Edge(0)->Point(1));
		double b = SqrDistance(C->Edge(1)->Point(0), C->Edge(1)->Point(1));
		double c = SqrDistance(C->Edge(2)->Point(0), C->Edge(2)->Point(1));
		if ((a >= b) and (a >= c))
			return C->Edge(0);
		else if ((b >= a) and (b >= c))
			return C->Edge(1);
		else
			return C->Edge(2);
	}
	static double SqrDistance(const GenericPoint *P1, const GenericPoint *P2)
	{
		return (P1->Coordinates() - P2->Coordinates()).squaredNorm();
	}
	GenericPoint *NewPoint()
	{
		GenericPoint *P = meshPointer->CreatePoint();
		meshPointer->AddPoint(P);
		return P;
	}
	GenericEdge *NewEdge()
	{
		GenericEdge *E = meshPointer->CreateEdge();
		meshPointer->AddEdge(E);
		return E;
	}
	GenericCell *NewCell()
	{
		GenericCell *C = meshPointer->CreateCell();
		meshPointer->AddCell(C);
		return C;
	}

	// Riempie un lato vuoto con informazioni geometriche di punti e celle
	void SetEdgeGeometry(GenericEdge *E, const GenericPoint *P0, const GenericPoint *P1, const GenericCell *right, const GenericCell *left)
	{
		E->AddPoint(P0);
		E->AddPoint(P1);
		E->InitializeCells(2);
		E->AddCell(right); // RightCell = cell[0]
		E->AddCell(left);  // LeftCell = cell[1]
	}

	// Inizializza le informazioni di parentela fra un padre e due figli
	void SetFamily(GenericTreeNode *father, GenericTreeNode *C1, GenericTreeNode *C2)
	{
		father->InitializeChilds(2);
		father->AddChild(C1);
		father->AddChild(C2);
		C1->SetFather(father);
		C2->SetFather(father);
	}

	// Inizializzano le informazioni geometriche su punti e lati di una cella vuota
	void SetCellPoints(GenericCell *C, const GenericPoint *P0, const GenericPoint *P1, const GenericPoint *P2)
	{
		C->InitializePoints(3);
		C->AddPoint(P0);
		C->AddPoint(P1);
		C->AddPoint(P2);
	}
	void SetCellEdges(GenericCell *C, const GenericEdge *E0, const GenericEdge *E1, const GenericEdge *E2)
	{
		C->InitializeEdges(3);
		C->AddEdge(E0);
		C->AddEdge(E1);
		C->AddEdge(E2);
	}
	int puntocomune(const GenericEdge *A, const GenericEdge *B)
	{
		if (A->Point(0)->Id() == B->Point(0)->Id())
			return A->Point(0)->Id();
		else if (A->Point(0)->Id() == B->Point(1)->Id())
			return A->Point(0)->Id();
		else if (A->Point(1)->Id() == B->Point(0)->Id())
			return A->Point(1)->Id();
		else if (A->Point(1)->Id() == B->Point(1)->Id())
			return A->Point(1)->Id();
		else
		{
			std::cerr << "nope1" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
};
} // namespace GeDiM

#endif
