Úkolem je vytvořit program, který bude řešit logickou hru - odebírání žetonů.

Hru hrají dva hráči A a B. Na stole jsou ve tvaru kříže umístěné žetony. Na každém žetonu je umístěné celé číslo (kladné, záporné, nula). Uprostřed (v průsečíku) je umístěn speciální žeton bez čísla. Hru začíná hráč A, který odebere libovolný žeton z konce kříže (má tedy 4 možnosti na výběr). Hodnota uvedená na žetonu se přičte k jeho skóre. Následně hraje hráč B, který analogicky odebírá jeden z dalších dostupných žetonů (vždy z konců ramen kříže). Hráči se v odebírání střídají, dokud hra neskončí. To nastane po odebrání všech žetonů s čísly. Cílem hry je získat co nejvyšší skóre, tedy odebrat co nejvíce žetonů s co nejvyššími hodnotami.

Na vstupu programu jsou zadané hodnoty žetonů na jednotlivých ramenech kříže. Pro jednoduchost si ramena označíme podle světových stran (N-North, E-East, W-West, S-South). Program dostane seznam hodnot žetonů v těchto ramenech, uspořádání je vždy směrem od konce ramene ke středu. Na vstupu tedy budou 4 sekvence, jako například v ukázce (pořadí světových na vstupu stran se může lišit):

N: { 1, 2 }
W: { 3, 5 }
E: { 9, 1, 1, 1 }
S: { 1, 7 }
Tomuto zadání odpovídá rozmístění žetonů podle následujícího obrázku:



Program načte zadání a začne simulovat hru. Hraje střídavě za oba hráče A i B, volí vždy takový tah, který je pro hráče optimální (přináší nejvíce bodů do jeho finálního výsledku). Následně pak program vypíše tahy jednotlivých hráčů a celkové skóre. Výpis má následující podobu:

A: E[0] (9)
B: E[1] (1)
A: N[0] (1)
B: N[1] (2)
A: S[0] (1)
B: S[1] (7)
A: W[0] (3)
B: W[1] (5)
A: E[2] (1)
B: E[3] (1)
Celkem A/B: 15/16
První řádka udává tah hráče A, odebírá žeton z východního ramene na pozici 0, tento žeton má hodnotu 9. Následuje tah hráče B, který odebírá z východního ramene žeton na pozici 1 s hodnotou 1, … Za předpokladu optimální hry obou hráčů v této hře může hráč A získat skóre 15 a hráč B skóre 16.

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Po detekování chyby se program ukončí. Za chybu považujte:

Nebylo zadané některé rameno kříže, některé rameno kříže bylo zadáno vícekrát nebo má rameno nesprávné označení (platná označení jsou N, E, W a S),
rameno kříže neobsahuje žádný žeton,
rameno kříže obsahuje více než 32 žetonů,
chybí nebo přebývá některý z oddělovačů (čárka, dvojtečka, složená závorka),
nečíselné zadání hodnoty žetonu.
