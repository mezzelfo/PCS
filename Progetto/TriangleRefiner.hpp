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
	private:
	    /*
         Seguono dichiarazione e definizione di funzioni semplici o di supporto
		*/

        // Ritorna la distanza tra due punti
		static double SqrDistance(const GenericPoint* P1, const GenericPoint* P2)
		{
			return (P1->Coordinates()-P2->Coordinates()).squaredNorm();
		}

		// Ritorna il lato più lungo di una cella
		const GenericEdge* LongestEdge(const GenericCell* C)
		{
			double a = SqrDistance(C->Edge(0)->Point(0),C->Edge(0)->Point(1));
			double b = SqrDistance(C->Edge(1)->Point(0),C->Edge(1)->Point(1));
			double c = SqrDistance(C->Edge(2)->Point(0),C->Edge(2)->Point(1));
			if ((a >= b) and (a >= c))
				return C->Edge(0);
			else if ((b >= a) and (b >= c))
				return C->Edge(1);
			else
				return C->Edge(2);
		}

		// Ritorna true se il triangolo ha almeno un lato marcato
		bool HasMarkedEdges(const GenericCell* C)
		{
			return (idEdgesToCut.at(C->Edge(0)->Id())) or (idEdgesToCut.at(C->Edge(1)->Id())) or (idEdgesToCut.at(C->Edge(2)->Id()));
		}

		// Ritorna true se il lato è sul bordo ovvero confina con una cella NULL
		bool IsOnBorder(const GenericEdge* E)
		{
			return (E->Cell(0) == NULL) or (E->Cell(1) == NULL);
		}

		// Creano in modo corretto e coerente vari tipi di oggetti geometrici
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
			idEdgesToCut.push_back(false);     //Creando un lato è necessario estendere idEdgesToCut perchè lo comprenda
			return E;
		}
		GenericCell* NewCell()
		{
			GenericCell* C = meshPointer->CreateCell();
			meshPointer->AddCell(C);
			return C;
		}

		// Riempie un lato vuoto con informazioni geometriche di punti e celle
		void SetEdgeGeometry(GenericEdge* E, const GenericPoint* P0, const GenericPoint* P1, const GenericCell* right, const GenericCell* left)
		{
			E->AddPoint(P0);
			E->AddPoint(P1);
			E->InitializeCells(2);
			E->AddCell(right);	// RightCell = cell[0]
			E->AddCell(left);	// LeftCell = cell[1]
		}

		// Inizializza le informazioni di parentela fra un padre e due figli
		void SetFamily(GenericTreeNode* father, GenericTreeNode* C1, GenericTreeNode* C2)
		{
			father->InitializeChilds(2);
			father->AddChild(C1);
			father->AddChild(C2);
			C1->SetFather(father);
			C2->SetFather(father);
		}

		// Inizializzano le informazioni geometriche su punti e lati di una cella vuota
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

		/*
		 Seguono dichiarazioni di funzioni algoritmiche importanti o complesse
		*/
		void RotateCell(GenericCell* C);								// Riordina i puntatori a lati e punti del triangolo in modo coerente
		void PensaciTuAlLatoIgnoto(GenericCell* C, GenericEdge* E);		// Sistema le condizioni di vicinanza tra un triangolo ed un lato "esterno"
		void RefinePairedTriangles(GenericCell* C0, GenericCell* C1);	// Taglia contemporanemante due triangoli che condividono il lato lungo
		void RefineBorderTriangle(GenericCell* C0);						// Taglia un triangolo che ha il lato lungo sul bordo della mesh

		/*
			Membri della classe TriangleRefiner
		*/

		GenericMesh* meshPointer;	// Puntatore alla mesh
		vector<bool> idEdgesToCut;	// Vettore di variabili booleane. Se l'elemento n-esimo del vettore è true allora il lato con id = n è da tagliare

	public:
		// Nel costruttore richiedo una mesh e preparo il vettore di bool grande abbastanza
		TriangleRefiner(GenericMesh& mesh)
		{
			meshPointer = &mesh;
			idEdgesToCut.assign(meshPointer->NumberOfEdges(), false);
		}
		~TriangleRefiner()
		{
			meshPointer = NULL;
			idEdgesToCut.clear();
		}

		// Ritorna true se nel vettore c'è ancora almeno un true
		bool anyTriangleToCut()
		{
		for(unsigned edgeId = 0; edgeId < meshPointer->NumberOfEdges(); edgeId++)
			if (idEdgesToCut.at(edgeId))
				return true;

		return false;
		}

		// Funzione che ruota la cella e marca da tagliare il lato più lungo
		void PrepareTriangle(const unsigned int& value);

		// Raffina la mesh in maniera conforme
		Output::ExitCodes RefineMesh();
	};
}

#endif
