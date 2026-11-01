# Ustalenia dotyczące `pseiudo.c`

## Podsumowanie strukturalne

- Plik zawiera około 750 funkcji i 802 ostrzeżenia dekompilatora.
- To pseudokod, a nie kod gotowy do kompilacji. Zawiera nieprawidłowe deklaracje, np. `LAB_xxx+1`.
- Adresy w pliku są przesunięte względem adresów używanych w dokumentacji: plik używa bazy 0, a dokumentacja bazy `0x10000`. Aby je uzgodnić, do adresów z pliku należy dodać `0x10000`. Przykładowo punkt wejścia to `0x35ad4` w pliku, czyli `0x45ad4` po normalizacji.
- Nie znaleziono kodu zmiennoprzecinkowego; obliczenia gry są wykonywane na liczbach całkowitych.
- Konwencja wywołań to Watcom `__regparm3`.

## Wywołania systemowe

- `INT 21h` (DOS): 41 użyć, związanych z plikami, pamięcią oraz wejściem/wyjściem.
- `INT 31h` (DPMI): 8 użyć, dotyczących pamięci chronionej, przerwań i mapowania.
- `INT 10h` (BIOS wideo): 4 użycia, prawdopodobnie do ustawiania trybu graficznego.
- `INT 1Ah` (zegar): 1 użycie.
- `INT 15h`: 1 użycie.

## Sprzęt i porty

Wykryto 184 odwołania do portów. Część wyrażeń jest ucięta przez dekompilator, więc liczba ta jest dolną granicą.

- `0x3C8` / `0x3C9`: porty palety VGA. Wskazuje to na tryb 256 kolorów, prawdopodobnie 320x200.
- `0xA0000`: dwa odwołania do pamięci wideo. Rysowanie odbywa się głównie przez wskaźnik, a nie przez stały adres.
- `0x201`: joystick; 10 odczytów.
- `0x40` / `0x43`: timer PIT, prawdopodobnie wykorzystywany do taktowania gry.
- `0x21` / `0xA1`: kontrolery PIC, co wskazuje na własne obsługi IRQ.
- Występuje wiele odwołań do portów przez zmienne, np. `out(DAT_...)`. Mogą dotyczyć karty dźwiękowej, której porty są konfigurowane w `LIONKING.CFG`. Na podstawie samego pseudokodu nie da się ustalić dokładnego typu karty.

## Struktura funkcji

- Najczęściej wywoływane funkcje, prawdopodobnie niskopoziomowe narzędzia:
  - `FUN_000062c0`: 178 wywołań.
  - `FUN_0000a75c`: 90 wywołań.
  - `FUN_0000a780`: 82 wywołania.
- Największe funkcje (około 300–580 linii) znajdują się w obszarach `0x26000`–`0x2b000` oraz `0x38000`. Mogą odpowiadać za rysowanie, animację lub biblioteczne formatowanie.
- Funkcje w obszarze `0x9000`–`0xA800` wyglądają na związane z obsługą plików i pamięci.
- Obszar `0x35000` i dalszy zawiera kod startowy Watcoma, zgodnie z położeniem punktu wejścia.

## Ograniczenia analizy

- W pliku nie ma wyodrębnionych napisów, dlatego nie da się nazwać funkcji na podstawie komunikatów.
- Bez nazw symboli i sygnatur FLIRT nie da się wiarygodnie oddzielić logiki gry od bibliotek bez dalszej ręcznej analizy.
- Dalszym krokiem może być wyciągnięcie napisów z `obj2_data.bin` i próba powiązania ich z funkcjami.

## Wyodrębnione grupy bibliotek

Wstępny podział funkcji znajduje się w katalogu [`libs/`](./libs/). Zawiera osobne pliki dla DOS-owego I/O, usług systemowych, VGA, audio oraz runtime Watcoma/libc/conio. Podział jest heurystyczny; szczegóły i ograniczenia opisuje [`libs/README.md`](./libs/README.md).

Aktualny [`libs/FUNCTIONS.tsv`](./libs/FUNCTIONS.tsv) zawiera 216 wydzielonych definicji wraz z oryginalnymi i aktualnymi nazwami oraz modułami. Każda z 750 definicji trafia dokładnie do jednego miejsca: 190 do `libs/*`, 26 do `engine/*`, a 534 pozostaje w głównym [`pseiudo.c`](./pseiudo.c). Poprzedni licznik 749 pomijał deklarację `FUN_000070ae` bez typu zwrotnego; funkcja była zachowana. Oryginał jest zachowany jako [`pseiudo.c.backup`](./pseiudo.c.backup).

## Następny krok analizy

### Weryfikacja pliku EXE

Dodany [`OLD.EXE`](./bin/OLD.EXE) jest właściwym plikiem gry: rozpoznano format MS-DOS LE z DOS/4G, a zawarte napisy to m.in. `Disney's The Lion King`, `lionking.cfg` i `lionking.epf`. W nagłówku LE punkt wejścia ma obiekt `1` i offset `0x35ad4`; baza obiektu 1 wynosi `0x10000`, więc liniowy adres wejścia to `0x45ad4`. Potwierdza to wcześniejszą korektę bazy adresów.

W pseudokodzie nie ma definicji funkcji zaczynającej się pod surowym offsetem `0x35ad4`. Analiza instrukcji EXE, opisana poniżej, potwierdza jednak rzeczywisty kod w tym miejscu.

### Odwzorowanie obiektów i stron LE

- Wewnętrzny nagłówek MZ: offset plikowy `0x25214`.
- Nagłówek LE: `0x27c64` (`0x25214 + 0x2a50`).
- Pole początku danych stron LE: `0x25a00`, względem wewnętrznego MZ, nie względem początku całego EXE. Rzeczywisty początek stron w pliku to `0x4ac14`.
- Rozmiar strony: `0x1000`. Wpis mapy stron ma 3-bajtowy numer strony (najstarszy bajt pierwszy) i bajt flag.
- Obiekt 1: baza `0x10000`, rozmiar wirtualny `0x39dc0`, 58 stron, początek plikowy `0x4ac14`.
- Obiekt 2: baza `0x50000`, rozmiar wirtualny `0x215b0`, 32 strony, początek plikowy `0x84c14`.
- Cały [`obj1_code.bin`](./bin/obj1_code.bin) (236992 bajty) i cały [`obj2_data.bin`](./bin/obj2_data.bin) (129673 bajty) porównano bajt po bajcie z odpowiednimi fragmentami EXE: oba są identyczne. Zrzut danych jest krótszy od rozmiaru wirtualnego obiektu; nie należy zakładać, że zawiera pełny obraz pamięci ani relokacje.
- Wejście leży na logicznej/plikowej stronie 54 obiektu 1, pod offsetem plikowym `0x806e8`.

### Potwierdzona ścieżka startowa

Disasemblacja jest zapisana w [`bin/startup.asm`](./bin/startup.asm). Adresy instrukcji są prezentowane z bazą kodu `0x10000`. Obszar tekstowy pomiędzy skokiem wejściowym a właściwym startupem celowo pominięto w disasemblacji, aby nie traktować napisu jako instrukcji.

| Offset w obiekcie kodu | Adres z bazą `0x10000` | Ustalenie |
|---|---|---|
| `0x35ad4` | `0x45ad4` | Bajty `EB 76`: skok do `0x45b4c`, ponad osadzonym napisem identyfikującym runtime Watcoma. |
| `0x35b4c` | `0x45b4c` | Początek właściwego startupu: wyrównanie stosu, wykrywanie środowiska DOS/extendera, przygotowanie argumentów/środowiska i zerowanie pamięci. |
| `0x35d57` | `0x45d57` | Wywołanie `0x46fce` z `EAX = 0xff`. |
| `0x36fce` | `0x46fce` | Dispatcher tabeli inicjalizatorów: wybiera wpisy według priorytetu, wywołuje wskaźniki i oznacza obsłużone wpisy. |
| `0x35d5e` | `0x45d5e` | Wywołanie `0x46f7f`. |
| `0x36f7f` | `0x46f7f` | Przygotowanie runtime i wywołanie `0x497c3`, następnie pobranie wartości z `DS:0x2059c` i `DS:0x205a0`. |
| `0x36fbf` | `0x46fbf` | Bezpośrednie wywołanie `0x10010`, prawdopodobnego odpowiednika `main` gry. |
| `0x00010` | `0x10010` | Sekwencja wywołań inicjalizacyjnych i dalszego kodu gry; tej funkcji nie ma w pseudokodzie. |
| `0x36fc4` | `0x46fc4` | Po powrocie z kodu gry wywołanie `0x45f1a`, funkcji obecnej w pseudokodzie jako `FUN_00035f1a`. |

Funkcja pod `0x10010` wywołuje kolejno `0x10084`, `0x10070`, `0x10740`, `0x10b70`, `0x12210`, `0x18a7f`, `0x18d18`, `0x13677`, `0x1864c`, `0x146b0` i `0x101f0`. `0x1864c` odpowiada istniejącej `FUN_0000864c`; pozostałych dokładnych nazw odpowiadających celom tej sekwencji nie znaleziono w obecnym pseudokodzie. Nie przypisano jeszcze tym wywołaniom nazw semantycznych.

Adresy `DS:...` z instrukcji są offsetami względem segmentu danych. Nie należy dodawać im automatycznie bazy kodu `0x10000`; obiekt danych ma odrębną bazę `0x50000`, a relokacje wymagają osobnej analizy.

### Zalecany kolejny etap

Obecny podział zachowuje kompletność tylko względem 750 definicji wyeksportowanych przez dekompilator, a nie całego kodu EXE. Brak startupu i prawdopodobnego `main` jest potwierdzony, nie wynika z utraty funkcji przy podziale.

Należy uzupełnić analizę/dekompilację od offsetów `0x35ad4`, `0x35b4c`, `0x36f7f`, `0x36fce` i `0x10`, zachowując poprawne granice instrukcji oraz relokacje. Następnie prześledzić wywołania z `0x10`, zwłaszcza `0x46b0` i `0x1f0`, aby rozpoznać sterowanie grą. Nie zastąpiono brakujących funkcji wymyślonym pseudokodem.

## Ścieżka od wejścia gry do pętli

Dowody instrukcyjne zapisano w [`bin/main_flow.asm`](./bin/main_flow.asm). Poniższe adresy kodu zawierają bazę `0x10000`; offset w obiekcie kodu to adres minus `0x10000`. Nazwy semantyczne są opisami analitycznymi, nie odzyskanymi symbolami.

| Adres | Rola | Dowód | Pewność |
|---|---|---|---|
| `0x10084` → `0x100d2` | Zachowanie poprzedniego stanu wideo | Odczyt BIOS Data Area i `INT 10h` z `AH=03h` (pozycja kursora). | Wysoka |
| `0x10070` → `0x100ac` | Włączenie VGA mode 13h i przygotowanie bufora | `AX=0013h`, `INT 10h`; alokacja `0x10e00` bajtów, jeśli bufor `DS:0x39c` jest pusty. Tryb 320×200, 256 kolorów jest teraz potwierdzony, nie tylko przypuszczalny. | Wysoka |
| `0x10740` → `0x10790` | Instalacja obsługi timera | DOS `AX=3508h` i `2508h` (pobranie/ustawienie wektora 08h), następnie wywołanie funkcji programującej PIT. | Wysoka |
| `0x10b70` → `0x10b98` | Instalacja obsługi klawiatury | DOS `AX=3509h` i `2509h` (wektor 09h), zerowanie 128 bajtów tablicy wejścia pod `DS:0x10b3`. | Wysoka |
| `0x12210` → `0x1224a` | Otwarcie i odczyt indeksu archiwum zasobów | `main` przekazuje `EAX=4`; pod offsetem danych `4` jest `lionking.epf`. Wywołania open/read/seek, odczyt 11 bajtów nagłówka i alokacja tabeli o rozmiarze liczba wpisów × `0x16`. | Wysoka |
| `0x18a7f` | Odczyt konfiguracji dźwięku | Argumenty `0x135` i `0x133` odpowiadają napisom `lionking.cfg` i `r`. Parser porównuje pola z `SOUND`, `MUSIC`, `EFFECTS` i używa formatów tekstowych. | Wysoka |
| `0x18d18` | Inicjalizacja wybranego backendu audio | Rozgałęzienia według identyfikatora urządzenia, połączenie m.in. z kodem `0x3dc2d` (`FUN_0002dc2d`). Nie przypisano jeszcze identyfikatorów do nazw kart. | Wysoka dla roli, nieustalona dla modeli kart |
| `0x13677` | Kalibracja osi joysticka | Wyzerowanie offsetów `DS:0x4df5/0x4df7`, wywołanie znanej obsługi gameportu `0x136a7`, zapis wyników jako offsetów. | Wysoka |
| `0x1864c` | Inicjalizacja stanu losowego z BIOS-u zegara | Istniejąca `FUN_0000864c`; `INT 1Ah` i zapis kombinacji rejestrów pod `DS:0x1c38c`. Dokładny algorytm generatora wymaga analizy jego konsumentów. | Wysoka dla pobrania zegara, średnia dla roli ziarna |
| `0x146b0` | Sterowanie ekranami i rozgrywką | Pętle, przygotowanie obiektów, sprawdzanie wejścia, przejścia stanu i dispatch aktualizacji; opis poniżej. | Wysoka |
| `0x101f0` → `0x10207` | Sprzątanie i zakończenie | Przejście do wyłączania timera, helpera klawiatury, odtworzenia wideo, wyjścia tekstowego i `0x45f1a`. To nie pętla gry. | Wysoka |

Porównania napisów wykonano na zrzucie danych, nie na offsetach plikowych całego EXE. Natomiast selektory segmentów i wskaźniki zapisane w niezałatanym kodzie nie są jeszcze kompletnym obrazem runtime; np. natychmiastowe zera przy ładowaniu segmentów wymagają uwzględnienia fixupów LE.

### Zidentyfikowana struktura pętli

1. `0x146b0` rozpoczyna ustawienie stanu. Ścieżka zależna od `DS:0x173f1` może ominąć pierwszy ekran.
2. Pierwsza pętla (`0x14777`–`0x147a9`) wykonuje callback `0x147b2` przez dispatcher `0x14520`, czyści bufor, wywołuje rysowanie i kopiuje obraz do VGA przez `0x10234`. Kończy się po wyzerowaniu licznika `DS:0x5011`, początkowo `0x82`. To ekran czasowy/intro; jego dokładnej nazwy nie ustalono.
3. Kod od `0x14802` przygotowuje stan i obiekty, wybiera wpisy z tabel oraz ścieżkę zależną od `DS:0x173f1`. Dane tej ścieżki sugerują odtwarzanie wcześniej przygotowanego wejścia, ale nazwa „demo” pozostaje hipotezą.
4. Pętla rozgrywki (`0x14a17`–`0x14abe`) odczytuje wejście i flagi stanu. Wywołuje `0x144a3`, a następnie `0x14520` z callbackiem `0x14f50`. Brak sygnału pod `DS:0x10b4` powoduje skok wstecz do `0x14a17`.
5. Dispatcher `0x14520` wylicza liczbę aktualizacji z `DS:0x1085`: mnoży wartość przez 5, dodaje akumulator `DS:0x541d`, dzieli przez 10, zachowuje resztę i wywołuje callback tyle razy, ile wynosi iloraz. Jest to dowód integerowego akumulatora taktowania. Nominalne taktowanie opisano niżej; rzeczywistej częstotliwości nie zmierzono.
6. Callback `0x14f50` inkrementuje licznik `DS:0x173a0`, wywołuje helper wejścia `0x184bc`, przechodzi listę obiektów od `DS:0x1fa84`, ustawia bieżący obiekt `DS:0x1c394` i wywołuje jego funkcję przez wskaźnik. Obsługuje też przypadek usunięcia obiektu.
7. Przy zmianie stanu kod `0x1454e` wybiera następny wpis z tabeli i przechodzi do przygotowania kolejnej części gry. Ścieżka `0x14ac5` wykonuje sprzątanie i wraca skokiem `0x14af1` do `0x146b0`.

Nie ustalono jeszcze, który warunek całkowicie kończy tę maszynę stanów. Istniejąca ścieżka kończąca `main` pod `0x101f0` jest rozpoznana, ale nie oznacza, że każda gałąź sterowania wraca tam normalnie; część ścieżek skacze bezpośrednio do `0x10207`.

### Wnioski dla dalszego podziału

- `0x14520`, `0x14f50` oraz kod `0x1454e`–`0x14af6` to kandydaci do przyszłej grupy silnika: taktowanie, aktualizacja obiektów i sterowanie stanem.
- `FUN_00000234` jest kopiowaniem obrazu do pamięci VGA: `16000` DWORD-ów, czyli `64000` bajtów. Została przeniesiona do `libs/vga.c` jako `vga_present_frame`.
- Przed dodaniem brakującego pseudokodu należy wyeksportować prawidłowe funkcje z dekompilatora. Dowody asemblerowe pozwalają nazwać role, ale nie uzasadniają zgadywania sygnatur, globali ani odtworzonego C.
- Następny konkretny cel: prześledzić `0x144a3`, źródło licznika `DS:0x1085` i flagę `DS:0x10b4`, aby ustalić kolejność renderowania, rzeczywistą częstotliwość aktualizacji oraz warunki pauzy/przejścia/wyjścia.

## Taktowanie, renderowanie i wyjście — uzupełnienie

Dowody zapisano w [`bin/frame_timing.asm`](./bin/frame_timing.asm). Jest to analiza statyczna niezałatanych obiektów LE; nie uruchamiano gry.

### Producent czasu i nominalna częstotliwość

- Instalacja timera `0x10790` ustawia dzielnik PIT `0x4268 = 17000`, czyli około **70,187 Hz** przy zegarze PIT `1193182 Hz`. To wartość początkowa, nie stałe taktowanie gry.
- Handler `0x1084d` inkrementuje word `DS:0x1082`, byte `DS:0x1084` oraz DWORD `DS:0x1c390`. Na początku obsługi programuje PIT wartością `0xffff`; przed powrotem, pod `0x109b4`, ustawia **`0x2e36 = 11830`**, czyli nominalnie **100,861 Hz**. Pominięcie tego ponownego programowania prowadziłoby do błędnego wniosku o aktualizacjach 35 Hz.
- `0x10234` atomowo pobiera i zeruje `DS:0x1084` pomiędzy `CLI` i `STI`, zapisuje pobraną liczbę do `DS:0x1085`, a potem kopiuje obraz do VGA. To liczba ticków od poprzedniego pobrania, nie licznik klatek ani stała „delta”.
- Dispatcher `0x14520` wykonuje `floor((ticks * 5 + remainder) / 10)` aktualizacji i zachowuje resztę modulo 10. Oznacza to średnio jedną aktualizację na dwa zliczone ticki, nominalnie **50,430 aktualizacji/s** przy dzielniku 11830.
- Jest też odrębna ścieżka sekwencji zdarzeń `0x109cf`–`0x10acb`: pobiera dwunastobajtowe rekordy, programuje PIT z pola `[esi+0xa]`, wykonuje callback z tabeli oraz oblicza pozostały odcinek względem `0x2e36`. Nie potwierdzono jeszcze, gdzie ta ścieżka jest aktywowana. Nie wolno utożsamiać każdego sprzętowego IRQ ze zliczonym tickiem głównego handlera.

**Ograniczenia:** częstotliwości są obliczeniami z dzielników, nie pomiarem. Przeprogramowanie PIT w handlerze, czas obsługi przerwań, ich blokowanie i alternatywna ścieżka mogą zmieniać rzeczywiste odstępy. `DS:0x1084` jest bajtem i zawija się po 256 zliczeniach; po długiej przerwie nie zachowuje pełnego czasu. Kod pauzy celowo zeruje oba liczniki przy wznowieniu. Akumulator `DS:0x541d` jest współdzielony z innymi sekwencjami, w tym pętlą dzielącą przez 7 pod `0x143f2`, więc proporcji 1/2 nie należy przypisywać wszystkim ekranom.

### Kolejność jednej iteracji rozgrywki

Ścieżka bez zmiany stanu pod `0x14aa2`:

1. `0x144a3` przygotowuje i prezentuje obraz.
   - `0x11799` ogranicza pozycję widoku do wymiarów obszaru minus 320×200 i przygotowuje współrzędne wyrównane do 8 pikseli.
   - `0x1181d` wykonuje pierwszy etap rysowania.
   - Ustawienie `DS:0x19aa4 = 0`, potem `0x18762`: pierwszy przebieg listy obiektów.
   - `0x11aae`: kolejny etap rysowania.
   - Ustawienie `DS:0x19aa4 = 0x80`, potem `0x18762`: drugi przebieg listy obiektów.
   - Dodatkowe wywołania zależne od numeru stanu `DS:0x173aa`; następnie `0x10234`, czyli kopia do VGA.
2. `0x14520` używa pobranych ticków i wywołuje aktualizację obiektów `0x14f50` zero lub więcej razy.
3. Kod sprawdza Esc i wraca do początku sprawdzania wejścia/stanu.

`0x18762` filtruje listę od `DS:0x1ca7c` według bitu `0x80` w polu obiektu `+0xe` oraz flagi ukrycia w `+0xf`. Rozdzielenie rysowania obiektów na dwa przebiegi jest potwierdzone. Nazwy „tło”, „pierwszy plan” i „HUD” dla poszczególnych etapów pozostają robocze.

**Ważna konsekwencja:** w tej ścieżce renderowanie jest przed aktualizacją logiki. Liczba prezentacji obrazu nie jest równa liczbie aktualizacji. W `0x144a3` i `0x10234` nie ma oczekiwania na retrace; istnieje osobny helper `0x10823`, który czeka na zmianę ticka lub na port VGA `0x3da`, ale jego obecność nie dowodzi synchronizacji każdej klatki. Ponadto renderer `0x18762` sam zmienia liczniki animacji — nie jest funkcją pozbawioną efektów ubocznych.

### Klawiatura: Esc, P i przejścia

| Stan/offset danych | Znaczenie i dowód |
|---|---|
| `DS:0x10b3 + scancode` | Tablica stanu klawiszy. IRQ klawiatury `0x10c0a` odczytuje port `0x60`, maskuje kod przez `0x7f`, a pod `0x10cbd` zapisuje stan do indeksowanego bajtu. Zwykłe naciśnięcie daje `0xff`, puszczenie `0`; Shift jest traktowany osobno. |
| `DS:0x10b2` | Ostatni surowy kod klawiatury, łącznie z bitem puszczenia. Nie jest wyłącznie kodem ostatniego naciśnięcia. |
| `DS:0x10b4` | Indeks `1` tablicy, czyli **Esc** dla używanego zestawu scancode. W pętli gry `0x14ab1` przechodzi do `0x14ac5`, wykonuje sprzątanie i wraca do `0x146b0` (ponowne wejście w sterowanie menu/ekranami). Nie oznacza natychmiastowego zakończenia EXE. |
| `DS:0x10cc` | Indeks `0x19`, czyli **P**. Blok `0x14caf` reaguje na P, rysuje ekran/element pauzy, zeruje stan P i czeka pod `0x14d71` na kolejne P. Przy wznowieniu wywołuje helper audio, odtwarza paletę i zeruje `DS:0x1084/0x1085`, zapobiegając nadrabianiu czasu pauzy. Wejście jest pomijane przy `DS:0x173f0 != 0` lub `DS:0x19a8c != 0`. Nie rozpoznano jeszcze wywołującego tego bloku w ścieżce aktualizacji. |
| `DS:0x19365 != 0` | Przejście do `0x1454e`, czyli wyboru/przygotowania następnego stanu. To nie jest flaga zakończenia programu. |
| `DS:0x173ce == 0` | Dodatkowa ścieżka przejścia: dla stanu >=12 skok do `0x1454e`, dla 11 kontynuacja, w pozostałych przypadkach dekrementacja `DS:0x173c6` i skok do `0x13fbb`. Interpretacja jako śmierć/utrata życia jest prawdopodobna, ale wymaga analizy dalszej ścieżki. |

**Potwierdzone zakończenie z menu:** kod pod `0x1328f` sprawdza Esc, wywołuje `0x18665` i wygaszenie palety `0x106fe`, ustawia `EDX=0x3169`, po czym skacze do `0x10207`. Pod tym offsetem danych znajduje się komunikat pożegnalny. Następnie wykonywana jest znana ścieżka sprzątania i zakończenia runtime. Daje to ścieżkę wyjścia z gry bez normalnego powrotu przez końcowe wywołanie w `main`.

### Następny cel po tej analizie

Odzyskano źródło czasu, kolejność renderowania, znaczenie Esc oraz blok pauzy. Przed naprawą implementacji należy ustalić połączenia pośrednie: wywołującego `0x14caf`, aktywację `0x109cf` i tablice callbacków obiektów. To wymaga interpretacji fixupów LE, nie kolejnego zgadywania na podstawie zepsutego eksportu C. Podział istniejących ciał można wykonywać już teraz, bez zmiany ich zachowania; pierwszy etap opisano poniżej.

## Pierwsze moduły silnika i czytelne nazwy

Wydzielono dziewięć istniejących definicji do [`engine/`](./engine/) i prezentację VGA do [`libs/vga.c`](./libs/vga.c). Wszystkie odwołania w aktywnym pseudokodzie używają nowych nazw; adresowe etykiety i globale pozostają bez zmian.

| Oryginalny symbol | Aktualna nazwa | Moduł |
|---|---|---|
| `FUN_00000234` | `vga_present_frame` | `libs/vga.c` |
| `FUN_00001799` | `render_prepare_viewport` | `engine/render.c` |
| `FUN_0000181d` | `render_stage_one` | `engine/render.c` |
| `FUN_00001aae` | `render_stage_two` | `engine/render.c` |
| `FUN_000044a3` | `render_game_scene` | `engine/render.c` |
| `FUN_000044f3` | `render_basic_scene` | `engine/render.c` |
| `FUN_00004520` | `engine_dispatch_ticks` | `engine/timing.c` |
| `FUN_00004f50` | `engine_update_objects` | `engine/objects.c` |
| `FUN_000084bc` | `input_poll_controls` | `engine/input.c` |
| `FUN_00008762` | `render_object_pass` | `engine/render.c` |

Nazwy wynikają z udokumentowanej analizy asemblera; nie poprawiono błędnych stałych, sygnatur ani globali eksportu. Narzędzie [`tools/split_pseudocode.pl`](./tools/split_pseudocode.pl) sprawdza wszystkie 750 sygnatur i ciał względem backupu po odwróceniu zmian nazw, wyłączność właściciela, wywołania, dołączenia modułów i spis pochodzenia. Przyszłe celowe poprawki implementacji będą wymagać dostosowania tej kontroli: obecnie gwarantuje zachowanie pseudokodu, nie poprawność gry.

Cel docelowy to działający program. Dalszy podział ma prowadzić do odzyskania poprawnych implementacji oraz zastępowania potwierdzonych standardowych API oryginalnymi bibliotekami. Nie wykonano jeszcze podmiany runtime na libc: nazwa kategorii nie wystarcza do ustalenia API, ABI ani semantyki błędów. Backup pozostaje nietknięty.

## Kolejny podział: zasoby, pule i sterowanie audio

Wydzielono kolejnych 13 definicji i zaktualizowano ich wywołania w całym aktywnym pseudokodzie. Dowody z oryginalnego obiektu kodu zapisano w [`bin/module_blocks.asm`](./bin/module_blocks.asm).

| Adres kodu | Aktualna nazwa | Moduł | Ustalona rola |
|---|---|---|---|
| `0x122d0` | `resources_get_entry_info` | `engine/resources.c` | Wyszukanie wpisu i zwrot pól `+0x12`/`+0xe` w rejestrach, z sygnalizacją przez CF. Eksport C nie zachował pełnego kontraktu. |
| `0x122e8` | `resources_load_entry` | `engine/resources.c` | Wyszukanie wpisu, seek w archiwum, alokacja i przejście do ścieżki odczytu/dekodowania. |
| `0x123d9` | `resources_find_entry` | `engine/resources.c` | Normalizacja nazwy i przeszukiwanie rekordów o rozmiarze `0x16`. Operacja zmienia bufor nazwy; nie jest zwykłym porównaniem bez efektów ubocznych. |
| `0x12457` | `resources_read_raw_bytes` | `engine/resources.c` | Odczyt surowych danych w porcjach maksymalnie `0x8000`. |
| `0x18350` | `engine_acquire_object` | `engine/objects.c` | Pobranie elementu z wolnej puli `DS:0x1fa80`, dołączenie do listy aktywnej i wyzerowanie stanu. |
| `0x183ee` | `engine_release_object` | `engine/objects.c` | Odłączenie z listy aktywnej i zwrot do puli; nie standardowy free. |
| `0x186b0` | `render_acquire_node` | `engine/render.c` | Pobranie z puli `DS:0x1ca78` i wstawienie do listy rysowania według pola kolejności. |
| `0x188f2` | `render_release_node` | `engine/render.c` | Odłączenie węzła rysowania i zwrot do jego odrębnej puli. |
| `0x1893c` | `render_disable_animation` | `engine/render.c` | Wyzerowanie bitu `0x20` w polu `+0xf`. |
| `0x18941` | `render_set_animation_period` | `engine/render.c` | Ustawienie okresu w `+0xd`, jeśli argument niezerowy, i włączenie bitu `0x20` dla niezerowego okresu. |
| `0x18f31` | `audio_control_set_effect` | `engine/audio_control.c` | Sterowanie jednym z dwóch kanałów efektów; identyfikator `-1` zatrzymuje kanał, inne konfigurują efekt. |
| `0x18fb9` | `audio_control_select_music` | `engine/audio_control.c` | Zatrzymanie/przygotowanie odtwarzania i warunkowe załadowanie wybranego utworu. `-1` pomija wybór nowego utworu. |
| `0x19187` | `audio_control_stop_effect_channels` | `engine/audio_control.c` | Wywołanie helpera zatrzymania dla kanałów `DS:0x19aa8` i `DS:0x19aa8 + 1`. |

W tym etapie nie zmieniono ABI, struktur, globali ani błędnych instrukcji eksportu. Nie zastąpiono puli obiektów przez `malloc/free`, archiwum EPF przez libc ani sterowania muzyką przez niepotwierdzone API zewnętrzne. To własne warstwy programu nad potencjalnie zastępowalnymi bibliotekami.

Po tym etapie pozostał do wydzielenia dekoder `FUN_0000248f` i wrappery zasobów; wykonano to w kolejnym etapie poniżej. Inicjalizacja audio i pul oraz niepewne helpery nadal wymagają ustalenia granic, zamiast nadawania nazw tylko według sąsiedztwa adresów.

## Wydzielenie dekodera EPF

Do [`engine/resource_decoder.c`](./engine/resource_decoder.c) przeniesiono:

- `FUN_0000248f` → `resources_decode_dictionary_stream` (kod `0x1248f`);
- `FUN_00002704` → `resources_set_code_width` (kod `0x12704`).

Do [`engine/resources.c`](./engine/resources.c) przeniesiono wrappery `FUN_0000221a` i `FUN_00002236` jako `resources_load_entry_wrapper` i `resources_get_entry_info_wrapper`. Są to opisy ról wrapperów, nie odtworzone kontrakty C; eksport nie zachował argumentów i wyników przekazywanych w rejestrach.

Dowody zapisano w [`bin/resource_decoder.asm`](./bin/resource_decoder.asm):

- Początkowa szerokość kodu wynosi 9 bitów (`0x124f1`), a indeks nowych wpisów słownika rozpoczyna się od `0x100` (`0x124ff`).
- Helper `0x12704` ustawia maskę `(1 << width) - 1`, kod resetu o jeden mniejszy i próg wzrostu słownika o dwa mniejszy od maski.
- Porównanie z maską prowadzi do zwolnienia czterech buforów i powrotu (`0x125d5` → `0x126db`). Porównanie z kodem resetu prowadzi do ponownego ustawienia indeksu słownika (`0x125e2` → `0x124ff`). Reset nie wykonuje ponownie instrukcji ustawiającej szerokość na 9 bitów.
- Dekodowanie przechodzi łańcuch wordowych prefiksów i bajtowych sufiksów, zapisuje je na stosie roboczym, a następnie emituje w odwrotnej kolejności (`0x1261a`–`0x1266f`).
- Kolejny wpis to poprzedni kod i pierwszy bajt bieżącej sekwencji. Szerokość rośnie do maksymalnie 14 bitów (`0x126b9`–`0x126c9`).
- Kod zawiera obsługę przypadku bieżącego kodu >= indeks następnego wpisu. Limit długości przechodzonego łańcucha wynosi `0xfa0`; jego przekroczenie prowadzi do błędu, nie cichego sukcesu.

To silne dowody rodziny LZW, lecz nie zgodności z konkretnym formatem czy biblioteką. Położenie kodów sterujących zależy tutaj od szerokości i różni się od popularnych wariantów. Nie podmieniono dekodera na standardową bibliotekę. Jego wyeksportowane ciało nadal zawiera błędne stałe i wskaźniki; przeniesienie nie jest naprawą implementacji.

Brakujące definicje inicjalizacji pul (`0x183b5`, `0x188c1`) nie mogą zostać po prostu przeniesione z eksportu: tych dokładnych funkcji w nim nie ma. Ich odtworzenie wymaga osobnego, zweryfikowanego etapu. Po tej ekstrakcji pozostały 534 definicje w pliku głównym; zachowano wszystkie 750.
