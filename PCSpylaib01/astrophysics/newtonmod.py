
"""
Modulo per applicazioni della legge
di gravitazione universale di Newton."""

# Costante di Gravitazione Universale
G = 6.67 * 1e-11  # N m^2 / kg^2

# Distanza media Sole-Terra
DSoleTerra = 1496 * 1e8 # m

# Distanza media Sole-Marte
DSoleMarte = 2279 * 1e8 # m

# Distanza media Terra-Luna
DTerraLuna = 3844 * 1e5 # m

# Massa della Luna
Ml = 7342 * 1e22  # kg

# Raggio Lunare
Rl = 1737 * 1e3 # m

# Massa della Terra
Mt = 5.972 * 1e24  # kg

# Massa di Marte
Mm = 6.39 * 1e23  # kg

# Raggio Terrestre
Rt = 6371 * 1e3  # m

# Raggio Marziano
Rm = 3390 * 1e3  # m

# Massa del Sole
MS = 1.9891 * 1e30  # kg

# Raggio Solare
RS = 6.960 * 1e8  # m

# Temperatura Solare
TS = 5778  # K

# Rapporto temperatura-colore delle stelle
tempranges = [(0, 3700), (3700, 5200), (5200, 6000),
              (6000, 7500), (7500, 10000), (10000, 30000), (30000, 60000)]
colors = ['Rosso', 'Arancione', 'Giallo',
          'Bianco-Giallo', 'Bianco', 'Bianco-Azzurro', 'Blu-Azzurro']
starclass_spett = ['M', 'K', 'G', 'F', 'A', 'B', 'O']

# COMPREHENSION CHE CREA UN DIZIONARIO stardict TALE CHE:
# CHIAVI: classi spettrali delle stelle
# VALORI: dizionari della forma {'color': colore stella, 'temp. range': (temp. min, temp.max)}
stardict = {starclass_spett[i]: {'color': colors[i], 'temp. range': tempranges[i]}
            for i in range(len(tempranges))}


def newton_law(kg1, kg2, m):
    """
    Funzione che calcola il modulo della forza gravitazionale tra due corpi. Le unità di misura da utilizzare devono
    essere espresse in kg per le masse ed in metri per la distanza tra i corpi.
    INPUT:
    kg1, kg2 = kg massa corpo 1 e 2
    m = distanza tra corpi 1 e 2
    OUTPUT:
    f = modulo della forza gravitazionale tra i due corpi"""

    f = (G * kg1 * kg2) / (m ** 2)
    return f


def newton_to_kgf(n):
    """
    Funzione che converte newton in kilogrammi-forza.
    INPUT:
    n = Newton da convertire
    OUTPUT:
    kgf = valore in kg-forza dei Newton passati in input"""

    kgf = n * 0.10197
    return kgf



