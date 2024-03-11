Úkolem je vytvořit program, který dokáže vyhledávat v zadaných bodových hodnoceních.

Vstupem našeho programu je seznam bodových hodnocení v předmětu PA1. Jedna vstupní hodnota bodů představuje hodnocení jednoho studenta. Následně chceme tato data analyzovat. Tedy chceme zjistit, kolik studentů připadá na zadaný interval bodového hodnocení.

Vstupem je nejprve seznam bodových hodnocení. Bodové hodnocení studenta je celé číslo v intervalu 0 až 1000000000 včetně. Bodová hodnocení jsou zadaná ve složených závorkách, jednotlivé hodnoty jsou oddělené právě jednou čárkou. Po zadání bodových hodnocení přicházejí dotazy. Každý dotaz je zadaný jako interval (uzavřený, polootevřený, otevřený), meze intervalu jsou zadané jako celá čísla, čísla jsou oddělená středníkem. Intervalů může být zadaných mnoho, zpracování dotazů pokračuje do konce vstupu (EOF).

Výstupem programu je počet studentů, který dosáhl bodového hodnocení pro každý dotazovaný interval.

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

hodnocení studentů není zadané jako celé číslo v intervalu 0 až 1000000000,
hodnocení studentů není ve složených závorkách,
hodnocení studentů nejsou oddělena čárkou,
musí být zadaný alespoň jeden hodnocený student,
dotazovaný interval není zadaný jako otevřený, polootevřený ani jako uzavřený,
meze dotazovaného intervalu nejsou celá čísla (mohou být i záporná),
meze dotazovaného intervalu nejsou oddělené středníkem.
