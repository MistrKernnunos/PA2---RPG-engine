# Formát mapy uložené v souboru
- za curly bracket se nachází ID a jméno mapy
  - jméno se může skládat pouze z jednoho slova
  - mapa se vždy skládá z jednotlivých místností
- jednotlivé složky jsou do sebe vnořeny pomocí curly brackets

## formát jedné místnosti
- místnost vžy začínám ID místnosti a jménem místnosti
- následují perimetrové zdi a vnitřní zdi
- pak následují dveře
- pak samotné entity
- každá složka je samostatně obalena do curly brackets
  
## stěny
- stěny budou zadáný pomocí souřadnic, vždy souřadnice začátku a konce
  - `(0,0;10,10)` stěna z bodu 0,0 do bodu 10,10
  - první v souboru s mapou budou perimetrové zdi, jednotlivé zdi na sebe musí navazovat a tvořit uzavřený tvar
  - pak se tam můžou nacházet další stěny, které již nemusí tvořit tvary
  
## souřadnice
- souřadnice můžou být 0 nebo kladná celá čísla