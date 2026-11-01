# Pozostaly pseudokod po podziale

Glowny [pseiudo.c](../pseiudo.c) jest teraz agregatorem dołączeń i komentarzy.
Wszystkie 753 definicje eksportu mają jednego właściciela: 228 w
[libs/](../libs/), 47 w [engine/](../engine/) i 478 tutaj.
Wspólne deklaracje zachowano w [globals.inc](./globals.inc).
Dodatkowy [game_main](../engine/main.c) został odtworzony z asemblera, nie z
eksportu; jest liczony osobno i nie zmienia powyższych 753 definicji.

Poniższy podział jest neutralny: używa przedziałów adresowych, nie domniemanych
funkcji gry ani pierwotnych granic bibliotek. Przedziały dotyczą adresów eksportu
(baza zero); adresy kodu z dokumentacji wymagają dodania `0x10000`.
Sufiks symbolu thunk może opisywać cel skoku, nie jego własny początek.
Funkcje można później przenosić do rozpoznanych modułów przez
[RENAMES.tsv](../libs/RENAMES.tsv).

| Plik | Przedział eksportu | Definicje |
|---|---|---:|
| [block_00000.c](./block_00000.c) | `0x00000–0x03fff` | 37 |
| [block_04000.c](./block_04000.c) | `0x04000–0x07fff` | 48 |
| [block_08000.c](./block_08000.c) | `0x08000–0x0bfff` | 57 |
| [block_0c000.c](./block_0c000.c) | `0x0c000–0x0ffff` | 48 |
| [block_10000.c](./block_10000.c) | `0x10000–0x13fff` | 59 |
| [block_14000.c](./block_14000.c) | `0x14000–0x17fff` | 61 |
| [block_18000.c](./block_18000.c) | `0x18000–0x1bfff` | 54 |
| [block_1c000.c](./block_1c000.c) | `0x1c000–0x1ffff` | 31 |
| [block_20000.c](./block_20000.c) | `0x20000–0x23fff` | 48 |
| [block_24000.c](./block_24000.c) | `0x24000–0x27fff` | 16 |
| [block_2c000.c](./block_2c000.c) | `0x2c000–0x2ffff` | 2 |
| [block_30000.c](./block_30000.c) | `0x30000–0x33fff` | 7 |
| [block_34000.c](./block_34000.c) | `0x34000–0x37fff` | 10 |

Oryginalne nazwy, linie i znormalizowane adresy są w
[FUNCTIONS.tsv](../libs/FUNCTIONS.tsv). Nie poprawiono ciał, błędnych stałych,
sygnatur ani globali. Te pliki nie są samodzielnymi jednostkami kompilacji.
Znaczące komentarze pozostają też w niezmienionym
[pseiudo.c.backup](../../pseiudo.c.backup).

Walidacja z katalogu projektu: `perl tools/split_pseudocode.pl --check`.
Sprawdza zachowanie wszystkich definicji i deklaracji, nie działanie gry.
`--complete` odtwarza pełny podział; zwykłe uruchomienie stosuje manifest.
Parser uwzględnia również wielowierszowe sygnatury; poprzedni licznik 750
pomijał trzy definicje z wielowierszowymi parametrami.
