**TME6 Report**

---

#### Question 1

10 processus
'''
pere
│
└── fils1 "1:3"
    │
    ├── pfils1 "1:0"
    │
    └── pfils2 "2:3"
        │
        └── ppfils1 "1:0"
        │
        └── ppfils2 "2:0"
        │
        └── ppfils3 "3:3"
            │
            └── pppfils1 "1:0"
            │
            └── pppfils2 "2:0"
            │
            └── pppfils3 "3:0"
'''
            
---

#### Question 6

##### le combat n'est plus équitable pour 2 raisons :

- Luke masque les signaux mais ne les démasque pas et passe tout le combat à ignorer les signaux sauf lors de la première exécution de defense_luke où omask représente un masque où SIGINT n'est pas masqué.

- Même après avoir reglé le problème précédent, Luke invoque sigsuspend est attend la réception du signal d'attaque de la part de Vador. Luke passe beaucoup plus de temps que Vador en défense.
