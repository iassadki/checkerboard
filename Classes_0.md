# Jeu
- joueur_actuel : Joueur
- plateau : Plateau

--methodes
- demarrer() : void
- terminer() : void
- changer_joueur() : void

# Plateau
- pieces : Liste<Piece>

--methodes
- initialiser_plateau() : void

# Joueur
- pieces : Liste<Piece>

--methodes
- effectuer_deplacement(depart : Position, arrivee : Position) : bool
- déplacer_piece(depart : Position, nouvelle_pos : Position) : bool
- retirer_piece(piece : Piece) : void
est_deplacement_valide(depart : Position, arrivee : Position, joueur : Joueur) : bool

# Piece
- couleur : string
- est_reine : bool
- position : Position

--methodes
- promouvoir() : void

# Position
- x : int
- y : int 

--methodes
- est_valide() : bool