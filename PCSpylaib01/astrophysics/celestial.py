
"""
Modulo contenente classi
di oggetti celesti."""

import astrophysics.newtonmod as nw  # importazione modulo newtonmod con nome nw per usarne funzioni e costanti
from math import pi  # importazione variabile pi greco dal modulo math


class CelestialBody():
    """
    Classe per la definizione di corpi celesti.
    """
    # METODO SPECIALE DI INIZIALIZZAZIONE
    def __init__(self, name, M, r):
        """
        Metodo speciale di inizializzazione
        :param name: nome; :param M: massa; :param r: raggio;
        """
        # ATTRIBUTI DI ISTANZA
        # attributo nome
        self.name = name
        # attributo massa
        self.mass = M
        # attributo raggio
        self.radius = r
        # attributo volume
        self.volume = (4 / 3) * pi * (r ** 3)
        # attributo ciorconferenza equatoriale
        self.equator = 2 * pi * r
        # attributo densità
        self.density = self.mass / self.volume
        # attributo satelliti (INIZIALIZZATO COME DIZIONARIO VUOTO)
        self.satellites = {}
        # attributo distanze dei satelliti (INIZIALIZZATO COME DIZIONARIO VUOTO)
        self.satellites_dist = {}
        # attributo "satellite di" (INIZIALIZZATO COME DIZIONARIO VUOTO)
        self.satelliteof = {}
        # attributo "distanze dagli ogg. di cui è satellite" (INIZIALIZZATO COME DIZIONARIO VUOTO)
        self.satelliteof_dist = {}

        # LUCA SAVANT AIRA
        # attributo accelerazione gravitazionale
        self.acceleration = nw.G * self.mass / self.radius**2

    # ATTRIBUTO DI CLASSE
    obj_type = 'Corpo Celeste'

    # METODO PER STAMPARE/RESTITUIRE INFO
    def info(self):
        """
        Metodo per visualizzare i paramtri del corpo celeste.
        """
        # RICORDA: __dict__ è un ATTRIBUTO SPECIALE creato di default da python. È un dizionario contenente le coppie
        # (nome attributo, valore attributo) dell'istanza.
        info_dict = self.__dict__

        # utilizzo del metodo format delle stringhe
        print('*** ATTRIBUTI OGGETTO: {} ***'.format(self.name))
        # ciclo for sulle coppie (chiave, valore) del dizionario, utilizzando il metodo .items() dei dizionari
        for (key, val) in info_dict.items():
            print(key, ':', val)
        print('')

    # METODO PER IL CALCOLO DELLA FORZA GRAVITAZIONALE
    def Gforce(self, m, d, typedist='center'):
        """
        Metodo per il calcolo della forza gravitazionale tra il corpo ed un'altro oggetto.
        :param m: massa dell'altro oggetto; :param d: distanza del centro di m dal centro del corpo;
        :return: forza gravitazionale
        """
        # chiamata alla funzione newton_law del modulo newtonmod
        if typedist == 'center':
            f = nw.newton_law(self.mass, m, d)
        elif typedist == 'surf':
            f = nw.newton_law(self.mass, m, d+self.radius)
        return f

    # METODO PER AGGIUNTA DI SATELLITE (utilizza la creazione di nuove coppie (chiave, valore) dei dizionari)
    def add_satellite(self, other, d):
        """
        Metodo per l'aggiunta di satelliti al corpo celeste considerato
        :param other: altro oggetto di tipo corpo celeste; :param d: distanza MEDIA tra i corpi self ed other
        """
        # creazione della coppia (nome ogg. other, ogg. other) nel dizionario dei satelliti
        self.satellites[other.name] = other
        # creazione della coppia (nome ogg. other, distanza) nel dizionario delle distanze dei satelliti
        self.satellites_dist[other.name] = d
        # creazione della coppia (nome ogg. self, ogg. self) nel dizionario "satellite di" dell'ogg. other
        other.satelliteof[self.name] = self
        # creazione della coppia (nome ogg. self, distanza) nel dizionario "distanze dagli ogg. di cui è satellite"
        # dell'ogg. other
        other.satelliteof_dist[self.name] = d

    # METODO PER STABILIRE L'OGG COME SATELLITE DI UN ALTRO (equivalente al metodo add_satellite ma con other e self
    # scambiati nei comandi)
    def add_assatellite(self, other, d):
        """
        Metodo per l'aggiunta del corpo self come satellite di un altro corpo other
        :param other: altro oggetto di tipo corpo celeste; :param d: distanza MEDIA tra i corpi self ed other
        """
        other.satellites[self.name] = self
        other.satellites_dist[self.name] = d
        self.satelliteof[other.name] = other
        self.satelliteof_dist[other.name] = d

    def remove_satellite(self, name):
        """
        Metodo per la rimozione di satelliti dal corpo celeste considerato
        :param name: nome del satellite da eliminare
        """
        self.satellites[name].satelliteof.pop(self.name)
        self.satellites[name].satelliteof_dist.pop(self.name)
        self.satellites.pop(name)
        self.satellites_dist.pop(name)

    def remove_satellite(self, name):
        """
        Metodo per la del corpo self come satellite di un altro corpo
        :param name: nome del satellite da cui eliminarsi
        """
        self.satelliteof[name].satellites.pop(self.name)
        self.satelliteof[name].satellites_dist.pop(self.name)
        self.satelliteof.pop(name)
        self.satelliteof_dist.pop(name)

    def weight(self, m):
        """
        Metodo per ricavare il peso in kilogrammi-forza di un oggetto sulla superficie
        """
        return nw.newton_to_kgf(m * self.acceleration)

    def Gforce_satellites(self, name):
        """
        Metodo per calcolare la forza gravitazionale tra self e un oggetto satellite o di cui e' satellite
        """
        if name in self.satellites:
            return nw.newton_law(self.mass, self.satellites[name].mass, self.satellites_dist[name])
        if name in self.satelliteof:
            return nw.newton_law(self.mass, self.satelliteof[name].mass, self.satelliteof_dist[name])
        print("Satellite non trovato")
        return 0
        


    # METODO SPECIALE repr (per la stringa stampata a schermo quando si digita il nome di un oggetto)
    def __repr__(self):
        caratt = '{}, mass: {}, radius: {}'.format(self.name, self.mass, self.radius)
        desc = '< CelestialBody object {} >'.format(caratt)
        return desc
    
    # METODO SPECIALE len (per ottenere un output con il comando len(istanza))
    def __len__(self):
        return int(self.radius)

    # METODO SPECIALE str (per ottenere un output con il comando str(istanza))
    def __str__(self):
        return self.name

    # METODO SPECIALE le (per ottenere un output con il comando ogg1 <= ogg2)
    def __le__(self, other):
        return self.mass <= other.mass

    # METODO SPECIALE lt (per ottenere un output con il comando ogg1 < ogg2)
    def __lt__(self, other):
        return self.mass < other.mass
    
    # METODO SPECIALE le (per ottenere un output con il comando ogg1 >= ogg2)
    def __ge__(self, other):
        return self.mass >= other.mass

    # METODO SPECIALE lt (per ottenere un output con il comando ogg1 > ogg2)
    def __gt__(self, other):
        return self.mass > other.mass

        # METODO SPECIALE le (per ottenere un output con il comando ogg1 == ogg2)
    def __eq__(self, other):
        return self.mass == other.mass

    def __iadd__(self, pair):
        self.add_satellite(pair[0], pair[1])
        return self

    def __isub__(self, name):
        self.remove_satellite(name)
        return self

    

# SOTTOCLASSE Star DELLA CLASSE CelestialBody
class Star(CelestialBody):
    """
    Classe per la definizione di stelle (sottoclasse di corpo celeste)
    """
    # MODIFICA DEL METODO SPECIALE DI INIZIALIZZAZIONE (aggiunta dell'argomento temperatura in input)
    def __init__(self, name, M, r, T):
        # ATTRIBUTI DI ISTANZA EREDITATI (tutti i vari attributi di istanza della classe padre vengono generati
        # chiamando il suo il metodo __init__)
        CelestialBody.__init__(self, name, M, r)

        # ATTRIBUTO DI CLASSE EREDITATO e MODIFICATO
        self.obj_type = 'Stella ({})'.format(self.obj_type)

        # NUOVI ATTRIBUTI DI ISTANZA
        # attributo temperatura
        self.temp = T
        
        # Confronto temperatura stella con valori nel dizionario stardict nel modulo newtonmod.
        # ciclo for sulle chiavi del dizionario
        for key in nw.stardict.keys():
            # controlla se la temperatura è compresa nel range indicato e, se vero, assegna colore e classe.
            if nw.stardict[key]['temp. range'][0] <= T < nw.stardict[key]['temp. range'][1]:
                # attributo colore stella
                self.color = nw.stardict[key]['color']
                # attributo classe stella
                self.starclass_yerks = key

    # RISCRITTURA METODO SPECIALE repr RISPETTO ALLA CLASSE PADRE
    def __repr__(self):
        caratt = '{}, mass: {}, radius: {}, temp: {}, yerks class: {}'.format(self.name, self.mass, self.radius,
                                                                              self.temp, self.starclass_yerks)
        desc = '< Star object {} >'.format(caratt)
        return desc



class SolarSystem():
    """
    Classe per la definizione di sistemi solari
    """
    def __init__(self, name, Star, l):
        """
        Metodo speciale di inizializzazione
        :param name: nome; :param Star: Stella principale; :param l: lista di CelestialBody;
        """
        # ATTRIBUTI DI ISTANZA
        # attributo nome
        self.name = name
        # attributo Star
        self.Star = Star
        # attributo lista pianeti
        self.planets = self.Star.satellites
        self.planets_stardist = self.Star.satellites_dist
        for planet in l:
            d = input("Inserire la distanza tra "+planet.name+" e "+self.Star.name+" ")
            self.add_planet(planet, d)


        self.mass = self.Star.mass
        for p in self.planets:
            self.mass += self.planets[p].mass
            for sat in self.planets[p].satellites:
                self.mass += self.planets[p].satellites[sat].mass

        self.radius = max(self.planets_stardist.values())
        self.obj_type = 'Oggetto Celeste (Sistema Solare)'

    def info(self):
        info_dict = self.__dict__

        # utilizzo del metodo format delle stringhe
        print('*** ATTRIBUTI OGGETTO: {} ***'.format(self.name))
        # ciclo for sulle coppie (chiave, valore) del dizionario, utilizzando il metodo .items() dei dizionari
        for (key, val) in info_dict.items():
            print(key, ':', val)
        print('')

    def add_planet(self, planet, stardist):
        self.Star.add_satellite(planet,stardist)
        self.planets[planet.name] = planet
        self.planets_stardist[planet.name] = stardist

    def remove_planet(self, name):
        self.Star.remove_satellite(name)
        self.planets.pop(name)
        self.planets_stardist.pop(name)

    def __repr__(self):
        caratt = '{}, mass: {}, radius: {}, star class (yerks): {}'.format(self.name, self.mass, self.radius, 'bha')
        desc = '< SolarSystem object {} >'.format(caratt)
        return desc





