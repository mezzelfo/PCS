#include "TriangleRefiner.hpp"

namespace GeDiM
{
    double distance(const GenericPoint* A, const GenericPoint* B)
    {
        return((A->Coordinates()-B->Coordinates()).norm());
    }
	const GenericEdge* LongestEdgePtr(const GenericCell* cell)
    {
        // Sono veramente un triangolo?
        assert(cell->NumberOfPoints() == 3);
        assert(cell->NumberOfEdges() == 3);

        double a = distance(cell->Edge(0)->Point(0),cell->Edge(0)->Point(1));
        double b = distance(cell->Edge(1)->Point(0),cell->Edge(1)->Point(1));
        double c = distance(cell->Edge(2)->Point(0),cell->Edge(2)->Point(1));
        if ((a > b) and (a > c))
            return cell->Edge(0);
        else if (b > c)
            return cell->Edge(1);
        else
            return cell->Edge(2);
    }
	Output::ExitCodes correggiOrientamento(GenericCell* cell)
    {
        // Sono veramente un triangolo?
        assert(cell->NumberOfPoints() == 3);
        assert(cell->NumberOfEdges() == 3);

        // Ruoto i vertici in modo che points[0] == LongestEdgePtr->Point(0)
        // Il punto 0 del lato più lungo è costante
        const GenericEdge* longestEdge = LongestEdgePtr(cell);
        const GenericPoint* P = longestEdge->Point(0);
        if (cell->Point(0) == P)
        {
            //niente da fare
        }
        else if (cell->Point(1) == P)
        {
            // ruoto da una parte
            cell->InsertPoint(cell->Point(2),1);
            cell->InsertPoint(cell->Point(0),2);
            cell->InsertPoint(P,0);

            //cell->InsertEdge(cell->Edge(2),1);
            //cell->InsertEdge(cell->Edge(0),2);
            //cell->InsertEdge(longestEdge,0);
        }
        else if (cell->Point(2) == P)
        {
            // ruoto dall'altra parte
            cell->InsertPoint(cell->Point(1),2);
            cell->InsertPoint(cell->Point(0),1);
            cell->InsertPoint(P,0);

            //cell->InsertEdge(cell->Edge(1),2);
            //cell->InsertEdge(cell->Edge(0),1);
            //cell->InsertEdge(longestEdge,0);
        }
        else
        {
            cerr << "Punto non trovato\n";
            //return Output::GenericError;
        }

        if (cell->Edge(0) == longestEdge)
        {
            //niente da fare
        }
        else if (cell->Edge(1) == longestEdge)
        {
            // ruoto da una parte
            cell->InsertEdge(cell->Edge(2),1);
            cell->InsertEdge(cell->Edge(0),2);
            cell->InsertEdge(longestEdge,0);
        }
        else if (cell->Edge(2) == longestEdge)
        {
            // ruoto dall'altra parte
            cell->InsertEdge(cell->Edge(1),2);
            cell->InsertEdge(cell->Edge(0),1);
            cell->InsertEdge(longestEdge,0);
        }
        else
        {
            cerr << "Lato non trovato\n";
            //return Output::GenericError;
        }
        return Output::Success;
    }

    TriangleRefiner::TriangleRefiner() { meshPointer = NULL;}
	TriangleRefiner::~TriangleRefiner() { }
	void TriangleRefiner::SetMesh( GenericMesh& mesh )
    {
        meshPointer = &mesh;
        cellsToCut.assign(meshPointer->NumberOfCells(),false);
        edgesToCut.assign(meshPointer->NumberOfEdges(),false);
    }
    void TriangleRefiner::AddCellToRefine( const unsigned int& value )
    {
        // Se la cella è già stata segnata come da raffinare allora esco subito
        if (cellsToCut.at(value) == true) return;
        // Altrimenti la setto da raffinare
        cellsToCut.at(value) = true;
        // La oriento nel modo corretto
        GenericCell* cellaAttuale = meshPointer->Cell(value);
        correggiOrientamento(cellaAttuale);

        // Setto da tagliare il lato più lungo
        const GenericEdge* longestEdge = LongestEdgePtr(cellaAttuale);
        edgesToCut.at(longestEdge->Id()) = true;
        // Poi ricorro sui vicini
        if ((longestEdge->RightCell() != NULL) and (longestEdge->RightCell() != cellaAttuale))
            AddCellToRefine(longestEdge->RightCell()->Id());
        else if ((longestEdge->LeftCell() != NULL) and (longestEdge->LeftCell() != cellaAttuale))
            AddCellToRefine(longestEdge->LeftCell()->Id());
        else
        {
            // Vuol dire che sono sul bordo
            if (!((longestEdge->RightCell() == NULL) and (longestEdge->LeftCell() == cellaAttuale)) or
                ((longestEdge->LeftCell() == NULL) and (longestEdge->RightCell() == cellaAttuale)))
                {
                    cerr << "Davvero?\n";
                    cerr << cellaAttuale << '\t' << longestEdge->RightCell() << '\t' << longestEdge->LeftCell() << '\n';
                }   
        }

        return;
    }
    void TriangleRefiner::tagliaLato(GenericEdge* l)
    {
        assert(l->NumberOfPoints() == 2);
        const GenericPoint*P0 = l->Point(0);
        const GenericPoint*P1 = l->Point(1);
        
        GenericPoint* Pm = meshPointer->CreatePoint();
        GenericEdge* E0 = meshPointer->CreateEdge();
        GenericEdge* E1 = meshPointer->CreateEdge();

        meshPointer->AddPoint(Pm);
        meshPointer->AddEdge(E0);
        meshPointer->AddEdge(E1);
        
        Pm->SetCoordinates(0.5*(P0->Coordinates()+P1->Coordinates()));
                
        E0->AddPoint(P0);
        E0->AddPoint(Pm);
        E1->AddPoint(Pm);
        E1->AddPoint(P1);

        E0->SetFather(l);
        E1->SetFather(l);

        assert(l->NumberOfChilds() == 0);
        l->AddChild(E0);
        l->AddChild(E1);
        
    }
    void TriangleRefiner::fillCell(GenericCell* c, const vector<const GenericPoint*> pointList, const vector<const GenericEdge*> edgeList)
    {
        assert(c->NumberOfPoints() == 0);
        assert(c->NumberOfEdges() == 0);
        c->AddPoint(pointList[0]);
        c->AddPoint(pointList[1]);
        c->AddPoint(pointList[2]);
        // Inserisco i lati su cui insite la prima sotto-cella
        c->AddEdge(edgeList[0]);
        c->AddEdge(edgeList[1]);
        c->AddEdge(edgeList[2]);
        assert(c->NumberOfPoints() == 3);
        assert(c->NumberOfEdges() == 3);
    }
    Output::ExitCodes TriangleRefiner::RefineMesh()
    {
    	for(unsigned int cellId = 0; cellId < meshPointer->NumberOfCells(); cellId++)
        {
            if (cellsToCut.at(cellId) == true)
            {
                // La preparo per essere tagliata
                AddCellToRefine(cellId);

                // Ingredienti che mi servono
                GenericCell* cell = meshPointer->Cell(cellId);
                assert(cell->NumberOfChilds()==0);
                
                GenericEdge* longestEdge = meshPointer->Edge(LongestEdgePtr(cell)->Id());
                const GenericPoint* P0 = longestEdge->Point(0);
                const GenericPoint* P1 = longestEdge->Point(1);
                const GenericPoint* Pp = cell->Point(2); // Punto opposto al lato lungo
                GenericEdge* L0 = meshPointer->Edge(cell->Edge(1)->Id());
                GenericEdge* L1 = meshPointer->Edge(cell->Edge(2)->Id());

                GenericCell* C0 = meshPointer->CreateCell();
                GenericCell* C1 = meshPointer->CreateCell();
                meshPointer->AddCell(C0);
                meshPointer->AddCell(C1);
                cellsToCut.push_back(false);
                cellsToCut.push_back(false);

                GenericEdge* Ee = meshPointer->CreateEdge();
                meshPointer->AddEdge(Ee);
                edgesToCut.push_back(false);

                GenericPoint* Pm;
                GenericEdge *E0, *E1;
                
                if (not(longestEdge->HasChilds()))
                {
                    tagliaLato(longestEdge);
                    E0 = (GenericEdge*)longestEdge->Child(0);
                    E1 = (GenericEdge*)longestEdge->Child(1);
                    Pm = meshPointer->Point(E0->Point(1)->Id());
                    // Devo allungare i vettori di bool
                    // Ho creato 2 edge (i due sotto lati nella funzione taglialato)
                    edgesToCut.push_back(false);
                    edgesToCut.push_back(false);
                }
                else
                {
                    E0 = (GenericEdge*)longestEdge->Child(1);  //bisogna invertire gli indici per rispettare l'orientamento
                    E1 = (GenericEdge*)longestEdge->Child(0);
                    Pm = meshPointer->Point(E0->Point(0)->Id());  //sono nel passato
                    assert(Pm == E1->Point(1));
                }

                cell->AddChild(C0);                // Parentela
                cell->AddChild(C1);
                C0->SetFather(cell);
                C1->SetFather(cell);


                // Inserisco i punti su cui insiste la mediana
                Ee->AddPoint(Pp);
                Ee->AddPoint(Pm);

                fillCell(C0,{Pm,Pp,P0},{Ee,L1,E0});
                
                fillCell(C1,{Pm,P1,Pp},{E1,L0,Ee});

                // Aggiorno le informazioni di vicinanza
                // Punto medio balza perchè è un punto e i punti non hanno diritti

                // Per i lati RightCell = cells[0]
                // Primo/secondo sottosegmento si appoggia all'ignoto da una parte e da C0/C1 sull'altra

                E0->AddCell(C0);
                E1->AddCell(C1);                //E0->AllocateCells(2);
                assert(E0->NumberOfCells() <= 2);
                assert(E1->NumberOfCells() <= 2);

                // Mediana del lato lungo
                Ee->AddCell(C0);
                Ee->AddCell(C1);

                //assert((L1->Cell(0) == cell) or (L1->Cell(1) == cell));
                //assert((L0->Cell(0) == cell) or (L0->Cell(1) == cell));

                if (L1->Cell(0) == cell)
                    L1->InsertCell(C0,0);
                else if (L1->Cell(1) == cell)
                    L1->InsertCell(C0,1);
                else
                {
                    cerr << "Un altro errore1\n";
                    cerr << cell << '\t' << L1->Cell(0) << '\t' << L1->Cell(1) << '\n';
                }
                    

                if (L0->Cell(0) == cell)
                    L0->InsertCell(C1,0);
                else if (L0->Cell(1) == cell)
                    L0->InsertCell(C1,1);
                else
                {
                    cerr << "Un altro errore2\n";
                    cerr << cell << '\t' << L0->Cell(0) << '\t' << L0->Cell(1) << '\n';
                }  
                
                // Ora ho tagliato il lato più lungo e ho raffinato la cella
                cellsToCut.at(cellId) = false;
                edgesToCut.at(longestEdge->Id()) = false; // Forse questa riga non va qua ma nell'if        TODO
                
                // Se una delle celle ha almeno un lato da tagliare è da raffinare
                if (edgesToCut.at(C0->Edge(0)->Id()) or
                    edgesToCut.at(C0->Edge(1)->Id()) or
                    edgesToCut.at(C0->Edge(2)->Id()))
                    AddCellToRefine(C0->Id());

                if (edgesToCut.at(C1->Edge(0)->Id()) or
                    edgesToCut.at(C1->Edge(1)->Id()) or
                    edgesToCut.at(C1->Edge(2)->Id()))
                    AddCellToRefine(C1->Id());



                // Ricontrollo tutto il vettore
                cellId = 0;
            }
        }
    	return Output::Success;
    }

    //DA INCORPORARE

    Output::ExitCodes TriangleRefiner::Raffinamento4latiDatagliare()
    {

    for(unsigned int cellId = 0; cellId < meshPointer->NumberOfCells(); cellId++)
        {
            if (cellsToCut.at(cellId) == true)
            {

        // Ingredienti che mi servono
        GenericCell* cell = meshPointer->Cell(cellId);

       // Non mi serve più l'info del lato più lungo, nè ruotarlo
        GenericPoint* P0 = meshPointer->Point(cell->Point(0)->Id());
        GenericPoint* P1 = meshPointer->Point(cell->Point(1)->Id());
        GenericPoint* P2 = meshPointer->Point(cell->Point(2)->Id());
        GenericEdge* L0 = meshPointer->Edge(cell->Edge(0)->Id());
        GenericEdge* L1 = meshPointer->Edge(cell->Edge(1)->Id());
        GenericEdge* L2 =  meshPointer->Edge(cell->Edge(2)->Id());

         GenericPoint* Pm0, *Pm1, *Pm2;
         GenericEdge *E0, *E1, *E2, *E3, *E4, *E5, *E6, *E7, *E8;
         GenericCell *C0, *C1,*C2, *C3;

         // Creo i punti medi e li aggiungo alla struttura

        Pm0 = meshPointer->CreatePoint();  // Punto medio del lato L0
        meshPointer->AddPoint(Pm0);
        Pm1 = meshPointer->CreatePoint();  // Punto medio del lato L1
        meshPointer->AddPoint(Pm1);
        Pm2 = meshPointer->CreatePoint();  // Punto medio del lato L2
        meshPointer->AddPoint(Pm2);

        //Creo i lati nuovi e li aggiungo alla struttura

        E0 = meshPointer->CreateEdge();    // Primo sotto-segmento del lato L0(da P0 a PmO )
        meshPointer->AddEdge(E0);
        E1 = meshPointer->CreateEdge();    // Secondo sotto-segmento del lato L0(da PmO a P1 )
        meshPointer->AddEdge(E1);
        E2 = meshPointer->CreateEdge();    // Primo sotto-segmento del lato L1(da P1 a Pm1 )
        meshPointer->AddEdge(E2);
        E3 = meshPointer->CreateEdge();    // Secondo sotto-segmento del lato L1(da Pm2 a P2 )
        meshPointer->AddEdge(E3);
        E4 = meshPointer->CreateEdge();    // Primo sotto-segmento del lato L2(da P2 a Pm2 )
        meshPointer->AddEdge(E4);
        E5 = meshPointer->CreateEdge();    // Secondo sotto-segmento del lato L2(da Pm2 a P0 )
        meshPointer->AddEdge(E5);

        //Creo i lati della cella centrale

        E6 = meshPointer->CreateEdge();    // da Pm2 a PmO
        meshPointer->AddEdge(E6);
        E7 = meshPointer->CreateEdge();    // da Pm0 a Pm1
        meshPointer->AddEdge(E7);
        E8 = meshPointer->CreateEdge();    // da Pm1 a Pm2
        meshPointer->AddEdge(E8);


        C0 = meshPointer->CreateCell();    //Prima cella
        meshPointer->AddCell(C0);
        C1 = meshPointer->CreateCell();    //Seconda cella
        meshPointer->AddCell(C1);
        C2 = meshPointer->CreateCell();    //Terza cella
        meshPointer->AddCell(C2);
        C3 = meshPointer->CreateCell();    // Cella centale
        meshPointer->AddCell(C3);

        // Aggiorno le informazioni di parentela
        L0->AddChild(E0);
        L0->AddChild(E1);
        E0->SetFather(L0);
        E1->SetFather(L0);

        L1->AddChild(E2);
        L1->AddChild(E3);
        E2->SetFather(L1);
        E3->SetFather(L1);

        L2->AddChild(E4);
        L2->AddChild(E5);
        E4->SetFather(L2);
        E5->SetFather(L2);

        cell->AddChild(C0);
        cell->AddChild(C1);
        cell->AddChild(C2);
        cell->AddChild(C3);
        C0->SetFather(cell);
        C1->SetFather(cell);
        C2->SetFather(cell);
        C3->SetFather(cell);

        // Inizializzo i punri medi

        Pm0->SetCoordinates(0.5*(P0->Coordinates()+P1->Coordinates()));
        Pm1->SetCoordinates(0.5*(P1->Coordinates()+P2->Coordinates()));
        Pm2->SetCoordinates(0.5*(P2->Coordinates()+P0->Coordinates()));

        // Inserisco i punti nei segmenti
        E0->AddPoint(P0);
        E0->AddPoint(Pm0);
        E1->AddPoint(Pm0);
        E1->AddPoint(P1);

        E2->AddPoint(P1);
        E2->AddPoint(Pm1);
        E3->AddPoint(Pm1);
        E3->AddPoint(P2);

        E4->AddPoint(P2);
        E4->AddPoint(Pm2);
        E5->AddPoint(Pm2);
        E5->AddPoint(P0);

        E6->AddPoint(Pm2);
        E6->AddPoint(Pm0);
        E7->AddPoint(Pm0);
        E7->AddPoint(Pm1);
        E8->AddPoint(Pm1);
        E8->AddPoint(Pm2);

        //Inizializzo le celle

        C0->AddPoint(P0);
        C0->AddPoint(Pm0);
        C0->AddPoint(Pm2);
        C0->AddEdge(E0);
        C0->AddEdge(E6);
        C0->AddEdge(E5);

        C1->AddPoint(Pm0);
        C1->AddPoint(P1);
        C1->AddPoint(Pm1);
        C1->AddEdge(E1);
        C1->AddEdge(E2);
        C1->AddEdge(E7);

        C2->AddPoint(Pm1);
        C2->AddPoint(P2);
        C2->AddPoint(Pm2);
        C2->AddEdge(E3);
        C2->AddEdge(E4);
        C2->AddEdge(E8);

        C3->AddPoint(Pm2);
        C3->AddPoint(Pm0);
        C3->AddPoint(Pm1);
        C3->AddEdge(E6);
        C3->AddEdge(E7);
        C3->AddEdge(E8);

        //Le celle per i lati -- To DO

        /*E0->AllocateCells(2);
        E0->InsertCell(C0,1);*/
            }}
        return Output::Success;

    }
}
