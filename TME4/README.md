**TME2 Report**

---

#### Question 2

Le comportement actuel est correct, car les méthodes `debiter` et `crediter` sont protégées par les mutex des comptes. Cependant, la méthode `transfert` elle-même n'est pas protégée.

---

#### Question 3

Ajout d'une méthode `getMutex` dans la classe `Compte`.

---

#### Question 4

Il est nécessaire de verrouiller les mutex des deux comptes concernés par le transfert au sein de la méthode `transfert` avant d'effectuer le transfert.

---

#### Question 5

Le premier thread verrouille deux fois le même mutex, une fois dans `transfert` et une fois dans `debiter`. Pour éviter cela, nous devons utiliser des `recursive_mutex` à la place.

---

#### Question 6

Il y a parfois un interblocage entre deux threads ayant les mêmes comptes créditeurs et débiteurs mais dans des sens opposés, car les mutex ne sont pas verrouillés dans le même ordre. La correction consiste à verrouiller les mutex dans l'ordre du système.

---

#### Question 7

Non, même si `getSolde` est protégé par un mutex, l'accès concurrent au solde des comptes peut fausser le résultat final. Tant qu'il y a un thread en cours d'exécution, le solde de n'importe quel compte peut changer, même s'il a déjà été comptabilisé.

---

#### Question 8

Bilan comptable incorrect : attendu 5000, obtenu : 4677
Échec

---

#### Question 9

Ajoutons un mutex dans la classe `Banque` et mettons en place les synchronisations nécessaires pour que le thread comptable obtienne toujours les bons résultats.

---

#### Question 10

Avec un seul mutex dans la banque, la concurrence entre les threads de transfert n'est plus possible. Proposons une approche alternative réutilisant les verrous de compte plutôt que d'en avoir un seul. Nous devons empêcher les threads de transfert d'accéder aux comptes que le comptable a déjà vus et crédités dans son bilan, sans introduire de deadlocks.

