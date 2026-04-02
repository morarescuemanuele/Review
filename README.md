## Functionalitati principale
* **Sistem de conturi:** Utilizatorii se pot inregistra cu un rol specific si se pot loga. La pornire, sistemul incarca deja cateva conturi si carti de test pentru a putea fi folosit imediat.
* **Acces pe baza de roluri:**
  * **Admin:** Controleaza baza de date. Poate vedea, adauga si sterge atat utilizatori, cat si carti. Are dreptul sa schimbe parolele sau username-urile altor utilizatori.
  * **Client:** Poate vizualiza catalogul complet de carti si poate acorda un rating (intre 1 si 10) fiecarei carti.
  * **Autor:** Poate publica o carte noua in sistem (care ii va purta automat numele) si are un meniu dedicat unde isi vede doar cartile publicate de el.
  * **Autor Activ:** Mosteneste ambele roluri. Poate citi si evalua carti, dar poate si publica propriile lucrari.
* **Tipuri diverse de carti:** Sistemul distinge intre carti digitale (EBook, AudioBook) si fizice (Carte Tiparita), fiecare avand caracteristici specifice precum format, marime fisier, narator sau greutate. Cartile isi calculeaza automat media notelor primite de la cititori.
* **Sistem de protectie la erori:** Programul foloseste propriul sistem de exceptii pentru a evita vreun crash. Indiferent daca introduci o litera in loc de un numar, cauti un ID care nu exista sau incerci o actiune nepermisa, programul afiseaza o eroare si te intoarce la meniu.

## Limitari si restrictii
* **Lipsa persistentei datelor:** Baza de date este tinuta exclusiv in memoria RAM (in vectori). Odata ce ai inchis programul, toate conturile noi create, cartile adaugate si review-urile lasate se sterg. Nu exista o conexiune la o baza de date reala (gen SQL) si nici nu salveaza in fisiere text locale.
