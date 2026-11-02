# Wydzielone bloki silnika

## Migracja DOS64

`LK_DOS64_NATIVE` wybiera zmigrowane implementacje w istniejących modułach:
[resources.c](resources.c), [resource_decoder.c](resource_decoder.c) i
[sprites.c](sprites.c). Stare ciała w osobnych plikach `*_legacy.inc`,
dołączanych tylko w gałęziach alternatywnych, są materiałem
do dalszego odtwarzania, nie kodem linkowanym do EXE. Natywne sygnatury używają
jawnych buforów, rozmiarów i błędów zamiast rejestrów oraz globalnych adresów DOS.
Sprawdzanie eksportu nadal dotyczy zachowanych ciał; testy natywnych gałęzi są
osobne, opisane w [README projektu](../../README.md).

[assets.c](assets.c) ma teraz natywny odczyt list nazw banków MCH oraz ładowanie
wybranego banku przez sprawdzony loader EPF. Lista młodego Simby z DS `0x744c`
zachowuje wszystkie 28 nazw i sloty 6-33. Próbka pozwala przełączać banki
klawiszami góra/dół; nie jest to zastępstwo logiki animacji ani rozgrywki.
Pełny loader zestawów poziomów i próbek audio pozostaje w
[assets_legacy.inc](assets_legacy.inc). Liczby definicji w tabeli poniżej
opisują zachowany eksport, nie liczbę natywnych funkcji.

[animation.c](animation.c) odtwarza wizualny podstrumień interpretera
`0x162c0` na podstawie handlera `0x1630b`, brakującego jako osobna funkcja
w eksporcie. Oryginalny eksport pozostaje w neutralnym bloku. Sekwencja idle
i deskryptory są wyciągane bez zmian z dumpu danych podczas budowania.
Próbka `--idle` uruchamia tę sekwencję automatycznie; A przełącza ją z ręcznym
przeglądaniem (`--manual` wybiera ręczny start). Zdarzenia tworzące obiekty gry
są wyłącznie jawnie rejestrowane w trybie diagnostycznym, nie wykonywane.
Nie jest to odtworzony pełny interpreter ani logika zachowania Simby.

`render_limit_camera_x` przenosi używany wynik 16-bitowy helpera `0x288e3`:
porównuje X ze znakiem z szerokością mapy w kafelkach *8-320 i ogranicza
tylko górną granicę. Nie dodano nieobecnego w oryginale dolnego limitu 0.
[check_camera_limit.c](../../tools/check_camera_limit.c) sprawdza wszystkie X
dla szerokości przy granicach i zawijanie wyniku.

`render_near_view` przenosi `0x2805c`: pozycja względem kamery i okna
320x200 z osobnymi marginesami ze znakiem. Krawędzie są wyłączone;
obliczenia granic są 32-bitowe, nie zawijane do 16 bitów.
[check_near_view.c](../../tools/check_near_view.c) sprawdza dokładne progi.

`render_local_rectangle_hit` odtwarza `0x1693d`: granice deskryptora obiektu
docelowego z odbiciami H/V i prostokąt lokalny względem obiektu bieżącego.
Ten drugi jest odbijany tylko poziomo, zgodnie z instrukcjami oryginału.
Porównania są ze znakiem, krawędzie włączone, współrzędne zawijane 16-bitowo.
[check_rectangle.c](../../tools/check_rectangle.c) sprawdza obie orientacje
obiektu źródłowego, wszystkie odbicia celu i skrajne współrzędne.

`render_objects_hit` przenosi `0x16a57`: dwa pełne deskryptory, niezależne
odbicia H/V i pozycje właścicieli. Współdzieli sprawdzony odczyt granic i
porównanie z testem prostokąta, bez globalnych buforów tymczasowych DOS.
[check_overlap.c](../../tools/check_overlap.c) sprawdza również symetrię wyniku
po zamianie obu obiektów i brak normalizacji zawiniętych granic.

Ścieżka idle używa teraz również oryginalnego nadrzędnego skryptu DS `0x5f84`:
inicjalizacja podstrumienia, wykonanie, powrót z zapisaniem adresu wznowienia
i względny skok pętli. Obsługiwane są też inicjalizacja oraz wykonanie
podstrumienia ruchu. Nierozpoznane identyfikatory handlerów zgłaszają błąd;
nie zostały zastąpione pustymi funkcjami. Próbka wywołuje ten executor zamiast
bezpośrednio wywoływać samą animację wizualną. Zachowano obraz i tempo.

Natywny silnik może również uruchomić oryginalną połączoną ścieżkę DS `0x3615`
przez `animation_movement_initialize` z [animation_data.h](animation_data.h).
Skrypt wybiera strumienie wizualny `0x362b` i ruchu `0x367a`, następnie przechodzi
do wspólnej pętli DS `0x325a`. Generator zachowuje oryginalne bajty skryptu,
strumieni i deskryptorów. [check_movement_program.c](../../tools/check_movement_program.c)
sprawdza 4000 aktualizacji, dokładne klatki, czas, zmianę stanu i pozycji,
odbicia oraz zawijanie współrzędnych. Nie przeniesiono jeszcze logiki wyboru
tego stanu ani kolizji; podgląd nadal pokazuje idle, bez nowego przypisania klawiszy.

Podział na podstawie potwierdzonego przepływu instrukcji, bez odtwarzania brakujących ciał C:

[physics.c](physics.c) przenosi oryginalne integratory 16.16: X `0x1a962`,
Y `0x1a99e`, grawitację `0x1a7ed` oraz ograniczenie prędkości `0x1a7bd/0x1a7d0`.
Dodawanie zachowuje 32-bitowe zawijanie, a limit `0x70000` używa porównania
ze znakiem. Grawitacja dodaje `0x4e00` przed zmianą pozycji i zawsze stosuje
limit, niezależnie od flagi wyłączającej go w drugim helperze.
[check_physics.c](../../tools/check_physics.c) sprawdza wszystkie ułamki 16-bitowe.

`engine_motion_accelerate_x` przenosi `0x1a9da` i helper `0x1cda1`:
32-bitowe dodanie przyspieszenia, ograniczenie ze znakiem do -4/+4 w 16.16,
następnie integracja X nową prędkością. Stan Y pozostaje bez zmian.
[check_acceleration.c](../../tools/check_acceleration.c) obejmuje wszystkie
ułamki oraz granice limitu i przepełnienia.

`engine_motion_brake_x` odtwarza `0x1a844` i `abs` z `0x1a60a`: zeruje
prędkość tylko przy ściśle mniejszej wartości bezwzględnej; w pozostałych
przypadkach odejmuje przekazany argument ze znakiem i zawijaniem 32-bitowym.
Nie dobiera sam kierunku hamowania. Zachowuje też x86 `abs(INT_MIN)`,
które pozostaje ujemne. [check_braking.c](../../tools/check_braking.c) sprawdza
te progi, oba znaki i niezmienione ułamki pozycji.

`engine_motion_right/left` przenoszą `0x1a886/0x1a8f2`, wymuszając odpowiednio
prędkość co najmniej +2 lub co najwyżej -2 przed integracją X. Tylko prawy
helper sprawdza bit 0x10 bajtu obiektu +0x4f i zeruje wtedy prędkość;
nie wprowadzono symetrycznej flagi, której nie ma w oryginale.
[check_directional_motion.c](../../tools/check_directional_motion.c) sprawdza
pełny zakres ułamków i granice porównań ze znakiem.

[render_object_bounds](render.c) i `render_point_hit` przenoszą test punktu
`0x168a4`: granice z deskryptora +2/+4/+6/+8, odbicia H/V, 16-bitowe
dodawanie pozycji i porównania ze znakiem z włączonymi krawędziami.
Trafienie zwraca oryginalne -1 przez parametr wyjściowy, brak trafienia 0;
błąd bufora jest osobnym statusem. Nie normalizujemy granic po zawinięciu,
bo oryginał też tego nie robi. Nie jest to jeszcze kolizja z mapą poziomu.

[behaviors.c](behaviors.c) przenosi konkretny handler `0x288a1`:
jednorazowe ustawienie skryptu DS `0x16741` i wyzerowanie typu przestrzennego,
sprawdzenie widoczności `0x1a743/0x1583d`, grawitacja, następnie interpreter.
Typowany [ENGINE_FALLING_OBJECT](behaviors.h) jest kontekstem natywnego obiektu,
bez zapisywania starych 32-bitowych wskaźników w bajtowym payloadzie.
Oryginalna sekwencja i deskryptor są wyciągane z dumpu bez zmian.
Usunięcie poza oknem zwalnia węzeł renderowania i zeruje bieżący obiekt;
istniejący dispatcher zwalnia obiekt i aktualizuje wskaźnik śledzony.
Flaga 1 omija sprawdzenie widoczności; flagi 2+4 wybierają stałe granice.
Okno musi całkowicie zawierać sprawdzane granice, jak w oryginale.

Callback z błędem ustawia `pool->update_status`; dispatcher zwraca go i nie
wykonuje następnych obiektów. Brak wymaganego okna, kontekstu, handlera skryptu
lub callbacku usuwania nie jest traktowany jako sukces.
Oryginalny handler zeruje typ przestrzenny. Jeśli inna logika później ustawi go
na niezerowy, wymagany jest `unlink_spatial`, wywołany przed zwolnieniem rendera.
Pełny indeks przestrzenny poziomu nadal wymaga migracji.
[check_falling.c](../../tools/check_falling.c) uruchamia rzeczywisty dispatcher,
nie osobną pętlę zastępującą zachowanie. Podgląd idle nie został zmieniony.

`engine_spawn_falling` przenosi ścieżkę `0x1508e -> 0x14fbd` dla dokładnego
rekordu DS `0x162fe`: handler `0x188a1`, zerowe flagi, początkowy deskryptor
`0xe540` i inicjalizator `0x188a1`. Rekord jest odczytywany z oryginalnych
danych, a identyfikatory sprawdzane zamiast rzutowania adresów na funkcje.
Tworzy obiekt i render, ustawia pozycję i porządek, następnie natychmiast
wykonuje oryginalny inicjalizator z zachowaniem wcześniejszego bieżącego obiektu.
Dispatcher odwiedza nowo dopisany obiekt jeszcze w tym samym przebiegu.
[check_spawn.c](../../tools/check_spawn.c) weryfikuje ten efekt, limity obu pul
i usuwanie podczas inicjalizacji.

To celowo tylko potwierdzony rekord, nie ogólny loader wszystkich definicji
obiektów. Stan i okno widoczności są dostarczane przez wywołującego i muszą
pozostać żywe. Nie można ponownie użyć stanu aktywnego obiektu w tej samej puli.
Natywna różnica bezpieczeństwa: brak zasobów lub błąd inicjalizacji nie
pozostawia częściowego obiektu z pustym renderem; zwracany jest błąd,
a przydzielone elementy są zwalniane. Usunięcie przez widoczność zwraca osobny
status 1; sukces z aktywnym obiektem 0, błąd -1.
Nie przeniesiono jeszcze wyboru obiektów przez pełną pętlę poziomu.

`engine_timed_behavior` odtwarza handler `0x2881d`: skrypt DS `0x16728`,
licznik 10, widoczność, dekrementacja licznika, utworzenie dziecka DS `0x162fe`
przy zerze na X rodzica i Y-16, następnie grawitacja i skrypt rodzica.
Dziecko powstaje przed przesunięciem rodzica; jest inicjalizowane od razu i
aktualizowane ponownie podczas dalszego przejścia tej samej listy.
[check_timed.c](../../tools/check_timed.c) sprawdza tę kolejność i zawijanie licznika.
Wywołujący dostarcza żywy stan dziecka oraz kolejność renderowania zamiast
nieistniejącego natywnego alokatora. Brak stanu lub zasobów zgłasza błąd.
Przy ponownym zerze po 65536 aktualizacjach potrzebny jest wolny stan dziecka;
aktywnego stanu nie nadpisujemy. Podgląd nie został zmieniony.

`engine_spawn_timed` odczytuje oryginalny rekord DS `0x162f0` i korzysta ze
wspólnej ścieżki tworzenia obiektu/rendera. Oba handler ID to `0x1881d`,
flagi zerowe, deskryptor początkowy `0xe4c8`. Inicjalizacja od razu zmniejsza
licznik do 9, więc dziecko powstaje w dziewiątej późniejszej aktualizacji
dispatchera, nie dziesiątej. Wywołujący przekazuje osobne żywe stany rodzica
i dziecka. [check_spawn_timed.c](../../tools/check_spawn_timed.c) sprawdza
całą tę ścieżkę bez ręcznego ustawiania handlera lub skryptu.

`engine_emitter_behavior` przenosi `0x2865d`: pierwsze wywołanie ustawia
kontynuację i wraca, kolejne zachowują licznik sprzed dekrementacji.
Przy aktywnej fladze DS `0x1938f` sprawdzane jest rozszerzone okno kamery,
na dolnych 7 bitach starego licznika 20/40 tworzone są rodzice na X-8/X+8.
Y jest wyrównywane do 4 z dodatkiem 2 zależnym od bitu 1 starego licznika.
Grawitacja zależy od znaku starego licznika, również przy wyłączonej fladze.
Na końcu wykonywany jest oryginalny skrypt.
Kamera i flaga są jawnymi żywymi wskaźnikami; pamięć łańcuchów rodzic/dziecko
dostarcza wywołujący jako sloty. Brak wolnego slotu jest błędem, nie pominięciem
tworzenia obiektu. [check_emitter.c](../../tools/check_emitter.c) sprawdza
160 aktualizacji z czterema emisjami i rzeczywistą aktualizacją całego łańcucha.

`engine_spawn_emitter` odtwarza oba wrappery `0x28773/0x28797`, warianty 0/1.
Rekord DS `0x162e2` ma handler/inicjalizator `0x1865d` i deskryptor `0xe4a0`.
Skrypt DS `0x166f6` lub `0x1670f` i licznik są przypisywane po powrocie
inicjalizatora; pierwsza klatka nie jest wykonywana w konstruktorze.
[check_spawn_emitter.c](../../tools/check_spawn_emitter.c) testuje oba warianty,
aktywną flagę i cały łańcuch emiter -> rodzic -> dziecko.
Sloty i ich stany muszą być wyłączne dla danego emitera i jego puli; ponowne
użycie następuje dopiero po usunięciu obu obiektów ze slotu.
Pełny setup poziomu i jego flaga aktywacji nadal nie są podłączone do podglądu.

`engine_setup_emitter_group` przenosi konkretny setup `0x287bb`: zeruje flagę
aktywacji, tworzy cztery emitery na X 3480/3512/3536/3568, Y 424, z licznikami
170/190/200/210 i wariantami 0/1/0/1. Właścicielem żywej flagi i stanów
łańcuchów jest `ENGINE_EMITTER_GROUP`. Wywołujący dostarcza kamerę, okno
widoczności i kolejności renderowania. Nie przestawiamy flagi na 1 zamiast
nieprzeniesionej jeszcze ścieżki zachowania bossa.
[check_emitter_group.c](../../tools/check_emitter_group.c) porównuje stałe
z instrukcjami oryginalnego kodu i uruchamia cały setup przez dispatcher,
łącznie z ośmioma łańcuchami rodzic/dziecko.
Przed setupem wymagane są cztery wolne obiekty i cztery węzły renderowania;
brak zasobów nie zeruje flagi i nie tworzy części grupy.
Grupy nie można zainicjalizować ponownie, dopóki którykolwiek jej obiekt
lub potomek jest aktywny w tej samej puli. Grupa musi pozostać żywa.
To setup emiterów, nie pełny setup ani działająca rozgrywka poziomu.

`engine_shake_behavior` przenosi `0x283cd`: licznik od 30, użycie wartości
sprzed dekrementacji, dokładna sekwencja wstrząsu 8/0/7/0/.../1/0 i usunięcie
przy ujemnym starym liczniku. W stanie 15, przy zerowej odporności,
niezerowym X obiektu i zerowej pionowej prędkości gracza wywołuje jawny
callback oryginalnego efektu `0x22315`. Brak callbacku w tej ścieżce jest błędem.
Nie wykonuje skryptu ani grawitacji. [check_shake.c](../../tools/check_shake.c)
sprawdza wszystkie bramki efektu i 32 aktualizacje do zwolnienia obiektu.

`engine_spawn_shake` przenosi `0x2853e` i rekord DS `0x162d4`:
handler/inicjalizator `0x183cd`, zerowe flagi, deskryptor `0xe48c`, X jako
znacznik efektu i Y=0. Konstruktor natychmiast ustawia wstrząs na 8 i licznik
na 29, potem ORuje flagę gracza +0x52 z 0x40. Zachowuje bieżący obiekt.
[check_spawn_shake.c](../../tools/check_spawn_shake.c) sprawdza oba znaczniki,
efekt w piętnastej późniejszej aktualizacji, zwolnienie i ponowne użycie.
Wstrząs i odporność są żywymi wskaźnikami; nie jest to zastępcza animacja.
Rzeczywisty handler obrażeń `0x22315` oraz podłączenie wstrząsu do pełnego
renderera poziomu pozostają nieprzeniesione. Wywołujący musi dostarczyć jawny
callback efektu przy niezerowym znaczniku, nie pusty sukces.

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

Wejście DOS64 `--emitters` pokazuje oryginalną scenę `CRUMBLIN` na
`LEVEL6.MAP`: grupa czterech emiterów, rodzice z licznikiem i spadające dzieci
działają przez dispatcher z oryginalnymi skryptami, grawitacją i usuwaniem.
Lista zasobów DS `0xe3d0` wskazuje `CRUMBLIN` w slocie 160.
Stała kamera, aktywacja po sekundzie i ponowne uruchomienie grupy po usunięciu
wszystkich obiektów są jawnie testowe; nie przeniesiono aktywacji przez bossa.
Test [check_scene.c](../../tools/check_scene.c) sprawdza 20 sekund rzeczywistego
wejścia i każdy piksel, a nie tylko powodzenie ładowania.
`--idle` i `--manual` zachowują wcześniejszy podgląd Simby i przeglądarkę banków.

Przygotowanie viewportu `0x11799` odtworzono z kodu maszynowego, ponieważ
dekompilator błędnie zastąpił kamerę stałymi. Kolejność: dolny clamp do zera,
górny clamp z porównaniem signed dolnego słowa wymiaru, zapis kamery logicznej,
dodanie shake do widocznego Y i wyrównanie początków do 8 pikseli.
[check_viewport.c](../../tools/check_viewport.c) sprawdza 1966080 przypadków.
Scena testowa uruchamia oryginalny obiekt shake razem z aktywacją emiterów,
z markerem X zero (bez wywołania obrażeń gracza). Przesunięcie obejmuje mapę
i sprite'y, nie kamerę używaną do cullingu; po prezentacji zeruje się jak
oryginalne DS `0x173e2`. Test sceny mierzy rzeczywistą różnicę kolorów ARGB
względem nieruchomej mapy, nie tylko zmianę indeksów palety.

Większy blok Simby z [block_0c000.c](../recovered/block_0c000.c) jest
przeniesiony do [behaviors.c](./behaviors.c): selektory `0x1e36e`, `0x1e3bf`,
`0x1e667`, `0x1e6ee` oraz reakcje `0x1e410`, `0x1e545`.
Selektory zwracają dokładny adres handlera, skrypt DS i licznik; adresy są
danymi, nie wskaźnikami funkcji x64. Kod maszynowy uzupełnił zgubione
przez dekompilator argumenty: skrypty `61aa/61b8` lub `5952/5960`,
liczniki 50/20 i skrypt `6116/591a` przy wyjściu.
Równie ważna poprawka: test kolizji ustawia **OR `0x20`**, nie stałą `0xbb`.

Reakcje działają przez dispatcher, oryginalny interpreter skryptów i
grawitację gracza `0x20e37` (+`0x4e00` młody / +`0x6000` dorosły).
Zachowano 16 aktualizacji ruchu, wyjście w następnej, ujemną prędkość Y -5,
ruch X -3/+3 i asymetryczny stop prawego wariantu.
Nieprzeniesiony test `0x174b2` i docelowe stany gracza są jawnymi callbackami.
Brak wymaganej zależności zatrzymuje dispatcher błędem.

Test [check_player_reactions.c](../../tools/check_player_reactions.c) wykonuje
11010048 selekcji; [check_player_deflection.c](../../tools/check_player_deflection.c)
sprawdza cały odcinek z dokładnymi pozycjami, ułamkami i deskryptorami.
Podgląd `--deflection` korzysta z oryginalnych `SYFLIPBW/SYFLIPFW` i wykonuje
osiem powtarzanych przypadków testowych. Na granicy następnego stanu zatrzymuje
reakcję, zamiast dopisywać rozgrywkę. [check_scene.c](../../tools/check_scene.c)
z argumentem `--deflection` sprawdza 20 sekund rzeczywistego wejścia:
128064000 pikseli ARGB, 320 klatek z ruchem i 20 granic przejścia.

Test `--flight` łączy odbicie, pełne ścieżki lotu `0x1aa97` /
`0x1ae53` oraz selektory lądowania `0x1b307` / `0x1b4a0`.
Strzałki zmieniają kierunek w powietrzu przez oryginalne rozgałęzienia.
Zachowano asymetrię sondy w górę, resetu skryptu, licznika i zerowania Y.
Grawitacja `0x20ea6` uwzględnia bit 2 flag; `0x20e37` z wcześniejszego
odbicia nadal używa ograniczenia bezwarunkowo.

Przy przejściu z odbicia handler jest już ustawiony. Oryginalny lot pomija
wtedy inicjalizację i zachowuje skrypt przewrotu — nie wymusza `0x6116`.
Podgląd ładuje wszystkie 28 banków młodego Simby, ponieważ dalsze rekordy
skryptu wychodzą poza same banki przewrotów.
Ziemia na Y=160, wyniki sondy, brak krawędzi i ponowne uruchomienia są
jawnym fixture; rzeczywiste sondy mapy i wybrane stany naziemne nie są
zastąpione wymyśloną grą. Test zatrzymuje się na ich granicy.
[check_player_air.c](../../tools/check_player_air.c) sprawdza pełne ścieżki
i 2752512 lądowań, a [check_scene.c](../../tools/check_scene.c) z `--flight`
sprawdza 20 sekund rzeczywistego wejścia, dziesięć pełnych łańcuchów
i 128064000 pikseli. `--steering` sprawdza też wejście strzałek.

Kolejny blok: skoki `0x1b604` / `0x1b7e7`, podtrzymanie `0x1b5ac`
i regeneracja po lądowaniu `0x1b19f` / `0x1b253`. Argumenty z kodu
maszynowego: start `6180/5944`, dalszy lot `612c/5928`, opóźnienie 4/10.
Zachowano prędkości startowe, boost 8/6, bit `0x1000`, flagę pędu
`0x2000`, zmianę kierunku bez ponownej inicjalizacji i wcześniejsze
przejście dorosłego do lotu przy Vy >= -3. Prawe OR maski kolizji
wykonuje się przed sondą, lewe po niej; początek skoku wykonuje AND `0xdf`.
Regeneracja ustawia handler idle przed ostatnią animacją, nie wywołuje
jeszcze jego pełnej logiki. Żądanie dźwięku 4/5 jest jawnym callbackiem.

Podgląd `--jump` demonstruje krótkie/długie skoki w obu kierunkach.
Spacja przejmuje sterowanie, rozpoczyna skok na ziemi i podtrzymuje boost;
strzałki zmieniają kierunek, Escape wychodzi. Zdarzenie Spacji jest
zapamiętywane między odpytywaniem HID a tickiem gry. Po lądowaniu można
skoczyć ponownie. Ziemia Y=160, idle/input i automatyczny demo-reset są
nadal fixture, nie przeniesionym poziomem; manualny tryb nie teleportuje
ani nie uruchamia skoków sam. `--flight` zachowuje wcześniejszy test.

[check_player_jump.c](../../tools/check_player_jump.c) sprawdza 393210
opóźnień, 393216 liczników regeneracji, 4608 kombinacji boost i 218
niezależnych ticków trajektorii. [check_scene.c](../../tools/check_scene.c) z `--jump`
sprawdza dziewięć pełnych skoków i 128064000 pikseli; `--jump-steering`
cztery skoki z klawiatury, osiem zmian kierunku, zdarzenia długiego idle
i różnicę wysokości co najmniej 40 pikseli między krótkim i trzymanym skokiem.

Domyślne wejście przenosi teraz pełne idle naziemne `0x1c2cd/0x1c8d5`,
bieg `0x1cdc2/0x1d108`, obrót `0x1beb7/0x1c0a1`, kucanie
`0x1b9ca/0x1bc80` i turlanie `0x1ea46/0x1eb56` z oryginalnego obiektu
kodu. Reset `0x1c28e` zeruje prędkości i state, wykonuje AND `0xfd`
maski kolizji i czyści bit `0x10`; nie zapisuje stałej z dekompilatora.
Akceleracja korzysta z już przeniesionego helpera `0x1cda1/0x1a9da`.

Powiązano idle -> bieg -> obrót -> skok -> lot -> lądowanie -> wybrany
stan naziemny. Bieg wybiera skok `6172/5936` bez opóźnienia, idle
`6180/5944` z 4/10 tickami. Zachowano różny skrypt dalszego lotu dla
prawego wymuszonego skoku, lewy bieg kontynuujący po fladze 1 i różne
inicjalizacje lewego/prawego kucania. Turlanie wybiera się z prędkością
większą niż 3, odejmuje/dodaje `0xe00`, może odbić prędkość na oryginalnych
flagach granicy i wraca do biegu przy progu 2. Żądanie próbki 6 jest jawne.

Strzałki poziome biegną, Down kuca/turla, Spacja skacze, Ctrl ryczy. Po lądowaniu
nie ma już atrapowej pauzy ani zerowania pędu przez podgląd. Fixture
to płaska ziemia Y=160, sondy, wejście demo i polityka
śledzenia X przez kamerę. Rzeczywiste kolizje mapy i specjalne stany
nie zostały podmienione fikcyjnym poziomem.
Diagnostyka wszystkich podglądów trafia do `LIONKING.LOG` w bieżącym
katalogu, nadpisywanego przy starcie. Podczas gry nie jest renderowany
tekst konsoli. Błąd zapisu kończy podgląd; komunikat konsoli pojawia się
dopiero po zatrzymaniu renderowania.
[check_player_ground.c](../../tools/check_player_ground.c) sprawdza
bezpośrednio przeniesione gałęzie i trajektorie; domyślny
[check_scene.c](../../tools/check_scene.c) sprawdza spięty blok.

Kolejny blok dodaje ryk `0x1ec69`, animację reakcji `0x1ee35`,
ogłuszenie `0x1ee60`, selektor obrażeń `0x1ef04`, odrzut
`0x1f017/0x1f160`, ślizg `0x1f80d` oraz naziemne/powietrzne
stany pochyłości `0x1fe3c/0x1ff83`. Wszystkie używają oryginalnych
strumieni DS i istniejącego interpretera animacji.

Helper `0x1a6ff` wykonuje grawitację `0x4e00` również dla dorosłego
Simby, zeruje rodzaj kontaktu w locie i zatrzymuje Vy przy podparciu.
Odrzut ma Vy=-3, Vx=+1/-1, licznik 18/40, blokadę granic oraz
oryginalną asymetrię testu bitu formy. Obrażenia zmniejszają dodatnie
HP, ustawiają odporność 100 i wybierają stronę na podstawie źródła;
przeniesiono też wyjątek ogłuszenia przy podparciu.

Ryk przenosi ładunek do jednoklatkowego impulsu w ticku 14/30,
kończy w ticku 55/94, zachowuje kierunek z parametru counter.
Próbki 2/3/4/5 są jawnie zgłaszane bez odtwarzania; `0x1510c`
w oryginale jest RET, więc nie dorobiono mu efektów.

Domyślne demo trwa 12 sekund: ruch/skoki, dwa ryki, testowe trafienie.
H wstrzykuje trafienie, T cyklicznie kontakt terenu 6/9/5/8 na 60
ticków. Źródło obrażeń, te kontakty i początkowe mierniki to fixture.
Odnawianie ryku, odliczanie odporności i reakcje przeciwników pozostają
nieprzeniesione. [check_player_actions.c](../../tools/check_player_actions.c)
obejmuje kierunki, timingi, maski, odrzut, ogłuszenie i przejścia ślizgu.
