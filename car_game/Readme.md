

### Descriere 
Sonia si-a luat permisul. Drept urmare, Sonia acum incepe sa mearga cu masina pe strada.
Dar strazile din Romania sunt pline de gropi si obstacole ! Ajut-o pe Sonia sa evite obstacolele de pe strada.
In Level1.in putem vedea strada pe care Sonia merge cu viteza legala de 50km/h, unde "S" este masina Soniei, iar "#" sunt zone interzise peste care nu are voie sa treaca cu masina.
La fiecare pas, pe harta nivelului 1 (din Level1.in), vor aparea un numar de obstacole, care vor fi afisate cu caracterul "O".
Sonia merge constant cu viteza maxima legala admisa de 50km/h, dar obstacolele incep sa apara din ce in ce mai multe pe masura ce Sonia inainteaza cu masina.
Ajut-o pe Sonia sa evite obstacolele si sa reziste cat mai mult pe strada cu masina fara sa faca buf.


### Framework
In codul din Framework.cpp, functia "playerMove" returneaza o decizie luata de sonia printr-un byte, iar decizia poate fi o combinatie de miscari (i.e. Sonia poate sa accelereze si sa mearga in dreapta simultan, setand doi biti pe 1).
Modifica doar playerMove(), folosindu-te de variabilele map[][], playerX, playerY, mapWidth si mapHeight pentru a rezista cat mai mult pe traseu !
