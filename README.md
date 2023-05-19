# Vector Vector

 <strong>TESTAVIMAS</strong><br>
 Testavimo sistemos parametrai:<br>
 <strong>CPU</strong> - Apple M1 chip: 8-core CPU with 4 performance cores and 4 efficiency cores, 8-core GPU, 16-core Neural Engine.<br>
 <strong>RAM</strong> - 8GB, VS code naudoja max 4GB.<br>
 <strong>SSD</strong> - 256GB.<br>
 <br>
 <strong> VECTOR FUNKCIJŲ TESTAVIMAS</strong><br>
<strong> Push_back():</strong><br>
    
    vektorius.push_back(1);
    vektorius.push_back(2);
    vektorius.push_back(3);

    klase.push_back(1);
    klase.push_back(2);
    klase.push_back(3);
vektorius: 123, klasė: 123<br>
 <strong> at():</strong><br>
 
    std::cout<<"std::vector at(2): "<<vektorius.at(2)<<std::endl;
    std::cout<<"Vector at(2): "<<klase.at(2)<<std::endl;
 
 vektorius: 3, klasė: 3</br>
  <strong> capacity():</strong><br>
  
    std::cout<<"std::vector capacity(): "<<vektorius.capacity()<<std::endl;
    std::cout<<"Vector capacity(): "<<klase.capacity()<<std::endl;
    
vektorius: 100, klasė: 100<br>
  <strong> front():</strong><br>
  
    std::cout<<"std::vector front(): "<<vektorius.front()<<std::endl;
    std::cout<<"Vector front(): "<<klase.front()<<std::endl;
 
vektorius: 1, klasė: 1<br>
 <strong> back():</strong><br>
 
    std::cout<<"std::vector back(): "<<vektorius.back()<<std::endl;
    std::cout<<"Vector back(): "<<klase.back()<<std::endl; 
vektorius: 3, klasė: 3<br>

<strong> max_size():</strong><br>

    std::cout<<"std::vector max_size(): "<<vektorius.max_size()<<std::endl;
    std::cout<<"Vector max_size(): "<<klase.max_size()<<std::endl;
    
   vektorius: 4611686018427387903, klasė: 18446744073709551615<br>
   
<strong> pop_back():</strong><br>

    vektorius.pop_back();
    klase.pop_back();
    
   vektorius: 12, klasė: 12<br>

 <br>
 <strong>NAUDOJIMOSI ŽINGSNIAI:</strong>
 <br>
 <ol>
 <li>Pasirinkite kokį konteinerį naudosite (v - vector, l - list, d - deque)</li>
  <li>Spauskite 1 - rezultatai bus pateikti failuose, 2 - rezultatai bus pateikti konsolėje</li>
 <li>Spauskite 1 - 1 strategija (kuriamas vargšų konteineris ir įrašai ištrinami iš pagrindinio konteinerio). Spauskite 2 - 2 strategija (kuriami 2 to pačio tipo vargšų ir šaunuolių konteineriai)</li>
 <li>Spauskite 'p' - studentus aprašote patys arba 'a' - skaitoma iš failo</li>
    <ol>
    <li>Jeigu pasirinkote 'p'</li>
        <ol>
         <li>Įveskite studento vardą ir pavardę</li>
         <li>Įveskite 'p' jeigu norite pažymius vesti pats arba 'a', jeigu norite sugeneruotų        pažymių</li>
              <ol>
              <li>Jeigu pasirinkote p - veskite pažymius 1-10 ir kai baigsite vesti spauskite 11</li>
              <li>Jeigu pasirinkote 'a' - įveskite teigiamą skaičių kiek pažymių generuoti</li>
              </ol>
         <li>Įveskite egzamino rezultatą (1-10)</li>
         </ol>
     <li>Jeigu pasirinkote 'a'</li>
        <ol>
        <li>Norėdami generuoti naują failą spauskite 'n', norėdami naudoti jau turimą failą spauskite 't'</li>
             <ol>
             <li>Jeigu pasirinkote 'n'.</li>
                  <ol>
                  <li>Pasirinkite kiek įrašų generuoti faile (1000, 10000, 100000, 1000000, 10000000)</li>
                  <li>Pasirinkite kiek pažymių generuoti</li>
                  </ol>
              <li>Jeigu pasirinkote 't'</li>
                 <ol> 
                 <li>Įveskite failo pavadinimą iš direktorijos</li>
                 </ol>
              </ol>
         </ol>
 </ol>
 <br>
  
<strong>V2.0</strong>
<br>
<ul>
  <li> Versijoje sukurta doxygen dokumentacija, atlikti move assignment operatoriaus, vidurkio skaičiavimo ir naujo failo generavimo funkcijų unit testavimas naudojant catch2</li>
  </ul>
  <br>
<strong>ĮDIEGIMO INSTRUKCIJA(veikia tik ant M1 chip mac)</strong>
<ul>
  <li>Atsisiųskite Paleidimas.dmg failą</li>
<li>Jį atidarius, jūsų darbalaukyje šalia Paleidimas.dmg failo atsiras Disk Image "Paleidimas"</li>
<li>Atidarykite Disk Image</li>
<li>Atidarykite failą "Program" ir programa pasileis</li>
  </ul>
