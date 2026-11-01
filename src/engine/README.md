# Wydzielone bloki silnika

## Migracja DOS64

`LK_DOS64_NATIVE` wybiera zmigrowane implementacje w istniejących modułach:
[resources.c](resources.c), [resource_decoder.c](resource_decoder.c) i
[sprites.c](sprites.c). Stare ciała w gałęziach alternatywnych są materiałem
do dalszego odtwarzania, nie kodem linkowanym do EXE. Natywne sygnatury używają
jawnych buforów, rozmiarów i błędów zamiast rejestrów oraz globalnych adresów DOS.
Sprawdzanie eksportu nadal dotyczy zachowanych ciał; testy natywnych gałęzi są
osobne, opisane w [README projektu](../../README.md).

Podział na podstawie potwierdzonego przepływu instrukcji, bez odtwarzania brakujących ciał C:

| Moduł | Definicje | Zakres |
|---|---:|---|
| [render.c](./render.c) | 10 | Przygotowanie widoku, etapy rysowania, warianty sceny, przebieg obiektów, pula węzłów renderowania i sterowanie animacją. |
| [timing.c](./timing.c) | 1 | Dispatcher aktualizacji z akumulatorem czasu. |
| [objects.c](./objects.c) | 3 | Aktualizacja listy obiektów przez callbacki oraz pobieranie i zwracanie obiektu do puli. |
| [input.c](./input.c) | 1 | Odczyt sterowania: klawiatura, joystick, odtwarzane wejście. |
| [resources.c](./resources.c) | 10 | Wyszukiwanie wpisu archiwum EPF, odczyt informacji, ładowanie zasobu, odczyt surowych bajtów, wrappery i zarządzanie slotami zasobów. |
| [resource_decoder.c](./resource_decoder.c) | 2 | Dekoder słownikowy danych EPF i ustawianie szerokości kodów. |
| [audio_control.c](./audio_control.c) | 3 | Wybór muzyki, ustawienie efektu i zatrzymanie dwóch kanałów efektów; warstwa gry nad sterownikiem audio. |
| [audio_config.c](./audio_config.c) | 3 | Parsowanie konfiguracji, przygotowanie ustawień urządzenia i inicjalizacja backendu audio. |
| [tiles.c](./tiles.c) | 3 | Parametry kafelków oraz przebiegi dla wpisów bez bitu `0x2000` i z tym bitem. |
| [tile_blitters.c](./tile_blitters.c) | 6 | Kopiowanie pikseli kafelków: nieprzezroczyste/przezroczyste, pełna szerokość i przycięcie po lewej/prawej. |
| [sprites.c](./sprites.c) | 1 | Rysowanie klatki sprite'a z zasobu w slocie, przycinanie do widoku i odbicie poziome. |
| [assets.c](./assets.c) | 4 | Przygotowanie zestawu zasobów poziomu oraz ładowanie list nazw zasobów i próbek audio. |
| [main.c](./main.c) | 1 odtworzona | Odpowiednik wejścia gry pod `0x10010`; kolejność inicjalizacji, uruchomienie sterowania grą i ścieżka sprzątania. |

Łącznie: 47 definicji silnika, 228 bibliotecznych i 478 w neutralnych blokach [recovered/](../recovered/). Zachowano wszystkie 753 definicje eksportu, w tym trzy wcześniej pomijane przez licznik sygnatury wielowierszowe. W głównym pliku nie pozostają żadne funkcje. Grupa [music_loaders.c](../libs/music_loaders.c) jest w bibliotekach, nie w silniku.

Dodatkowo odtworzono `game_main` w [main.c](./main.c) na podstawie
[main_flow.asm](../../bin/main_flow.asm). Nie pochodzi z backupu, więc nie wchodzi
do 753 definicji ani ich spisu. Agregator go dołącza; validator osobno sprawdza
jego obecność i właściciela. Nazwa `game_main`, zamiast hostowego `int main`,
nie narzuca jeszcze platformy ani wymyślonego kodu powrotu.

`game_main` wywołuje istniejące moduły konfiguracji audio i inicjalizacji
zegara. Wywołania bez zachowanych definicji mają jawne deklaracje `extern`
z adresami, nie puste implementacje. Dotyczy to również `FUN_000046b0`:
nadrzędna maszyna stanów i pętla rozgrywki nadal wymagają odtworzenia.
Nie zastąpiono jej samym wywołaniem renderera, które zgubiłoby intro, menu,
przejścia poziomów i obsługę wyjścia. To spięcie logiczne, nie działający linker
ani odtworzone ABI rejestrowe DOS.

Test: `perl tools/check_main.pl` sprawdza cele wszystkich 11 wywołań i stałe
w oryginalnym obiekcie kodu, następnie kompiluje izolowany harness z atrapami
wyłącznie testowymi. Weryfikuje kolejność wywołań `game_main`, offset EPF `4`,
offset komunikatu `0x11` i ustawienie flagi joysticka przed kalibracją, w tym
zachowanie wyzerowania flagi przez kalibrację. Nie testuje działania gry.
Pięć instrukcji przed wyeksportowanymi funkcjami audio to zapisy rejestrów na
stos, dlatego dla logicznego przepływu użyto istniejących nazwanych ciał;
nie oznacza to naprawy ich błędów dekompilacji.

Prezentacja bufora `vga_present_frame` znajduje się w [libs/vga.c](../libs/vga.c), nie w rendererze silnika.

Główny [pseiudo.c](../pseiudo.c) dołącza moduły i [globals.inc](../recovered/globals.inc); nie przechowuje już deklaracji ani ciał funkcji. Pliki nie są osobnymi jednostkami kompilacji ani działającym portem. Zachowano sygnatury i ciała eksportu, w tym błędy dekompilatora. Czytelna nazwa oznacza ustaloną rolę, nie poprawność implementacji. W szczególności wyeksportowany dispatcher zawiera błędną stałą zamiast odczytu ticków, a przygotowanie widoku — błędne stałe zamiast obliczeń widocznych w asemblerze.

`render_stage_one` i `render_stage_two` to celowo neutralne nazwy: nie potwierdzono jeszcze, które fragmenty przedstawiają tło, teren czy nakładki. Renderer obiektów modyfikuje też stan animacji. Nie przesunięto tych efektów ubocznych do aktualizacji logiki.

Mapowanie nazw i pochodzenia: [RENAMES.tsv](../libs/RENAMES.tsv) i [FUNCTIONS.tsv](../libs/FUNCTIONS.tsv). Dowody semantyczne: [FINDINGS.md](../../FINDINGS.md), [main_flow.asm](../../bin/main_flow.asm), [frame_timing.asm](../../bin/frame_timing.asm).

Dowody kolejnego podziału: [module_blocks.asm](../../bin/module_blocks.asm). Pula obiektów aktualizacji i pula węzłów renderowania są odrębne: nie połączono ich struktur. Funkcje `engine_acquire_object` i `engine_release_object` zarządzają pulą gry, nie są standardowym `malloc/free`. Obsługa EPF również nie jest biblioteką standardową: wywołuje niższą warstwę seek/read i własny dekoder. Dekoder został wydzielony jako `resources_decode_dictionary_stream`; dowody w [resource_decoder.asm](../../bin/resource_decoder.asm). Jego kod maszynowy używa słownika prefiksów/sufiksów, szerokości 9–14 bitów i kodów sterujących zależnych od szerokości. Jest podobny do LZW, ale nie potwierdzono zgodności z konkretną biblioteką. Moduły nie są jeszcze hermetyczne.

Walidacja: `perl tools/split_pseudocode.pl --check`. Potwierdza zachowanie eksportu, nie poprawność gry. Kolejne etapy: wydzielać następne rozpoznane bloki, odzyskiwać poprawne funkcje z EXE, definiować interfejsy i zastępować potwierdzone standardowe API oryginalnymi bibliotekami.

Dowody slotów, kafelków i audio: [tile_audio_blocks.asm](../../bin/tile_audio_blocks.asm). Sloty `DS:0x114c` tworzą tablicę 250 wskaźników; `0xffff` oznacza wybór wolnego slotu. Helpery niskopoziomowego rysowania kafelków przeniesiono do [tile_blitters.c](./tile_blitters.c). Nazwy przebiegów opisują bit wpisu, nie przypuszczalną warstwę wizualną. Przy audio zachowano nazwy zaczynające się od `audio_config_`, żeby odróżnić inicjalizację od sterownika i bieżącego odtwarzania.

Eksport `audio_config_parse_settings` zaczyna się pod `0x18a84`, wewnątrz rzeczywistej funkcji od `0x18a7f`; eksport `audio_config_initialize_backend` zaczyna się pod `0x18d1d`, wewnątrz funkcji od `0x18d18`. Przeniesiono dokładnie wyeksportowane ciała, bez dopisywania brakujących prologów. Adresy w spisie opisują eksport, nie gwarantują poprawnych granic funkcji EXE.

Dowody blitterów: [tile_blitters.asm](../../bin/tile_blitters.asm). Dane kafelka zajmują 64 bajty (8×8), indeks jest mnożony przez 64, a krok docelowego wiersza wynosi 320 bajtów. Bit `0x8000` odwraca kolejność kolumn, `0x4000` kolejność wierszy. Wariant przezroczysty pomija piksel o wartości zero; nie używa kanału alfa. Warianty nieprzezroczyste korzystają też z parametrów pionowego wycinka, dlatego `opaque_full_width` nie oznacza zawsze pełnej wysokości. Pseudokod nadal ma uszkodzone adresy i liczniki; nie zastąpiono tych funkcji przez `memcpy`, które nie zachowuje odbić, przezroczystości i kroku wierszy.

Dowody sprite'ów i zestawów zasobów: [asset_loading_blocks.asm](../../bin/asset_loading_blocks.asm). `assets_reload_level_samples` zwalnia poprzednie próbki i ładuje listy zależne od stanu; nie jest wyłącznie funkcją zwalniającą. Listy nazw zawierają pola o szerokości 8 bajtów z usuwaniem końcowych spacji. Rozdzielono warstwę zestawów od czytnika EPF i od sterownika audio, ale zależności do niewydzielonych helperów nadal istnieją.
