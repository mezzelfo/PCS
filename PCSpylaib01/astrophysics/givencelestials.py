"""
Modulo contenente alcuni
corpi celesti noti.
"""

import astrophysics.celestial as cel
import astrophysics.newtonmod as nw

# creazione di un oggetto della classe CelestialBody indicato dalla variabile earth.
# In input vengono passati una stringa per il nome, un valore di massa (letto dal modulo newtonmod sopra importato) ed
# un valore per il raggio (anche questo letto dal modulo newtonmod)
# Questi argomenti in input per l'inizializzazione, sono quelli richiesti dal metodo __init__ della classe CelestialBody
earth = cel.CelestialBody('Terra', nw.Mt, nw.Rt)

# LUCA SAVANT AIRA
mars = cel.CelestialBody('Marte',nw.Mm,nw.Rm)
moon = cel.CelestialBody('Luna',nw.Ml,nw.Rl)
sun = cel.Star('Sole',nw.MS,nw.RS,nw.TS)

sun.add_satellite(earth,nw.DSoleTerra)
sun.add_satellite(mars,nw.DSoleMarte)
moon.add_assatellite(earth,nw.DTerraLuna)

solsys = cel.SolarSystem('Pippo',sun,[earth, mars])

