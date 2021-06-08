# Zadani z progtestu

Naprogramujte engine pro grafické RPG

Váš engine:

1. ze souboru nahraje definici světa (mapu, předměty, příšery, ...)
2. umožní vytvořit herní postavu (její atributy a schopnosti) a následnou hru
3. implementuje jednoduchý soubojový systém a inventář
4. umožňuje ukládat a načítat rozehrané hry
5. Engine může fungovat jako real-time hra, či tahová hra.

# Upřesnění zadání

Vytvoříme tahový RPG engine, uřivatel sputí hru a pomocí přikázu v konzili připraví hru (načtení mapy, vytvoření
postavy, načtení rozehrané hry) a samotná hra bude ovládána pomocí příkazů Hra bude rozdělena do dvou větších celků a to
do samotné hry a menu

## Menu

V menu lze vytvořit novou postavu, načíst mapu, vytvořit novou hru (kombinace postavy a mapy), a načíst rozehranou hru.
V Menu se u6ivateli zobrazí nabídka možnostní, co může udělat.

- `load game` - načte hru ze souboru
- `create game` - dá hráči možnost vytvořit postavu a následně načíst mapu ze souboru

## Hra

Hra bude tahová, v každém tahu bude mít každá entita (hráč, příšera) určitý počet akčních bodů, které může použít na
pohyb, boj a další akce.

Akce, které budou k dispozici v herním módu. Jsou řešeny pomocí příkazů do konzole. Hráči se ukáže nabídka, ze které si
může vybrat co chce dělat

- `move` přepne do módu pohybu
- `attack` dá na výběr ze zbraní které může postava použít a následně dá na výběr z cílů na které může útočit
- `inventory` otevře invetář a umožní použití a konzumaci předmětů (lektvary, lékarnička)
- `loot` zobrazí se pokud se hráč přiblíží k entitě (truhla, mrtvá příšera) ze které může vzít nějaký předmět.
- `end-turn` předčasné ukončení tahu

.Třída `CInterface` zajišťuje komunikaci s uživatelem (jak vstup tak výstup).

Za fungování menu je zodpovědná třída `CMenu` a za hru je zodpovědná třída `CGame`.

# Polymorfismus

polymorfismus bude použit v třídě `CEntity` která bude obsahovat všechny entity. Každá podtřída má funkci `Turn`, která
řídí jejich akce v pruběhu tahu také má funcki  `Attack`,`Attacked`,`move`, které řeší útok a pohyb. Třída `CPlayer` je
podtřídou `CMobile`. Třída `CEntity` má podtřídy, které už reprezentují danou entitu a mají implementované abstraktní
funkce.

Na polymorfismus také narazíme ve třídě `CControler`, který má na starosti kontrolování entit, k entitě je přiřazaen v
době jejího načítání. Má jedinou abstraktni funkci a to funkci `control`.

Dále je polymorfismus využit i v třídě `CItem`, která ma abstraktní funkci `Effect`, která provede efekt předmětu a také
mám tříd `CWeapon`, která má abstraktní funkci `Attack`.