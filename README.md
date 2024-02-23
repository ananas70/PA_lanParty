
# Temă Proiectarea Algoritmilor - an I, sem. II
## LanParty

Fiecare echipă (**structura Team**) din fișierul de intrare este inserată într-o listă simplu înlănțuită alocată dinamic. Jucătorii (**structura Player**) sunt alocați dinamic într-un bloc de mărimea *nr_players* * *sizeof(Player)*, în funcția **create_Players**. 


### Task 1

Afișarea echipelor prin funcția **print_teams**.

### Task 2
Calcularea numărului de echipe ca putere a lui 2 (*N*) și a numărului de runde (*Nr_rounds*). Creez punctajul de echipă pentru fiecare echipă în parte (**create_team_points**) și șterg echipele cu punctaj minim (**delete_min_from_team**). Afișez tot prin funcția **print_teams**.

### Task 3
Creez coada (**Queue*** **q**) de meciuri și stivele cu echipele câștigătoare (**Stack** ***winners_stack**) și cele pierzătoare (**Stack** ***losers_stack**) cu ajutorul funcției **create_stacks**. Afișez stiva învingătorilor și o eliberez pe cea a pierzătorilor, după care creez coada de meciuri din runda urmatoare (**create_winners_match_queue**).

### Task 4
Inițializez **Node * BST_root=NULL** și creez arborele BST cu funcția **create_last_8_BST_tree**. La final îl parcurg în inordine(DRS).

### Task 5
Inițializez **AVL_Node*** **AVL_root=NULL** și creez arborele AVL și inserez în el (**AVL_insert**) pe măsură ce parcurg arborele BST în inordine (în funcția **DRS**). Îl parcurg pe nivelul 2 cu ajutorul funcției **level_order_traversal**.

La final efectuez eliberările de memorie necesare pentru blocurile de date alocate în heap.
