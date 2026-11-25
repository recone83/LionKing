# Wyodrębnione grupy bibliotek

Pliki `.c` w tym katalogu zawierają ciała funkcji skopiowane z pseudokodu `../pseiudo.c.backup`. To materiał do analizy, nie kod źródłowy gotowy do kompilacji. Każda funkcja ma komentarz z numerem linii źródłowej i adresem po normalizacji o `+0x10000`.

[`pseiudo.c.backup`](../pseiudo.c.backup) to niezmieniony oryginał. Główny [`pseiudo.c`](../pseiudo.c) jest kopią modularną: dołącza pliki z tego katalogu przez `#include`, a funkcje przeniesione do bibliotek pomija w treści głównej. Nadal jest to pseudokod i nie stanowi kompilowalnego programu.

Spis [`FUNCTIONS.tsv`](./FUNCTIONS.tsv) mapuje wszystkie 753 wydzielone definicje do oryginalnego i aktualnego symbolu, modułu, numeru linii backupu oraz adresu. Jest 228 definicji w bibliotekach, 47 w [`engine/`](../../src/engine) i 478 w [`recovered/`](../recovered); główny plik nie zawiera już definicji ani deklaracji globalnych. Poprzedni licznik 750 pomijał trzy funkcje z wielowierszowymi parametrami. Typ zwrotny `FUN_000070ae` również jest obecny, ale w poprzednim wierszu sygnatury. Nazwy `thunk_FUN_...` są osobnymi symbolami; adres z ich sufiksu może oznaczać cel, nie początek thunka.

| Plik | Liczba funkcji | Zakres |
|---|---:|---|
| [disk.c](./disk.c) | 10 | Wybrane funkcje DOS-owego I/O plików i buforowanych strumieni. Klasyfikacja jest heurystyczna. |
| [system.c](./system.c) | 10 | Usługi systemowe, DPMI, BIOS, timer, IRQ i joystick. |
| [vga.c](../../src/libs/vga.c) | 7 | BIOS wideo, porty palety VGA i prezentacja bufora obrazu. |
| [audio.c](./audio.c) | 45 | Zgrupowany obszar sterownika audio oraz funkcje używające jego konfigurowanych portów I/O. Typu karty nie ustalono. |
| [libc_conio.c](./libc_conio.c) | 116 | Funkcje z obszaru runtime Watcoma. W pseudokodzie nie zachowały się nazwy pozwalające wiarygodnie wskazać konkretne API conio. |
| [music_loaders.c](./music_loaders.c) | 40 | Sześć rodzin odczytu/konwersji modułów muzycznych i powiązane helpery; formaty oraz oryginalna biblioteka nie są jeszcze potwierdzone. |

Podział kategorii jest heurystyczny: dekompilator nie zachował nazw symboli ani wszystkich relacji bibliotecznych. Niektóre przypisania bazują na wywołaniach przerwań lub portów, inne na obszarze adresów. Pliki nie zawierają kompletnego zestawu używanych globali i zależności między funkcjami; nie należy ich traktować jako samodzielnych modułów kompilowalnych.

Czytelne nazwy i docelowe moduły są w [`RENAMES.tsv`](./RENAMES.tsv). Podział można powtórzyć poleceniem `perl tmp/tools/split_pseudocode.pl`; walidacja bez zapisu: `perl tmp/tools/split_pseudocode.pl --check`, uruchamiane z katalogu projektu. Narzędzie sprawdza zgodność każdej sygnatury i ciała z backupem po odwróceniu zmian nazw, brak duplikatów/ubytków, aktualność spisu, wywołania oraz dołączenie modułów.

Aktywny kod znajduje się w `src/`, a manifesty i narzędzia analityczne w `tmp/`. Ścieżki modułów w manifestach zachowują poprzednie nazwy względne do `src/`; narzędzie mapuje je na aktualne lokalizacje.

Opcja `--complete` wydziela wszystkie pozostałe funkcje do neutralnych przedziałów adresowych oraz przenosi wspólne deklaracje do [`globals.inc`](../recovered/globals.inc). Sprawdza też ich zgodność z backupem i brak kodu poza modułami w pliku głównym. Przedziały adresowe nie oznaczają rozpoznania kolejnych bibliotek.

Docelowo potwierdzone implementacje standardowych API mają być zastępowane oryginalnymi bibliotekami, nie rozwijane jako kopie dekompilacji. Samo umieszczenie funkcji w `libc_conio.c` nie potwierdza takiej zgodności. Przed zamianą trzeba ustalić kontrakt, ABI i zachowanie błędów; obecnie nie wykonano jeszcze żadnej zamiany na natywne API.

Grupa muzyczna powstała na podstawie łańcuchów wywołań, wspólnych rekordów wzorców/kanałów i konwersji indeksów do wskaźników, nie samego sąsiedztwa adresów. Nazwy `music_load_family_a`–`music_load_family_f` są neutralnymi nazwami sześciu punktów wejścia, nie identyfikatorami formatów. Pozostałe 34 funkcje zachowują nazwy adresowe; manifest dopuszcza identyczną nazwę oryginalną i aktualną dla samego przeniesienia. Dwa helpery rodziny B (`FUN_00027010`, `FUN_000271f0`) przeniesiono z błędnej heurystycznej kategorii systemowej. Wspólne wrappery alokacji `FUN_00025c00`, `FUN_00025c0c`, `FUN_00025c1c` i helper konwersji `FUN_00030a70` pozostają poza grupą.

Dowody: [music_loader_dispatch.asm](../../bin/music_loader_dispatch.asm), [music_loader_headers.asm](../../bin/music_loader_headers.asm). Obsługa AMF używana przez grę jest widoczna osobno pod kodem `0x19a71`; nie oznacza to, że wszystkie wydzielone rodziny są loaderami AMF. Nie wykonano jeszcze podmiany na oryginalną bibliotekę muzyczną.
