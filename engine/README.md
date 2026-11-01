# Wydzielone bloki silnika

Podział na podstawie potwierdzonego przepływu instrukcji, bez odtwarzania brakujących ciał C:

| Moduł | Definicje | Zakres |
|---|---:|---|
| [render.c](./render.c) | 10 | Przygotowanie widoku, etapy rysowania, warianty sceny, przebieg obiektów, pula węzłów renderowania i sterowanie animacją. |
| [timing.c](./timing.c) | 1 | Dispatcher aktualizacji z akumulatorem czasu. |
| [objects.c](./objects.c) | 3 | Aktualizacja listy obiektów przez callbacki oraz pobieranie i zwracanie obiektu do puli. |
| [input.c](./input.c) | 1 | Odczyt sterowania: klawiatura, joystick, odtwarzane wejście. |
| [resources.c](./resources.c) | 6 | Wyszukiwanie wpisu archiwum EPF, odczyt informacji, ładowanie zasobu, odczyt surowych bajtów i wrappery. |
| [resource_decoder.c](./resource_decoder.c) | 2 | Dekoder słownikowy danych EPF i ustawianie szerokości kodów. |
| [audio_control.c](./audio_control.c) | 3 | Wybór muzyki, ustawienie efektu i zatrzymanie dwóch kanałów efektów; warstwa gry nad sterownikiem audio. |

Łącznie: 26 definicji silnika. W głównym pliku pozostaje 534, w bibliotekach 190. Zachowano wszystkie 750 definicji eksportu.

Prezentacja bufora `vga_present_frame` znajduje się w [libs/vga.c](../libs/vga.c), nie w rendererze silnika.

Główny [pseiudo.c](../pseiudo.c) dołącza moduły; nadal przechowuje wspólne deklaracje globali i niewydzielone funkcje. Pliki nie są osobnymi jednostkami kompilacji ani działającym portem. Zachowano sygnatury i ciała eksportu, w tym błędy dekompilatora. Czytelna nazwa oznacza ustaloną rolę, nie poprawność implementacji. W szczególności wyeksportowany dispatcher zawiera błędną stałą zamiast odczytu ticków, a przygotowanie widoku — błędne stałe zamiast obliczeń widocznych w asemblerze.

`render_stage_one` i `render_stage_two` to celowo neutralne nazwy: nie potwierdzono jeszcze, które fragmenty przedstawiają tło, teren czy nakładki. Renderer obiektów modyfikuje też stan animacji. Nie przesunięto tych efektów ubocznych do aktualizacji logiki.

Mapowanie nazw i pochodzenia: [RENAMES.tsv](../libs/RENAMES.tsv) i [FUNCTIONS.tsv](../libs/FUNCTIONS.tsv). Dowody semantyczne: [FINDINGS.md](../FINDINGS.md), [main_flow.asm](../bin/main_flow.asm), [frame_timing.asm](../bin/frame_timing.asm).

Dowody kolejnego podziału: [module_blocks.asm](../bin/module_blocks.asm). Pula obiektów aktualizacji i pula węzłów renderowania są odrębne: nie połączono ich struktur. Funkcje `engine_acquire_object` i `engine_release_object` zarządzają pulą gry, nie są standardowym `malloc/free`. Obsługa EPF również nie jest biblioteką standardową: wywołuje niższą warstwę seek/read i własny dekoder. Dekoder został wydzielony jako `resources_decode_dictionary_stream`; dowody w [resource_decoder.asm](../bin/resource_decoder.asm). Jego kod maszynowy używa słownika prefiksów/sufiksów, szerokości 9–14 bitów i kodów sterujących zależnych od szerokości. Jest podobny do LZW, ale nie potwierdzono zgodności z konkretną biblioteką. Moduły nie są jeszcze hermetyczne.

Walidacja: `perl tools/split_pseudocode.pl --check`. Potwierdza zachowanie eksportu, nie poprawność gry. Kolejne etapy: wydzielać następne rozpoznane bloki, odzyskiwać poprawne funkcje z EXE, definiować interfejsy i zastępować potwierdzone standardowe API oryginalnymi bibliotekami.
