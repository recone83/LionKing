# Wyodrębnione grupy bibliotek

Pliki `.c` w tym katalogu zawierają ciała funkcji skopiowane z pseudokodu `../pseiudo.c.backup`. To materiał do analizy, nie kod źródłowy gotowy do kompilacji. Każda funkcja ma komentarz z numerem linii źródłowej i adresem po normalizacji o `+0x10000`.

[`pseiudo.c.backup`](../pseiudo.c.backup) to niezmieniony oryginał. Główny [`pseiudo.c`](../pseiudo.c) jest kopią modularną: dołącza pliki z tego katalogu przez `#include`, a funkcje przeniesione do bibliotek pomija w treści głównej. Nadal jest to pseudokod i nie stanowi kompilowalnego programu.

Spis [`FUNCTIONS.tsv`](./FUNCTIONS.tsv) mapuje 216 wydzielonych definicji do oryginalnego i aktualnego symbolu, modułu, numeru linii backupu oraz adresu. Jest 190 definicji w bibliotekach i 26 w [`engine/`](../engine/); pozostałe 534 są w głównym pliku. Razem eksport zawiera 750 definicji. Wcześniejszy licznik pomijał `FUN_000070ae`, której deklaracja nie zawiera typu zwrotnego. Nazwy `thunk_FUN_...` są osobnymi symbolami; adres z ich sufiksu może oznaczać cel, nie początek thunka.

| Plik | Liczba funkcji | Zakres |
|---|---:|---|
| [disk.c](./disk.c) | 10 | Wybrane funkcje DOS-owego I/O plików i buforowanych strumieni. Klasyfikacja jest heurystyczna. |
| [system.c](./system.c) | 12 | Usługi systemowe, DPMI, BIOS, timer, IRQ i joystick. |
| [vga.c](./vga.c) | 7 | BIOS wideo, porty palety VGA i prezentacja bufora obrazu. |
| [audio.c](./audio.c) | 45 | Zgrupowany obszar sterownika audio oraz funkcje używające jego konfigurowanych portów I/O. Typu karty nie ustalono. |
| [libc_conio.c](./libc_conio.c) | 116 | Funkcje z obszaru runtime Watcoma. W pseudokodzie nie zachowały się nazwy pozwalające wiarygodnie wskazać konkretne API conio. |

Podział kategorii jest heurystyczny: dekompilator nie zachował nazw symboli ani wszystkich relacji bibliotecznych. Niektóre przypisania bazują na wywołaniach przerwań lub portów, inne na obszarze adresów. Pliki nie zawierają kompletnego zestawu używanych globali i zależności między funkcjami; nie należy ich traktować jako samodzielnych modułów kompilowalnych.

Czytelne nazwy i docelowe moduły są w [`RENAMES.tsv`](./RENAMES.tsv). Podział można powtórzyć poleceniem `perl tools/split_pseudocode.pl`; walidacja bez zapisu: `perl tools/split_pseudocode.pl --check`, uruchamiane z katalogu projektu. Narzędzie sprawdza zgodność każdej sygnatury i ciała z backupem po odwróceniu zmian nazw, brak duplikatów/ubytków, aktualność spisu, wywołania oraz dołączenie modułów.

Docelowo potwierdzone implementacje standardowych API mają być zastępowane oryginalnymi bibliotekami, nie rozwijane jako kopie dekompilacji. Samo umieszczenie funkcji w `libc_conio.c` nie potwierdza takiej zgodności. Przed zamianą trzeba ustalić kontrakt, ABI i zachowanie błędów; obecnie nie wykonano jeszcze żadnej zamiany na natywne API.
