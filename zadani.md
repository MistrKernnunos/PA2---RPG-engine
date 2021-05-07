
# Zadani z progtestu

Naprogramujte engine pro grafické RPG

Váš engine:

1. ze souboru nahraje definici světa (mapu, předměty, příšery, ...)
2. umožní vytvořit herní postavu (její atributy a schopnosti) a následnou hru
3. implementuje jednoduchý soubojový systém a inventář
4. umožňuje ukládat a načítat rozehrané hry
5. Engine může fungovat jako real-time hra, či tahová hra.

# Upřesnění zadání

Vytvoříme tahový RPG engine, uřivatel sputí hru a pomocí přikázu v konzili připraví hru (načtení mapy, vytvoření postavy, načtení rozehrané hry) a samotná hra bude ovládána pomocí kombinace příkazů v konzoli a zachytávání kláves (primárně pro pohyb po mapě)
Hra bude rozdělena do dvou větších celků a to do samotné hry a menu

## Menu

V menu lze vytvořit novou postavu, načíst mapu, vytvořit novou hru (kombinace postavy a mapy), a načíst rozehranou hru.

- `new-character [name]` vytvoří novou postavu a zeptá se na rasu, rozdělení XP do jednotlivých schopností (pohyb, síla, životy...)
- `load-map [filename]` načte mapu ze souboru
- `load-game` dá na výběr ze všech uložených rozehraných her v enginu
- `create-game` vytvoří novou hru.
  - Zeptá se jestli chce vytvořit novou postavu, nebo použít již někdy vytvořenou postavu
  - Zeptá odkuď načíst mapu
  - spustí hru
- `quit` ukončí program

## Hra

Hra bude tahová, v každém tahu bude mít každá entita (hráč, příšera) určitý počet akčních bodů, které může použít na pohyb, boj a další akce. V jeden moment bude na obrazovce vidět jen aktuální místnost ve které se nachází náš charakter. Do dalších místností se dá procházet pomocí dveří.

Akce, které budou k dispozici v herním módu. Jsou řešeny pomocí příkazů do konzole

- `move` přepne do módu pohybu
  - zobrazí se okruh kam se může postava posunout a pomocí šipek si hráč vybere pozici, kam se chce posunout
- `attack` dá na výběr ze zbraní které může postava použít a následně dá na výběr z cílů na které může útočit
- `inventory` otevře invetář a umožní použití a konzumaci předmětů (lektvary, lékarnička)
- `defense` zaujmutíš obrané pozice (zvýší obrané staty)
- `loot` zobrazí se pokud se hráč přiblíží k entitě (truhla, mrtvá příšera) ze které může vzít nějaký předmět.
- `end-turn` předčasné ukončení tahu

Celá aplikace je ovládána přes třídu `CAplication`, příkazy jsou zpracovány pomocí třídy `CCommand` a její podtřídy. Třída `CInterface` zajišťuje komunikaci s uživatelem (jak vstup tak výstup).

Za fungování menu je zodpovědná třída `CMenu` a za hru je zodpovědná třída `CGame` a místnosti mají svou vlastní třídu a to `CRoom`.

# Polymorfismus

polymorfismus bude použit v třídě `CEntity` která bude obsahovat všechny entity. Každá podtřída má funkci `Turn`, která řídí jejich akce v pruběhu tahu také má funcki  `Attack` a `Defense`, které řeší útok a obranu pro každou entitu. Třída CEntity bude mít podtřídy `CMobile` a `CImMobile`. Třída `CMobile` má další polymorfní funkci `move`, která zajišťuje pohyb entit po mapě. Třída `CPlayer` je podtřídou `CMobile`.

Dále je polymorfismus využit i v třídě `CItem`, která ma abstraktní funkci `Effect`, která provede efekt předmětu. Tato třída má potřídu `CWeapon`, která má ještě navíc abstraktní funkci `Defense`.
